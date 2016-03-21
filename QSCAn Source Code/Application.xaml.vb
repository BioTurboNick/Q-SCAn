Imports System.Reflection

Public Class Application
    ' Application-level events, such as Startup, Exit, and DispatcherUnhandledException
    ' can be handled in this file.
    Const DefaultImageJPath_WOW64 As String = "C:\Program Files (x86)\ImageJ\imagej.exe"
    Const DefaultImageJPath As String = "C:\Program Files\ImageJ\imagej.exe"

    Const DefaultCellProfilerPath_WOW64 As String = "C:\Program Files (x86)\CellProfiler\cellprofiler.exe"
    Const DefaultCellProfilerPath As String = "C:\Program Files\CellProfiler\cellprofiler.exe"

    Friend Sub New()
        ToolTipService.ShowDurationProperty.OverrideMetadata(GetType(DependencyObject), New FrameworkPropertyMetadata(Int32.MaxValue))
        ToolTipService.InitialShowDelayProperty.OverrideMetadata(GetType(DependencyObject), New FrameworkPropertyMetadata(0))
    End Sub

    Private Sub Application_Startup(ByVal sender As Object, ByVal e As StartupEventArgs) Handles Me.Startup
        ' Find ImageJ and CellProfiler

        ' If ImageJ path is unset or the given file isn't found, try looking again:
        Dim checkImageJPath As Boolean
        If My.Settings.ImageJPath = "" OrElse Not My.Computer.FileSystem.FileExists(My.Settings.ImageJPath) Then checkImageJPath = True

        If checkImageJPath Then
            If My.Computer.FileSystem.FileExists(DefaultImageJPath) Then
                My.Settings.ImageJPath = DefaultImageJPath
                checkImageJPath = False
            ElseIf My.Computer.FileSystem.FileExists(DefaultImageJPath_WOW64) Then
                My.Settings.ImageJPath = DefaultImageJPath_WOW64
                checkImageJPath = False
            End If

            If checkImageJPath Then
                MessageBox.Show("Can't find the ImageJ executable. ImageJ may not have been installed and/or is in an unusual location. You may provide it manually in the Setup dialog, or re-run this program after installing ImageJ.", "Error")
            End If
        End If

        ' If CellProfiler path is unset or the given file isn't found, try looking again:
        Dim checkCellProfilerPath As Boolean
        If My.Settings.CellProfilerPath = "" OrElse Not My.Computer.FileSystem.FileExists(My.Settings.CellProfilerPath) Then checkCellProfilerPath = True

        If checkCellProfilerPath Then
            If My.Computer.FileSystem.FileExists(DefaultCellProfilerPath) Then
                My.Settings.CellProfilerPath = DefaultCellProfilerPath
                checkCellProfilerPath = False
            ElseIf My.Computer.FileSystem.FileExists(DefaultCellProfilerPath_WOW64) Then
                My.Settings.CellProfilerPath = DefaultCellProfilerPath_WOW64
                checkCellProfilerPath = False
            End If

            If checkCellProfilerPath Then
                MessageBox.Show("Can't find the CellProfiler executable. CellProfiler may not have been installed and/or is in an unusual location. You may provide it manually in the Setup dialog, or re-run this program after installing CellProfiler. If you are using the Python developer version, please specify its location manually.", "Error")
            End If
        End If

        ' If CellProfiler has been found, check for the Plugins path
        If Not checkCellProfilerPath Then
            ' If the Plugins path for CellProfiler is unset or the given path doesn't exist, try looking again:
            Dim checkCellProfilerPluginsPath As Boolean
            If My.Settings.CellProfilerPluginsPath = "" OrElse Not My.Computer.FileSystem.DirectoryExists(My.Settings.CellProfilerPluginsPath) Then checkCellProfilerPluginsPath = True

            If checkCellProfilerPluginsPath Then
                Try
                    Dim pathString As String = CStr(My.Computer.Registry.CurrentUser.OpenSubKey("Software").OpenSubKey("CellProfilerLocal.cfg").GetValue("PluginDirectory"))

                    ' CellProfiler tends to store the path with multiple escaped "\" characters
                    Do While pathString.Contains("\\")
                        pathString = pathString.Replace("\\", "\")
                    Loop

                    My.Settings.CellProfilerPluginsPath = pathString
                Catch ex As Exception
                    MessageBox.Show("Can't find the CellProfiler plugins path in the registry. CellProfiler may not have been installed and/or run for the first time. Reopen this program after doing so, or you may provide it manually in the Setup dialog.", "Error")
                End Try
            End If
        End If

        MySettings.Default.Save()

        PreCompileAllMethods()
    End Sub

    Private Sub PreCompileAllMethods()
        For Each typeItem As Type In Assembly.GetExecutingAssembly().GetTypes()
            For Each methodItem As MethodInfo In typeItem.GetMethods(BindingFlags.DeclaredOnly Or BindingFlags.NonPublic Or BindingFlags.Public Or BindingFlags.Instance Or BindingFlags.Static)
                If Not (methodItem.IsAbstract OrElse methodItem.ContainsGenericParameters) Then
                    ' Not an abstract method (can't compile those)
                    System.Runtime.CompilerServices.RuntimeHelpers.PrepareMethod(methodItem.MethodHandle)
                End If
            Next
        Next
    End Sub
End Class
