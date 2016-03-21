Imports System.ComponentModel
Imports System.Collections.ObjectModel
Imports System.IO
Imports System.Threading
Imports System.Text

''' <summary>
''' Contains the routines necessary to perform the Quantitative Subcellular Compartmentalization Analaysis (Q-SCAn) method.
''' Inherits from BackgroundWorker so that it runs on a separate thread from the UI.
''' However, CancelAsync() does not work, and WorkerSupportsCancellation = False to enforce this. Use RequestCancelAsync() instead.
''' </summary>
Friend Class QSCAnBackgroundWorker
    Inherits BackgroundWorker

#Region "Private Fields"
    Const qMark = """"

    ' Variables to hold local fixed copies of the settings as they were when the run started.
    Private imageJPath As String
    Private cellProfilerPath As String
    Private pythonPath As String
    Private cellProfilerPluginsPath As String

    Private shadingCorrectionPrefix As String
    Private darkCurrentCorrectionPrefix As String
    Private isDarkCurrentTimeSeries As Boolean
    Private analysisSuffix As String

    Private setMetadataManually As Boolean
    Private metadata As String

    Private inputImagesDirName As String
    Private outputDataDirName As String

    Private numFluorescenceChannels As Integer
    Private numOtherCompartments As Integer

    Private normalizationFileName As String
    Private compartmentLocalizationDataFileName As String

    Private openAndExportImageJMacroFileName As String
    Private calculateMedianImageJMacroFileName As String
    Private calculateMedianTimeSeriesImageJMacroFileName As String

    Private backgroundCorrectionPipelineFileName As String
    Private identifyCellsPipelineFileName As String
    Private measureImageIntensitiesPipelineFileName As String
    Private filterCellsAndIdentifyCompartmentsPipelineFileName As String
    Private calculateLocIndicesAndExportIntensitiesPipelineFileName As String

    Private checkPipelineSuccess As Boolean

    ' Arguments supplied to DoWork
    Private sourceImagesDir As String
    Private analysisDir As String
    Private fileExtension As String

    ' Computed variables
    Private inputImagesDir As String = ""
    Private outputDataDir As String = ""

    Private escapedMetadataFirst As String = ""
    Private escapedMetadataSubsequent As String = ""
    Private escapedSavedMetadata As String = ""

    Private numChannels As Integer = 0
    Private numCompartments As Integer = 0

    Private imageJProcess As New Process
    Private WithEvents cellProfilerProcess As New Process
    Private activeProcess As New Process

    Private showCPAcvitiy As Boolean

    Private imageJArgs As String = ""
    Private cellProfilerArgs As String = ""

    Private pipelineDictionary As New Dictionary(Of Integer, String) ' Step number --> Pipeline file name

    Private rootDir As String = My.Computer.FileSystem.CurrentDirectory
    Private numImages As Integer = 0

    Private watch As New Stopwatch

    Private workerWaitHandle As New AutoResetEvent(False) ' For completeion/cancelation
    Private subWorkerWaitHandle As New AutoResetEvent(False) ' For pause and resume

    Private errorFound As Boolean
    Private errorMessage As String

    Private errorStreamWriter As StreamWriter
    Private errorFileName As String

    Private cellProfilerNeedsPython As Boolean
#End Region

    ''' <summary>
    ''' Create a new instance of QSCAnBackgroundWorker.
    ''' </summary>
    Public Sub New()
        WorkerSupportsCancellation = False ' Disables use of CancelAsync(), which does not work with an event-driven structure.
        WorkerReportsProgress = True
    End Sub

#Region "Worker Initialization"
    ''' <summary>
    ''' Contains the logic to initialize and begin performing Q-SCAn and controls exit of the task.
    ''' </summary>
    ''' <param name="sender">The QSCAnBackgroundWorker.</param>
    ''' <param name="e">Arguments related to the current state of execution, and which are passed back out to the RunWorkerCompleted event.
    ''' ".result" contains a tuple of a boolean and a string, where the boolean indicates whether the method was successful, and the string
    ''' will contain the time elapsed if successful, or an error message if not.</param>
    Friend Sub QSCAnBackgroundWorker_DoWork(ByVal sender As Object, ByVal e As DoWorkEventArgs) Handles Me.DoWork
        With DirectCast(e.Argument, Tuple(Of String, String, String))
            sourceImagesDir = .Item1
            analysisDir = .Item2
            fileExtension = .Item3
        End With

        Try
            LoadSettings()
            PrepareRun()

            watch.Start()

            RaiseEvent StepCompleted(New StepCompletedEventArgs(0, True))

            workerWaitHandle.WaitOne() ' Wait for the process to be completed, cancelled, or experience a fatal error.

            watch.Stop()
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try

        If errorFound Then
            e.Result = Tuple.Create(Of Boolean, Object)(False, errorMessage)
        ElseIf Not cancelRequested Then
            e.Result = Tuple.Create(Of Boolean, Object)(True, watch.Elapsed)
        Else
            e.Result = Tuple.Create(Of Boolean, Object)(False, Nothing)
        End If

        e.Cancel = cancelRequested

        errorStreamWriter.Close()
    End Sub

    ''' <summary>
    ''' Load a copy of the settings from the application's settings object for use in this task.
    ''' </summary>
    Private Sub LoadSettings()
        With My.Settings
            imageJPath = .ImageJPath
            cellProfilerPath = .CellProfilerPath
            pythonPath = .PythonPath
            cellProfilerPluginsPath = .CellProfilerPluginsPath

            shadingCorrectionPrefix = .ShadingCorrectionPrefix
            darkCurrentCorrectionPrefix = .DarkCurrentCorrectionPrefix
            isDarkCurrentTimeSeries = .DarkCurrentIsTimeSeries
            analysisSuffix = .AnalysisSuffix

            numFluorescenceChannels = .NumberOfFluorescenceChannels
            numOtherCompartments = .NumberOfOtherCompartments

            setMetadataManually = .SetMetadataManually
            metadata = .Metadata

            inputImagesDirName = .InputImagesDirName
            outputDataDirName = .OutputDataDirName

            normalizationFileName = .Output_NormalizationFileName
            compartmentLocalizationDataFileName = .Output_CompartmentLocalizationData

            openAndExportImageJMacroFileName = .ImageJ_OpenAndExportChannelsFileName
            calculateMedianImageJMacroFileName = .ImageJ_CalculateMedianImageFileName
            calculateMedianTimeSeriesImageJMacroFileName = .ImageJ_CalculateMedianImageTimeSeriesFileName

            backgroundCorrectionPipelineFileName = .CellProfiler_BackgroundCorrectionFileName
            identifyCellsPipelineFileName = .CellProfiler_IdentifyCellsFileName
            measureImageIntensitiesPipelineFileName = .CellProfiler_MeasureImageIntensitiesFileName
            filterCellsAndIdentifyCompartmentsPipelineFileName = .CellProfiler_FilterCellsAndIdentifyCompartmentsFileName
            calculateLocIndicesAndExportIntensitiesPipelineFileName = .CellProfiler_CalculateLocalizationIndicesAndExportIntensitiesFileName

            checkPipelineSuccess = .CheckPipelineSuccess

            errorFileName = .CellProfilerLogFileName
        End With
    End Sub

    ''' <summary>
    ''' Compute and set up the resources needed by the Q-SCAn task.
    ''' </summary>
    Private Sub PrepareRun()
        watch.Reset()

        If Not setMetadataManually Then
            ' Replace the metadata in the pipeline files

            Dim builder As MetadataBuilder = MetadataBuilder.Create(metadata)

            ' Get just the field names
            Dim fields As IEnumerable(Of MetadataElement) = From field In builder
                                                   Where field.MetadataType = MetadataElementTypes.Field

            escapedMetadataFirst = metadata.Replace("\", "\\\\")

            Dim metadataStrings As New List(Of String)
            For Each field As MetadataElement In fields
                metadataStrings.Add("(?P<" & field.FieldName & ">" & field.MatchExpression & ")")
            Next
            escapedMetadataSubsequent = "\(" & String.Join(" - ", metadataStrings) & "\)"
            escapedMetadataSubsequent = escapedMetadataSubsequent.Replace("\", "\\\\")

            metadataStrings = New List(Of String)
            For Each field As MetadataElement In fields
                metadataStrings.Add("\g<" & field.FieldName & ">")
            Next
            escapedSavedMetadata = "(" & String.Join(" - ", metadataStrings) & ")"
            escapedSavedMetadata = escapedSavedMetadata.Replace("\", "\\\\")

            If Not BackupPipelineFiles() Then
                Exit Sub
            End If

            Dim versionUntested As Boolean
            versionUntested = ModifyPipelineFile(backgroundCorrectionPipelineFileName, fields)
            versionUntested = ModifyPipelineFile(identifyCellsPipelineFileName, fields) Or versionUntested
            versionUntested = ModifyPipelineFile(measureImageIntensitiesPipelineFileName, fields) Or versionUntested
            versionUntested = ModifyPipelineFile(filterCellsAndIdentifyCompartmentsPipelineFileName, fields) Or versionUntested
            versionUntested = ModifyPipelineFile(calculateLocIndicesAndExportIntensitiesPipelineFileName, fields) Or versionUntested

            If versionUntested Then
                MessageBox.Show("The pipeline files contain module versions that haven't been tested for metadata replacement.", "Notice", MessageBoxButton.OK, MessageBoxImage.Information)
            End If
        End If

        inputImagesDir = analysisDir & Path.DirectorySeparatorChar & inputImagesDirName
        outputDataDir = analysisDir & Path.DirectorySeparatorChar & outputDataDirName

        numChannels = 1 + numFluorescenceChannels
        numCompartments = 2 + numOtherCompartments

        imageJProcess = New Process
        imageJProcess.StartInfo = New ProcessStartInfo
        imageJProcess.StartInfo.FileName = imageJPath
        imageJArgs = "-batch " & qMark & rootDir & Path.DirectorySeparatorChar & "{0}" & qMark & " " & qMark & "{1}" & qMark ' String to be used by the Format function, which will allows {0} and {1} to be replaced.

        cellProfilerProcess = New Process
        cellProfilerArgs = "--pipeline " & qMark & rootDir & Path.DirectorySeparatorChar & "{0}" & qMark & " --image-directory " & qMark & "{1}" & qMark & " --output-directory " & qMark & "{1}" & qMark & " --plugins-directory " & qMark & cellProfilerPluginsPath & qMark & " --run-headless" ' String to be used by the Format function, which will allows {0} and {1} to be replaced.
        cellProfilerProcess.EnableRaisingEvents = True
        cellProfilerProcess.StartInfo = New ProcessStartInfo
        cellProfilerNeedsPython = cellProfilerPath.EndsWith(".py")
        With cellProfilerProcess.StartInfo
            If cellProfilerNeedsPython Then
                .FileName = pythonPath
                cellProfilerArgs = qMark & cellProfilerPath & qMark & " " & cellProfilerArgs
            Else
                .FileName = cellProfilerPath
            End If
            ' Set it up so that it doesn't create a winow and passes its error output to us.
            .UseShellExecute = False
            .CreateNoWindow = True
            .RedirectStandardError = True
        End With

        ' Reset the log file.
        errorStreamWriter = New StreamWriter(New FileStream(errorFileName, FileMode.Create, FileAccess.Write, FileShare.Read))
        errorStreamWriter.Close()

        pipelineDictionary = New Dictionary(Of Integer, String)
        pipelineDictionary.Add(3, backgroundCorrectionPipelineFileName)
        pipelineDictionary.Add(4, identifyCellsPipelineFileName)
        pipelineDictionary.Add(5, measureImageIntensitiesPipelineFileName)
        pipelineDictionary.Add(6, filterCellsAndIdentifyCompartmentsPipelineFileName)
        pipelineDictionary.Add(7, calculateLocIndicesAndExportIntensitiesPipelineFileName)
    End Sub

    ''' <summary>
    ''' Backs up a copy of the pipeline files before they are modified, so that they can be retrieved in case something goes terribly wrong.
    ''' </summary>
    ''' <result>Boolean indicating success.</result>
    Private Function BackupPipelineFiles() As Boolean
        Try
            ' Backup the last pipeline files
            Dim backupDir As String = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & "Pipeline Backup"
            My.Computer.FileSystem.CreateDirectory(backupDir)
            My.Computer.FileSystem.CopyFile(backgroundCorrectionPipelineFileName, backupDir & Path.DirectorySeparatorChar & backgroundCorrectionPipelineFileName, True)
            My.Computer.FileSystem.CopyFile(identifyCellsPipelineFileName, backupDir & Path.DirectorySeparatorChar & identifyCellsPipelineFileName, True)
            My.Computer.FileSystem.CopyFile(measureImageIntensitiesPipelineFileName, backupDir & Path.DirectorySeparatorChar & measureImageIntensitiesPipelineFileName, True)
            My.Computer.FileSystem.CopyFile(filterCellsAndIdentifyCompartmentsPipelineFileName, backupDir & Path.DirectorySeparatorChar & filterCellsAndIdentifyCompartmentsPipelineFileName, True)
            My.Computer.FileSystem.CopyFile(measureImageIntensitiesPipelineFileName, backupDir & Path.DirectorySeparatorChar & measureImageIntensitiesPipelineFileName, True)
            Return True
        Catch ex As Exception
            PrematureStop(ex.Message)
            Return False
        End Try
    End Function

    ''' <summary>
    ''' Modify the pipeline files to use the provided metadata.
    ''' </summary>
    ''' <param name="fileName">The file to modify.</param>
    ''' <param name="fields">The collection of metadata field elements.</param>
    ''' <returns>Boolean value indicating whether it detected proper versions.</returns>
    Private Function ModifyPipelineFile(ByVal fileName As String, ByVal fields As IEnumerable(Of MetadataElement)) As Boolean
        Dim fileLineList As List(Of String) = LoadFile(fileName)
        Dim newFileLineList As New List(Of String)

        Dim versionUntested As Boolean = False

        If Not fileLineList(1).StartsWith("Version:2") Then
            versionUntested = True
        End If

        Dim lineIndex As Integer
        Do
            Dim currentLine As String = fileLineList(lineIndex)
            Dim lineElements As String() = currentLine.Split({CChar(":")}, StringSplitOptions.RemoveEmptyEntries)

            If lineElements.Length > 0 Then
                Select Case lineElements(0)
                    Case "LoadSingleImage"
                        If fileName = backgroundCorrectionPipelineFileName Then
                            If Not currentLine.Contains("variable_revision_number:5") Then
                                versionUntested = True
                            End If

                            lineIndex += 1

                            Dim firstItem As Boolean = True
                            Do
                                currentLine = fileLineList(lineIndex)
                                lineElements = currentLine.Split({CChar(":")}, StringSplitOptions.RemoveEmptyEntries)

                                If lineElements.Length > 1 Then
                                    If lineElements(0) = "    Filename of the image to load (Include the extension, e.g., .tif)" Then
                                        Dim fieldElements As String() = lineElements(1).Split({CChar(" ")}, StringSplitOptions.RemoveEmptyEntries)

                                        ' For the first item, the shading correction image, save the last element "Median.tif"
                                        ' For the other items, the dark current correction images, save the last two elements, "<channel_name>" and "Median.tif"

                                        If firstItem Then
                                            lineElements(1) = String.Join(" ", {shadingCorrectionPrefix, fieldElements(fieldElements.Length - 1)})
                                            firstItem = False
                                        Else
                                            lineElements(1) = String.Join(" ", {darkCurrentCorrectionPrefix, fieldElements(fieldElements.Length - 2), fieldElements(fieldElements.Length - 1)})
                                        End If

                                        fileLineList(lineIndex) = String.Join(":", lineElements)
                                    End If
                                End If
                                lineIndex += 1
                            Loop Until lineIndex = fileLineList.Count OrElse String.IsNullOrWhiteSpace(fileLineList(lineIndex))
                        End If

                    Case "LoadImages"
                        If Not currentLine.Contains("variable_revision_number:11") Then
                            versionUntested = True
                        End If

                        Dim isBackgroundCorrectionPipeline As Boolean = fileName = backgroundCorrectionPipelineFileName

                        lineIndex += 1

                        Do
                            currentLine = fileLineList(lineIndex)
                            lineElements = currentLine.Split({CChar(":")}, StringSplitOptions.RemoveEmptyEntries)

                            If lineElements.Length > 1 Then
                                ' Note: CellProfiler pipeline files use "\" as an escape character. "\\\\" is decoded into "\" when it is loaded.
                                Select Case True
                                    Case isBackgroundCorrectionPipeline AndAlso lineElements(0) = "    Type the regular expression that finds metadata in the subfolder path"
                                        lineElements(1) = escapedMetadataFirst
                                        fileLineList(lineIndex) = String.Join(":", lineElements)

                                    Case Not isBackgroundCorrectionPipeline AndAlso lineElements(0) = "    Regular expression that finds metadata in the file name"
                                        lineElements(1) = escapedMetadataSubsequent
                                        fileLineList(lineIndex) = String.Join(":", lineElements)

                                End Select
                            End If
                            lineIndex += 1
                        Loop Until lineIndex = fileLineList.Count OrElse String.IsNullOrWhiteSpace(fileLineList(lineIndex))

                    Case "SaveImages"
                        If Not currentLine.Contains("variable_revision_number:7") Then
                            versionUntested = True
                        End If

                        lineIndex += 1

                        Do
                            currentLine = fileLineList(lineIndex)
                            lineElements = currentLine.Split({CChar(":")}, StringSplitOptions.RemoveEmptyEntries)

                            If lineElements.Length > 1 Then
                                Select Case lineElements(0)
                                    Case "    Text to append to the image name"
                                        lineElements(1) = " " & escapedSavedMetadata
                                        fileLineList(lineIndex) = String.Join(":", lineElements)

                                    Case "    Enter single file name"
                                        Dim fieldElements As String() = lineElements(1).Split({CChar(" ")}, StringSplitOptions.RemoveEmptyEntries)
                                        Dim prefix As String = lineElements(1).Remove(lineElements(1).IndexOf("(")).TrimEnd({CChar(" ")})

                                        lineElements(1) = prefix & " " & escapedSavedMetadata
                                        fileLineList(lineIndex) = String.Join(":", lineElements)
                                End Select
                            End If

                            lineIndex += 1
                        Loop Until lineIndex = fileLineList.Count OrElse String.IsNullOrWhiteSpace(fileLineList(lineIndex))

                    Case "ExportToSpreadsheet"
                        If Not currentLine.Contains("variable_revision_number:7") Then
                            versionUntested = True
                        End If

                        lineIndex += 1

                        Do
                            currentLine = fileLineList(lineIndex)
                            lineElements = currentLine.Split({CChar(":")}, StringSplitOptions.RemoveEmptyEntries)

                            If lineElements.Length > 1 Then
                                If lineElements(0) = "    Press button to select measurements to export" Then
                                    ' Strip and then re-add metadata fields

                                    Dim exportFields As String() = lineElements(1).Split({CChar(",")}, StringSplitOptions.RemoveEmptyEntries)
                                    Dim newExportFields As New List(Of String)(From field In exportFields
                                                                               Where Not field.Contains("Metadata"))
                                    For Each field As MetadataElement In fields
                                        newExportFields.Add("Image\x7CMetadata_" & field.FieldName)
                                    Next
                                    lineElements(1) = String.Join(",", newExportFields)
                                    fileLineList(lineIndex) = String.Join(":", lineElements)
                                End If
                            End If

                            lineIndex += 1
                        Loop Until lineIndex = fileLineList.Count OrElse String.IsNullOrWhiteSpace(fileLineList(lineIndex))
                End Select
            End If

            lineIndex += 1
        Loop While lineIndex < fileLineList.Count - 1

        SaveFile(fileName, fileLineList)

        Return versionUntested
    End Function
#End Region

#Region "RunSteps Methods"
    ''' <summary>
    ''' Starts the task by running Step 1 - Export all source images as TIFFs.
    ''' </summary>
    Private Sub RunStep1()
        If cancelRequested Then
            Exit Sub
        ElseIf pauseRequested Then
            subWorkerWaitHandle.WaitOne()
        End If

        Try
            ReportProgress(1)
            Dim imageJProcess As New Process
            imageJProcess.StartInfo = New ProcessStartInfo
            imageJProcess.StartInfo.FileName = imageJPath
            Dim imageJArgs As String = "-batch " & qMark & rootDir & Path.DirectorySeparatorChar & "{0}" & qMark & " " & qMark & "{1}" & qMark
            imageJProcess.StartInfo.Arguments = String.Format(imageJArgs, openAndExportImageJMacroFileName, sourceImagesDir & "|" & inputImagesDir)
            activeProcess = imageJProcess
            imageJProcess.Start()

            ' CHECK IF THIS becoming unecessary IS 1.48 specific or 64-bit specific


            ' Get the process spawned by ImageJ
            '' Looking for a Javaw process spawned after the main process.
            '' Or if that isn't found, ImageJ itself is fine -- Must have been a change in the most recent version of ImageJ
            'Dim imageJSubProcess As New Process


            'Do
            '    If cancelRequested Then Exit Sub

            '    Dim totalWaited As Integer
            '    Thread.Sleep(100)
            '    totalWaited += 100
            '    'For Each proc As Process In Process.GetProcessesByName("javaw")
            '    '    If proc.StartTime >= imageJProcess.StartTime Then
            '    '        imageJSubProcess = proc
            '    '    End If
            '    'Next

            '    For Each proc As Process In Process.GetProcessesByName("ImageJ")
            '        If proc.StartTime >= imageJProcess.StartTime Then
            '            imageJSubProcess = proc
            '        End If
            '    Next

            '    If totalWaited > 10000 Then
            '        RaiseEvent StepCompleted(New StepCompletedEventArgs(1, False))
            '        Exit Sub
            '    End If
            'Loop Until IsProcessAssociated(imageJSubProcess)

            'imageJSubProcess.EnableRaisingEvents = True
            'activeProcess = imageJSubProcess

            'AddHandler imageJSubProcess.Exited, AddressOf OnStep1Completed

            imageJProcess.EnableRaisingEvents = True
            AddHandler imageJProcess.Exited, AddressOf OnStep1Completed
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try
    End Sub

    ''' <summary>
    ''' Check whether the Process object is associated with a process,
    ''' which is indicated by whether the property throws an exception.
    ''' </summary>
    ''' <param name="proc">Process object to check.</param>
    ''' <returns>True if the Process is valid.</returns>
    Private Function IsProcessAssociated(proc As Process) As Boolean
        Try
            Dim test As Integer = proc.Id
            Return True
        Catch ex As Exception
            Return False
        End Try
    End Function

    ''' <summary>
    ''' Continues the task by running Step 2 - Calculate median background correction images.
    ''' These steps are too quick to warrant searching for the ImageJ process and setting an event.
    ''' </summary>
    Private Sub RunStep2()
        If cancelRequested Then
            Exit Sub
        ElseIf pauseRequested Then
            subWorkerWaitHandle.WaitOne()
        End If

        Try
            ReportProgress(2)
            Dim shadingCorrectionDir As String = GetDirectoryGivenPrefix(shadingCorrectionPrefix, inputImagesDir)
            Dim darkCurrentCorrectionDir As String = GetDirectoryGivenPrefix(darkCurrentCorrectionPrefix, inputImagesDir)

            ' Compute shading median image
            imageJProcess.StartInfo.Arguments = String.Format(imageJArgs, calculateMedianImageJMacroFileName, shadingCorrectionDir)
            imageJProcess.Start()

            ' Check for success of the shading median calculation
            Do
                If cancelRequested Then Exit Sub
                Dim totalWaited As Integer
                Thread.Sleep(100)
                totalWaited += 100
                If totalWaited > 10000 Then
                    RaiseEvent StepCompleted(New StepCompletedEventArgs(2, False))
                    Exit Sub
                End If
            Loop Until My.Computer.FileSystem.GetFiles(inputImagesDir).Count = 1

            ' Compute dark current median images
            If isDarkCurrentTimeSeries Then
                imageJProcess.StartInfo.Arguments = String.Format(imageJArgs, calculateMedianTimeSeriesImageJMacroFileName, darkCurrentCorrectionDir)
            Else
                imageJProcess.StartInfo.Arguments = String.Format(imageJArgs, calculateMedianImageJMacroFileName, darkCurrentCorrectionDir)
            End If
            imageJProcess.Start()

            ' Check for success of the dark current median calculations
            Do
                If cancelRequested Then Exit Sub
                Dim totalWaited As Integer
                Thread.Sleep(100)
                totalWaited += 100
                If totalWaited > 10000 Then
                    RaiseEvent StepCompleted(New StepCompletedEventArgs(2, False))
                    Exit Sub
                End If
            Loop Until My.Computer.FileSystem.GetFiles(inputImagesDir).Count = 1 + numChannels

            ' Delete all original exported images that were used to produce the correction images.
            For Each dir As String In My.Computer.FileSystem.GetDirectories(inputImagesDir)
                Dim dirName As String = GetPathElementName(dir)
                If dirName.StartsWith(shadingCorrectionPrefix) OrElse dirName.StartsWith(darkCurrentCorrectionPrefix) Then
                    Try
                        My.Computer.FileSystem.DeleteDirectory(dir, FileIO.DeleteDirectoryOption.DeleteAllContents)
                    Catch ex As IOException
                        ' This often catches and doesn't successfully delete the files. Sleep the thread and try again.
                        Thread.Sleep(0)
                        My.Computer.FileSystem.DeleteDirectory(dir, FileIO.DeleteDirectoryOption.DeleteAllContents)
                    End Try
                End If
            Next

            ' Count and store the number of images to process.
            numImages = My.Computer.FileSystem.GetDirectories(inputImagesDir).Count

            RaiseEvent StepCompleted(New StepCompletedEventArgs(2, True))
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try
    End Sub

    ''' <summary>
    ''' Starts running the CellProfiler process using the pipeline file associated with the step number.
    ''' </summary>
    ''' <param name="stepNum">The current step number.</param>
    Private Sub RunCellProfilerStep(ByVal stepNum As Integer)
        If cancelRequested Then
            Exit Sub
        ElseIf pauseRequested Then
            subWorkerWaitHandle.WaitOne()
        End If

        Try
            ReportProgress(stepNum)
            cellProfilerProcess.StartInfo.Arguments = String.Format(cellProfilerArgs, pipelineDictionary(stepNum), analysisDir)
            activeProcess = cellProfilerProcess
            cellProfilerProcess.Start()

            errorStreamWriter = New StreamWriter(New FileStream(errorFileName, FileMode.Append, FileAccess.Write, FileShare.Read))
            errorStreamWriter.WriteLine("===== Begin step " & stepNum & " =====")
            cellProfilerProcess.BeginErrorReadLine()
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try

    End Sub
#End Region

#Region "StepCompleted Members"
    Private Event StepCompleted(e As StepCompletedEventArgs)

    Friend Class StepCompletedEventArgs
        Inherits EventArgs

        Friend Property StepNumber As Integer

        Friend Property IsSuccessful As Boolean

        Friend Sub New(ByVal stepNum As Integer, ByVal success As Boolean)
            StepNumber = stepNum
            IsSuccessful = success
        End Sub
    End Class

    ''' <summary>
    ''' After the ImageJ process has exited, make sure that it was successful before moving on.
    ''' </summary>
    ''' <param name="sender">The terminated Process object.</param>
    ''' <param name="e"></param>
    Private Sub OnStep1Completed(sender As Object, e As EventArgs)
        If cancelRequested Then
            Exit Sub
        ElseIf pauseRequested Then
            subWorkerWaitHandle.WaitOne()
        End If

        Try
            ' Verify that Step 1 has completed successfully
            Dim numInputImages As Integer = My.Computer.FileSystem.GetFiles(sourceImagesDir).Where(Function(x) x.EndsWith(fileExtension)).Count
            Dim numOutputImages As Integer = My.Computer.FileSystem.GetDirectories(inputImagesDir).Count

            Dim success As Boolean = numInputImages = numOutputImages

            RaiseEvent StepCompleted(New StepCompletedEventArgs(1, success))
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try
    End Sub

    ''' <summary>
    ''' After the CellProfiler process has exited, make sure that it was successful before moving on.
    ''' </summary>
    ''' <param name="sender">The terminated Process object.</param>
    ''' <param name="e"></param>
    Private Sub OnCellProfilerStepCompleted(sender As Object, e As EventArgs) Handles cellProfilerProcess.Exited
        If cancelRequested Then
            Exit Sub
        ElseIf pauseRequested Then
            subWorkerWaitHandle.WaitOne()
        End If

        Try
            Dim cellProfilerProcess As Process = DirectCast(sender, Process)

            cellProfilerProcess.CancelErrorRead()

            Dim stepNum As Integer
            Dim success As Boolean
            Dim outputDirectory As String

            Select Case True
                Case cellProfilerProcess.StartInfo.Arguments.Contains(backgroundCorrectionPipelineFileName)
                    stepNum = 3
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Corrected Images"
                    If My.Computer.FileSystem.DirectoryExists(outputDirectory) Then
                        success = My.Computer.FileSystem.GetFiles(outputDirectory).Count = numChannels * numImages
                    End If

                Case cellProfilerProcess.StartInfo.Arguments.Contains(identifyCellsPipelineFileName)
                    stepNum = 4
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Objects"
                    If My.Computer.FileSystem.DirectoryExists(outputDirectory) Then
                        success = My.Computer.FileSystem.GetFiles(outputDirectory).Count = 2 * numImages
                    End If

                Case cellProfilerProcess.StartInfo.Arguments.Contains(measureImageIntensitiesPipelineFileName)
                    stepNum = 5
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Fully Corrected Images"
                    If My.Computer.FileSystem.DirectoryExists(outputDirectory) Then
                        success = My.Computer.FileSystem.GetFiles(outputDirectory).Count = (numChannels - 2) * numImages
                    End If
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Output Data"
                    If My.Computer.FileSystem.FileExists(outputDirectory & Path.DirectorySeparatorChar & normalizationFileName) Then
                        success = CalcNormValues()
                    Else
                        success = False
                    End If

                Case cellProfilerProcess.StartInfo.Arguments.Contains(filterCellsAndIdentifyCompartmentsPipelineFileName)
                    stepNum = 6
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Objects"
                    If My.Computer.FileSystem.DirectoryExists(outputDirectory) Then
                        success = My.Computer.FileSystem.GetFiles(outputDirectory).Count = (numCompartments + 3) * numImages
                    End If

                Case cellProfilerProcess.StartInfo.Arguments.Contains(calculateLocIndicesAndExportIntensitiesPipelineFileName)
                    stepNum = 7
                    outputDirectory = analysisDir & Path.DirectorySeparatorChar & "Output Data"
                    If My.Computer.FileSystem.DirectoryExists(outputDirectory) Then
                        success = My.Computer.FileSystem.FileExists(outputDirectory & Path.DirectorySeparatorChar & compartmentLocalizationDataFileName)
                    End If
            End Select

            errorStreamWriter.WriteLine("===== End of step " & stepNum & " =====")
            errorStreamWriter.Close()

            RaiseEvent StepCompleted(New StepCompletedEventArgs(stepNum, success))
        Catch ex As Exception
            PrematureStop(ex.Message)
        End Try
    End Sub

    ''' <summary>
    ''' Starts the next step after the previous step completed successfully, or report an error condition otherwise.
    ''' </summary>
    ''' <param name="e">Arguments that specify the completed step and whether it was successful.</param>
    Private Sub QSCAnBackgroundWorder_StepCompleted(e As StepCompletedEventArgs) Handles Me.StepCompleted
        If Not cancelRequested Then
            If (checkPipelineSuccess AndAlso e.IsSuccessful) OrElse Not checkPipelineSuccess Then
                Select Case e.StepNumber
                    Case 0
                        ' Everything is initialized
                        RunStep1()
                    Case 1
                        ' Step 1 has completed successfully
                        RunStep2()

                    Case 2
                        ' Step 2 has completed successfully
                        RunCellProfilerStep(3)

                    Case 3
                        ' Step 3 has completed successfully
                        RunCellProfilerStep(4)

                    Case 4
                        ' Step 4 has completed successfully
                        RunCellProfilerStep(5)

                    Case 5
                        ' Step 5 has completed successfully
                        RunCellProfilerStep(6)

                    Case 6
                        ' Step 6 has completed successfully
                        RunCellProfilerStep(7)

                    Case 7
                        ' Step 7 has completed successfully.
                        ' Release the worker thread.
                        workerWaitHandle.Set()
                    Case Else
                        Throw New Exception("This step number, " & e.StepNumber & ", is not recognized!")
                End Select
            ElseIf checkPipelineSuccess Then
                ' A step didn't complete successfully, but we only care if asked to check for success.
                ' Ask the user for what they want to do.
                ReportProgress(50)
                Dim message As String = "The previous step did not appear to complete successfully. I suggest reviewing the CellProfiler output in " & errorFileName & " (button at left of main window) and attempting to perform the step manually to find and fix the cause of the error. After doing that, return to this prompt." & Environment.NewLine & Environment.NewLine & "Would you like to attempt the previous step again (Yes)?" & Environment.NewLine & "Or would you like to continue with the next step (No)?" & Environment.NewLine & "Or would you like to abort (Cancel)?"
                Dim result As MessageBoxResult = MessageBox.Show(message, "Error", MessageBoxButton.YesNoCancel, MessageBoxImage.Question, MessageBoxResult.Cancel)

                Select Case result
                    Case MessageBoxResult.Yes
                        ' Go back one step and try again
                        RaiseEvent StepCompleted(New StepCompletedEventArgs(e.StepNumber - 1, True))
                    Case MessageBoxResult.No
                        ' Try this step again
                        RaiseEvent StepCompleted(New StepCompletedEventArgs(e.StepNumber, True))
                    Case Else
                        PrematureStop()
                End Select
            Else
                ' A step didn't complete successfully, but the user told us not to worry about it.
            End If
        Else
            ' Cancellation has been requested, so don't do anything.
        End If
    End Sub
#End Region

#Region "Cancellation Members"
    Private Event CancelRequest()

    Private cancelRequested As Boolean

    ''' <summary>
    ''' Request cancellation of the operation. Use this instead of CancelAsync().
    ''' </summary>
    Friend Sub RequestCancelAsync()
        cancelRequested = True
        RaiseEvent CancelRequest()
    End Sub

    ''' <summary>
    ''' Kill the active spawned process and release control of the main thread.
    ''' </summary>
    Private Sub QSCAnBackgroundWorker_CancelRequested() Handles Me.CancelRequest
        ' Kill the active running process (ImageJ or CellProfiler)
        Try
            If Not activeProcess.HasExited Then
                activeProcess.Kill()
            End If
        Catch ex As InvalidOperationException
            ' Thrown if activeProcess isn't associated with a running process or if it has already exited.
            ' Don't need to do anything.
        Catch ex As Win32Exception
            ' Thrown if activeProcess is currently terminating.
            ' Don't need to do anything.
        End Try

        ' Release the worker thread.
        workerWaitHandle.Set()
    End Sub
#End Region

#Region "Pause/Resume Members"
    Private Event PauseRequest()

    Private Event ResumeRequest()

    Private pauseRequested As Boolean
    Private resumeRequested As Boolean

    Friend Sub RequestPauseAsync()
        pauseRequested = True
        resumeRequested = False
        RaiseEvent PauseRequest()
    End Sub

    Friend Sub RequestResumeAsync()
        resumeRequested = True
        pauseRequested = False
        RaiseEvent ResumeRequest()
    End Sub

    Private Sub QSCAnBackgroundWorker_PauseRequested() Handles Me.PauseRequest
        ' Pause the active running process (ImageJ or CellProfiler)
        Try
            If Not activeProcess.HasExited Then
                NativeMethods.SuspendProcess(activeProcess)
            End If
        Catch ex As Exception
            ' Don't need to do anything
        End Try

        ' Close the error log
        errorStreamWriter.Close()

        watch.Stop()
    End Sub

    Private Sub QSCAnBackgroundWorker_ResumeRequested() Handles Me.ResumeRequest
        ' Pause the active running process (ImageJ or CellProfiler)
        Try
            If Not activeProcess.HasExited Then
                NativeMethods.ResumeProcess(activeProcess)
            End If
        Catch ex As Exception
            ' Don't need to do anything.
        End Try

        ' Reopen the error log
        errorStreamWriter = New StreamWriter(New FileStream(errorFileName, FileMode.Append, FileAccess.Write, FileShare.Read))

        watch.Start()

        ' Release any paused code
        subWorkerWaitHandle.Set()
    End Sub
#End Region

#Region "Routines"
    ''' <summary>
    ''' Load the CellProfiler output file, calculate the normalization values for each channel, and save
    ''' the values to the file for the next CellProfiler pipeline to read.
    ''' </summary>
    ''' <returns>A boolean value indicating True if it succeeds.</returns>
    Private Function CalcNormValues() As Boolean
        Dim normalizationDataFile As String = analysisDir & Path.DirectorySeparatorChar & outputDataDirName & Path.DirectorySeparatorChar & normalizationFileName
        Dim fileLineList As List(Of String)

        ' Load the file, find the column names, and remove the header row.
        Try
            fileLineList = LoadFile(normalizationDataFile)
        Catch ex As Exception
            Return False
        End Try

        If fileLineList.Count < 2 Then
            Return False
        End If

        Dim headerLine As String = fileLineList(0)
        Dim colNames As String() = headerLine.Split({CChar(",")})
        fileLineList.RemoveAt(0)

        Dim numCols As Integer = colNames.Count()

        ' Find the ids for the TotalArea and TotalIntensity columns
        ' Only one Total Area column is needed, the others should all be identical
        Dim totalAreaColumn As Integer
        Dim totalIntensityColumns As New List(Of Integer)
        For i As Integer = 0 To numCols - 1
            If colNames(i).Contains("TotalArea") Then
                totalAreaColumn = i
            ElseIf colNames(i).Contains("TotalIntensity") Then
                totalIntensityColumns.Add(i)
            End If
        Next

        ' Sum the cells over the TotalArea and TotalIntensity columns
        Dim columnSums(numCols) As Double
        For Each Line As String In fileLineList
            Dim cells As String() = Line.Split({CChar(",")})
            columnSums(totalAreaColumn) += CDbl(cells(totalAreaColumn))
            For Each col As Integer In totalIntensityColumns
                columnSums(col) += CDbl(cells(col))
            Next
        Next

        ' Calculate the average intensity for each channel and add a new "DatasetAverageIntensity" column
        ' for each original "TotalIntensity" column with the calculated value in it.
        ' Also multiply the value by 100, because the goal is to have the average value = 0.01 after dividing by
        ' this number.
        For Each col As Integer In totalIntensityColumns
            Dim averageIntensity As Double = columnSums(col) / columnSums(totalAreaColumn) * 100
            Dim channelName As String = colNames(col).Remove(colNames(col).LastIndexOf(CChar("_")))
            channelName = channelName.Substring(channelName.LastIndexOf(CChar("_")) + 1)

            headerLine &= "," & "DatasetAverageIntensity" & "_" & channelName

            For i As Integer = 0 To fileLineList.Count - 1
                fileLineList(i) &= "," & CStr(averageIntensity)
            Next
        Next

        fileLineList.Insert(0, headerLine)

        Try
            SaveFile(normalizationDataFile, fileLineList)
        Catch ex As Exception
            Return False
        End Try

        Return True
    End Function

    ''' <summary>
    ''' Finds a directory with the given prefix.
    ''' </summary>
    ''' <param name="prefix">The prefix to use.</param>
    ''' <param name="inputImagesDir">The directory to look in.</param>
    ''' <returns>The path to a directory matching the prefix.</returns>
    Private Shared Function GetDirectoryGivenPrefix(ByVal prefix As String, ByVal inputImagesDir As String) As String
        Dim dirList As ReadOnlyCollection(Of String) = My.Computer.FileSystem.GetDirectories(inputImagesDir)

        For Each dir As String In dirList
            If GetPathElementName(dir).StartsWith(prefix) Then
                Return dir
            End If
        Next

        Throw New IOException("No directories were found with the prefix " & prefix & " in the directory " & inputImagesDir)
    End Function

    ''' <summary>
    ''' Returns the name of the final element (file or directory) from a path.
    ''' </summary>
    ''' <param name="fullPath">Path string containing the element.</param>
    ''' <returns>The name of the last element in the path.</returns>
    Friend Shared Function GetPathElementName(ByVal fullPath As String) As String

        ' If the path has a trailing separator character, remove it.
        If fullPath.LastIndexOf(Path.DirectorySeparatorChar) = fullPath.Length - 1 Then
            fullPath = fullPath.Remove(fullPath.Length - 1)
        End If

        Return fullPath.Substring(fullPath.LastIndexOf(Path.DirectorySeparatorChar) + 1)
    End Function

    ''' <summary>
    ''' Read a text file from the specified location and load it into a list of lines.
    ''' </summary>
    ''' <param name="fileLocation">The path and file name of the file to be saved.</param>
    ''' <returns>A list of text lines from the file.</returns>
    Private Function LoadFile(ByVal fileLocation As String) As List(Of String)
        Dim openFileStream As New IO.FileStream(fileLocation, IO.FileMode.Open, IO.FileAccess.Read, IO.FileShare.Read)
        Dim openFileReader As New IO.StreamReader(openFileStream)
        Dim fileLineList As New List(Of String)

        Do
            fileLineList.Add(openFileReader.ReadLine)
        Loop Until openFileReader.EndOfStream

        openFileReader.Close()

        Return fileLineList
    End Function

    ''' <summary>
    ''' Save a file represented by a list of text lines to the specified path.
    ''' </summary>
    ''' <param name="fileLocation">The path and file name of the file to be saved.</param>
    ''' <param name="fileLineList">The list of text lines to be written to the file.</param>
    Private Sub SaveFile(ByVal fileLocation As String, ByVal fileLineList As List(Of String))
        Dim openFileStream As New IO.FileStream(fileLocation, IO.FileMode.Truncate, IO.FileAccess.Write, IO.FileShare.None)
        Dim openFileWriter As New IO.StreamWriter(openFileStream)

        For Each line As String In fileLineList
            openFileWriter.WriteLine(line)
        Next

        openFileWriter.Close()
    End Sub
#End Region

    Private Sub PrematureStop(Optional ByVal message As String = "")
        ' Report an error to the UI and release the worker thread.
        errorFound = True
        errorMessage = message
        workerWaitHandle.Set()
    End Sub

    ''' <summary>
    ''' Every time CellProfiler writes a line of data to the console, which it doews via the error stream, write that out to a file.
    ''' </summary>
    ''' <param name="sender">The process that generated the event.</param>
    ''' <param name="e">The data sent by the process.</param>
    Private Sub cellProfilerProcess_ErrorDataReceived(sender As Object, e As DataReceivedEventArgs) Handles cellProfilerProcess.ErrorDataReceived
        Try
            errorStreamWriter.WriteLine(e.Data)
        Catch ex As Exception
            ' It's okay, we probably closed the error writer.
        End Try
    End Sub

End Class
