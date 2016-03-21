Imports System.ComponentModel
Imports System.IO
Imports System.Threading
Imports System.Windows.Interop
Imports System.Windows.Shell
Imports Microsoft.Win32

Public Class MainWindow
    Implements IDisposable

    Dim WithEvents QSCAnWorker As QSCAnBackgroundWorker
    Dim currentOutputDir As String
    Dim windowHelper As WindowInteropHelper ' Pointer to this window for use with native methods.
    Dim waitingForInput As Boolean
    Dim fileExtension As String

    Public Shared ReadOnly TimeElapsedProperty As DependencyProperty = DependencyProperty.Register("TimeElapsed", GetType(TimeSpan), GetType(MainWindow), New PropertyMetadata(New TimeSpan))

    Public Property TimeElapsed As TimeSpan
        Get
            Return DirectCast(GetValue(TimeElapsedProperty), TimeSpan)
        End Get

        Private Set(ByVal value As TimeSpan)
            SetValue(TimeElapsedProperty, value)
        End Set
    End Property

    Private Sub MainWindow_Initialized(ByVal sender As Object, ByVal e As EventArgs) Handles Me.Initialized
        Me.TaskbarItemInfo = New TaskbarItemInfo
        windowHelper = New WindowInteropHelper(Me)
    End Sub

#Region "Control Button Event Handlers"
    Private Sub SetupButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles SetupButton.Click
        Dim setupWindow As New SetupWindow
        setupWindow.Owner = Me
        If setupWindow.ShowDialog() Then
            ResetDisplay()
        End If
    End Sub

    Private Sub RunButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles RunButton.Click
        ResetDisplay()

        Dim sourceImageDir As String = CStr(DataContext)

        Try
            If Not ValidatePaths() Then
                Exit Sub
            End If

            If sourceImageDir IsNot Nothing Then
                If sourceImageDir.IndexOfAny(Path.GetInvalidPathChars()) >= 0 OrElse Not My.Computer.FileSystem.DirectoryExists(sourceImageDir) Then
                    MessageBox.Show("The given path is invalid or doesn't exist.", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                    Exit Sub
                End If
            Else
                MessageBox.Show("Please specify an image source directory.", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Exit Sub
            End If

            currentOutputDir = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & QSCAnBackgroundWorker.GetPathElementName(CStr(DataContext)) & My.Settings.AnalysisSuffix

            ' Check output directory. If it contains files, warn user and ask if they would like to overwriter them.
            If My.Computer.FileSystem.DirectoryExists(currentOutputDir) Then
                If My.Computer.FileSystem.GetDirectories(currentOutputDir).Count > 0 Then
                    Dim result As MessageBoxResult = MessageBox.Show("There are already files in the output directory " & currentOutputDir & ". Would you like to delete them?", "Error", MessageBoxButton.YesNo, MessageBoxImage.Question, MessageBoxResult.No)

                    If result = MessageBoxResult.Yes Then
                        DeleteOutputDirectory()
                    Else
                        Exit Sub
                    End If
                End If
            End If

            My.Computer.FileSystem.CreateDirectory(currentOutputDir)
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
        End Try

        RunButton.Visibility = Windows.Visibility.Hidden
        PauseButton.Visibility = Windows.Visibility.Visible
        StopButton.IsEnabled = True
        SetupButton.IsEnabled = False
        SourceFolderButton.IsEnabled = False
        SourceFolderTextBox.IsEnabled = False
        ViewReadmeButton.Visibility = Windows.Visibility.Hidden
        ActivityIndicator.Visibility = Windows.Visibility.Visible
        Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Normal

        QSCAnWorker = New QSCAnBackgroundWorker
        QSCAnWorker.RunWorkerAsync(Tuple.Create(sourceImageDir, currentOutputDir, fileExtension))
        NativeMethods.SetSleeplessState(True)
    End Sub

    Private Sub PauseButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles PauseButton.Click
        QSCAnWorker.RequestPauseAsync()
        PauseButton.Visibility = Windows.Visibility.Hidden
        ResumeButton.Visibility = Windows.Visibility.Visible
        ActivityIndicator.IsIndeterminate = False
        Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Paused
    End Sub

    Private Sub ResumeButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles ResumeButton.Click
        QSCAnWorker.RequestResumeAsync()
        PauseButton.Visibility = Windows.Visibility.Visible
        ResumeButton.Visibility = Windows.Visibility.Hidden
        ActivityIndicator.IsIndeterminate = True
        Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Normal
    End Sub

    Private Sub StopButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles StopButton.Click
        QSCAnWorker.RequestCancelAsync()
    End Sub

    Private Sub SourceFolderButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles SourceFolderButton.Click
        Try
            Dim ofd As New OpenFileDialog
            If My.Settings.SourceImageRootPath = "" OrElse Not My.Computer.FileSystem.DirectoryExists(My.Settings.SourceImageRootPath) Then
                ofd.InitialDirectory = My.Computer.FileSystem.CurrentDirectory
            Else
                ofd.InitialDirectory = My.Settings.SourceImageRootPath
            End If
            ofd.Title = "Select one of the image files in the source directory"

            If ofd.ShowDialog() Then
                If Not CStr(DataContext) = My.Computer.FileSystem.GetParentPath(ofd.FileName) Then
                    DataContext = My.Computer.FileSystem.GetParentPath(ofd.FileName)
                    ResetDisplay()
                    fileExtension = My.Computer.FileSystem.GetFileInfo(ofd.FileName).Extension
                End If
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
        End Try
    End Sub

    Private Sub ClearFilesButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles ClearFilesButton.Click
        If DeleteOutputDirectory() Then
            ClearFilesButton.IsEnabled = False
        End If
    End Sub

    Private Sub ViewReadmeButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles ViewReadmeButton.Click
        Process.Start("explorer.exe", My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & "README.txt")
    End Sub

    Private Sub ViewFilesButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles ViewFilesButton.Click
        Process.Start("explorer.exe", currentOutputDir)
    End Sub

    Private Sub OpenCPLogFileButton_Clicked(ByVal sneder As Object, ByVal e As RoutedEventArgs) Handles OpenLogButton.Click
        Process.Start(My.Settings.CellProfilerLogFileName)
    End Sub
#End Region

#Region "Background Worker Event Handlers"
    ''' <summary>
    ''' Handle progress messages sent from the worker.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub QSCAnWorker_ProgressChanged(sender As Object, e As ProgressChangedEventArgs) Handles QSCAnWorker.ProgressChanged
        Select Case e.ProgressPercentage
            Case Is <= 7
                ' Normal progress

                If waitingForInput Then
                    ' Clear any conditions set when input was requested

                    NativeMethods.FlashWindowStop(windowHelper)
                    Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Normal
                    ActivityIndicator.IsIndeterminate = True
                    PauseButton.IsEnabled = True
                    StopButton.IsEnabled = True
                    OpenLogButton.Visibility = Windows.Visibility.Hidden
                End If

                Select Case e.ProgressPercentage
                    Case 1
                        Step1Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 1 / 8
                    Case 2
                        Step2Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 2 / 8
                    Case 3
                        Step3Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 3 / 8
                    Case 4
                        Step4Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 4 / 8
                    Case 5
                        Step5Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 5 / 8
                    Case 6
                        Step6Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 6 / 8
                    Case 7
                        Step7Text.Foreground = Brushes.Black
                        Me.TaskbarItemInfo.ProgressValue = 7 / 8
                End Select

            Case 50
                ' Worker needs user input

                waitingForInput = True
                NativeMethods.FlashWindow(windowHelper)
                Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Paused
                ActivityIndicator.IsIndeterminate = False
                PauseButton.IsEnabled = False
                StopButton.IsEnabled = False
                OpenLogButton.Visibility = Windows.Visibility.Visible
        End Select
    End Sub

    ''' <summary>
    ''' Handle events to be performed after the worker terminates.
    ''' </summary>
    ''' <param name="sender"></param>
    ''' <param name="e"></param>
    Private Sub QSCAnWorker_RunWorkerCompleted(sender As Object, e As RunWorkerCompletedEventArgs) Handles QSCAnWorker.RunWorkerCompleted
        RunButton.Visibility = Windows.Visibility.Visible
        PauseButton.Visibility = Windows.Visibility.Hidden
        ResumeButton.Visibility = Windows.Visibility.Hidden
        StopButton.IsEnabled = False
        SetupButton.IsEnabled = True
        SourceFolderButton.IsEnabled = True
        SourceFolderTextBox.IsEnabled = True
        ActivityIndicator.Visibility = Windows.Visibility.Hidden

        Dim isCancelled As Boolean = e.Cancelled

        If Not isCancelled Then
            ' Result can only be accessed if the worker wasn't cancelled.

            Dim result As Tuple(Of Boolean, Object) = DirectCast(e.Result, Tuple(Of Boolean, Object))

            Dim isSuccessful As Boolean = result.Item1

            If isSuccessful Then
                ' Completed successfully

                StatusText.Text = "Completed!"
                StatusText.Foreground = Brushes.Green

                TimeElapsed = DirectCast(result.Item2, TimeSpan)
                TimeElapsedText.Visibility = Windows.Visibility.Visible
                ViewFilesButton.Visibility = Windows.Visibility.Visible

                Me.TaskbarItemInfo.ProgressValue = 1

                If My.Settings.BeepOnComplete Then
                    My.Computer.Audio.PlaySystemSound(System.Media.SystemSounds.Beep)
                End If

                NativeMethods.FlashWindow(windowHelper)
            Else
                ' Run ended due to an error

                StatusText.Text = "Error"
                StatusText.Foreground = Brushes.Red

                Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.Error

                Dim message As String = CStr(result.Item2)

                If message <> "" Then
                    MessageBox.Show(message, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                End If

                ClearFilesButton.IsEnabled = True
                ClearFilesButton.Visibility = Windows.Visibility.Visible
            End If
        Else
            ' Run was cancelled

            StatusText.Text = "Cancelled"

            StatusText.Foreground = Brushes.Red

            ClearFilesButton.IsEnabled = True
            ClearFilesButton.Visibility = Windows.Visibility.Visible
        End If

        NativeMethods.SetSleeplessState(False)
    End Sub
#End Region

#Region "Routines"
    ''' <summary>
    ''' Reset the display to pre-run conditions.
    ''' </summary>
    Private Sub ResetDisplay()
        Step1Text.Foreground = Brushes.Gray
        Step2Text.Foreground = Brushes.Gray
        Step3Text.Foreground = Brushes.Gray
        Step4Text.Foreground = Brushes.Gray
        Step5Text.Foreground = Brushes.Gray
        Step6Text.Foreground = Brushes.Gray
        Step7Text.Foreground = Brushes.Gray

        Height = MinHeight

        ViewFilesButton.Visibility = Windows.Visibility.Hidden
        ClearFilesButton.Visibility = Windows.Visibility.Hidden
        OpenLogButton.Visibility = Windows.Visibility.Hidden
        TimeElapsedText.Visibility = Windows.Visibility.Hidden
        StatusText.Text = ""

        Me.TaskbarItemInfo.ProgressState = TaskbarItemProgressState.None
    End Sub


    ''' <summary>
    ''' Make sure there are no glaring problems with the settings.
    ''' </summary>
    ''' <returns>True if the settings appear valid, false if not.</returns>
    Private Function ValidatePaths() As Boolean
        With My.Settings
            If Not My.Computer.FileSystem.FileExists(.ImageJPath) Then
                MessageBox.Show("ImageJ does not exist at the location " & .ImageJPath & ".", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            If Not My.Computer.FileSystem.FileExists(.CellProfilerPath) Then
                MessageBox.Show("CellProfiler does not exist at the location " & .CellProfilerPath & ".", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            If .CellProfilerPath.EndsWith(".py") Then
                If Not My.Computer.FileSystem.FileExists(.PythonPath) Then
                    MessageBox.Show("Python does not exist at the location " & .PythonPath & ".", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                    Return False
                End If
            End If

            If Not My.Computer.FileSystem.DirectoryExists(.CellProfilerPluginsPath) Then
                MessageBox.Show("The CellProfiler plugins path does not exist at the location " & .CellProfilerPluginsPath & ".", "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            Dim imageJMacroPath As String = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .ImageJ_OpenAndExportChannelsFileName
            If Not My.Computer.FileSystem.FileExists(imageJMacroPath) Then
                MessageBox.Show("The Open And Export Channels ImageJ macro does not exist at the location " & imageJMacroPath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            imageJMacroPath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .ImageJ_CalculateMedianImageFileName
            If Not My.Computer.FileSystem.FileExists(imageJMacroPath) Then
                MessageBox.Show("The Calculate Median Image ImageJ macro does not exist at the location " & imageJMacroPath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            imageJMacroPath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .ImageJ_CalculateMedianImageTimeSeriesFileName
            If Not My.Computer.FileSystem.FileExists(imageJMacroPath) Then
                MessageBox.Show("The Calculate Median Image From Time Series ImageJ macro does not exist at the location " & imageJMacroPath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            Dim cellProfilerPipelinePath As String = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .CellProfiler_BackgroundCorrectionFileName
            If Not My.Computer.FileSystem.FileExists(cellProfilerPipelinePath) Then
                MessageBox.Show("The Background Correction CellProfiler pipeline does not exist at the location " & cellProfilerPipelinePath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            cellProfilerPipelinePath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .CellProfiler_IdentifyCellsFileName
            If Not My.Computer.FileSystem.FileExists(cellProfilerPipelinePath) Then
                MessageBox.Show("The Identify Cells CellProfiler pipeline does not exist at the location " & cellProfilerPipelinePath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            cellProfilerPipelinePath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .CellProfiler_MeasureImageIntensitiesFileName
            If Not My.Computer.FileSystem.FileExists(cellProfilerPipelinePath) Then
                MessageBox.Show("The Measure Image Intensities CellProfiler pipeline does not exist at the location " & cellProfilerPipelinePath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            cellProfilerPipelinePath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .CellProfiler_FilterCellsAndIdentifyCompartmentsFileName
            If Not My.Computer.FileSystem.FileExists(cellProfilerPipelinePath) Then
                MessageBox.Show("The Filter Cells and Identify Compartments CellProfiler pipeline does not exist at the location " & cellProfilerPipelinePath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If

            cellProfilerPipelinePath = My.Computer.FileSystem.CurrentDirectory & Path.DirectorySeparatorChar & .CellProfiler_CalculateLocalizationIndicesAndExportIntensitiesFileName
            If Not My.Computer.FileSystem.FileExists(cellProfilerPipelinePath) Then
                MessageBox.Show("The Calculate Localization Indices and Export Intensities CellProfiler pipeline does not exist at the location " & cellProfilerPipelinePath, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
                Return False
            End If
        End With

        Return True
    End Function

    ''' <summary>
    ''' Delete the current output directory.
    ''' </summary>
    Private Function DeleteOutputDirectory() As Boolean
        Try
            If My.Computer.FileSystem.DirectoryExists(currentOutputDir) Then
                Try
                    My.Computer.FileSystem.DeleteDirectory(currentOutputDir, FileIO.DeleteDirectoryOption.DeleteAllContents)
                Catch ex As IOException
                    ' This often catches and doesn't successfully delete the files. Sleep the thread and try again.
                    Thread.Sleep(0)
                    My.Computer.FileSystem.DeleteDirectory(currentOutputDir, FileIO.DeleteDirectoryOption.DeleteAllContents)
                End Try
            End If

            ' Wait up to 10 seconds to make sure it has finished deleting.
            Do
                Dim totalWaited As Integer
                Thread.Sleep(100)
                totalWaited += 100

                If totalWaited > 10000 Then
                    Exit Do
                End If
            Loop Until Not My.Computer.FileSystem.DirectoryExists(currentOutputDir)
            Return True
        Catch ex As Exception
            MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error)
            Return False
        End Try
    End Function
#End Region

#Region "IDisposable Support"
    Private disposedValue As Boolean ' To detect redundant calls

    ' IDisposable
    Protected Overridable Sub Dispose(disposing As Boolean)
        If Not Me.disposedValue Then
            If disposing Then
                QSCAnWorker.Dispose()
            End If
        End If
        Me.disposedValue = True
    End Sub

    ' This code added by Visual Basic to correctly implement the disposable pattern.
    Public Sub Dispose() Implements IDisposable.Dispose
        ' Do not change this code.  Put cleanup code in Dispose(disposing As Boolean) above.
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
#End Region

End Class
