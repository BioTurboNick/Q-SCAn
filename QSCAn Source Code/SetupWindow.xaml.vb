Imports System.Collections
Imports Microsoft.Win32

Public Class SetupWindow
    Private Sub SetupWindow_Closed() Handles Me.Closed
        If Not DialogResult Then
            ' Replace any changes to the settings.
            MySettings.Default.Reload()
        End If
    End Sub

    Private Sub SaveButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles SaveButton.Click
        With MySettings.Default
            ' Check that values which should be unique are unique. If they aren't, force the user to change them.

            If .ShadingCorrectionPrefix = .DarkCurrentCorrectionPrefix Then
                MessageBox.Show("The prefix for the dark current and shading correction image files must be unique.", "Error")
                Exit Sub
            End If

            If .InputImagesDirName = .OutputDataDirName Then
                MessageBox.Show("The input image and output data directory names must be unique.", "Error")
                Exit Sub
            End If
        End With

        MySettings.Default.Save()
        Me.DialogResult = True
        Me.Close()
    End Sub

    Private Sub CancelButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles CancelButton.Click
        Me.Close()
    End Sub

    Private Sub ResetButton_Clicked(ByVal sender As Object, ByVal e As RoutedEventArgs) Handles ResetButton.Click
        Dim resetConfirmed As MsgBoxResult = MsgBox("Are you sure you want to reset the settings to default?", MsgBoxStyle.YesNo, "Confirm Settings Reset")

        If resetConfirmed = MsgBoxResult.Yes Then
            MySettings.Default.Reset()
        End If
    End Sub

    Private Sub EditImageMetadataButton_Click(sender As Object, e As RoutedEventArgs) Handles EditImageMetadataButton.Click
        Dim editMetadataWindow As New EditMetadataWindow
        editMetadataWindow.Owner = Me
        If editMetadataWindow.ShowDialog() Then
            MySettings.Default.Metadata = DirectCast(editMetadataWindow.DataContext, MetadataBuilder).ToString()
        End If
    End Sub

    Private Sub ImageJPathButton_Click(sender As Object, e As RoutedEventArgs) Handles ImageJPathButton.Click
        MySettings.Default.ImageJPath = GetPath(MySettings.Default.ImageJPath, "Find the location of the ImageJ executable.")
    End Sub

    Private Sub CellProfilerPathButton_Click(sender As Object, e As RoutedEventArgs) Handles CellProfilerPathButton.Click
        MySettings.Default.CellProfilerPath = GetPath(MySettings.Default.CellProfilerPath, "Find the location of the CellProfiler Python script or executable.")
    End Sub

    Private Sub HelpButton_Click(sender As Object, e As RoutedEventArgs) Handles HelpButton.Click
        Process.Start("Readme.txt")
    End Sub

    Private Function GetPath(ByVal startPath As String, ByVal dialogTitle As String) As String
        Dim newPath As String = startPath

        Dim ofd As New OpenFileDialog
        If startPath = "" OrElse Not My.Computer.FileSystem.FileExists(startPath) Then
            ofd.InitialDirectory = My.Computer.FileSystem.CurrentDirectory
        Else
            ofd.InitialDirectory = My.Computer.FileSystem.GetParentPath(startPath)
        End If

        ofd.Title = dialogTitle

        Try
            If ofd.ShowDialog() Then
                newPath = ofd.FileName
            End If
        Catch ex As Exception
            MessageBox.Show(ex.Message)
        End Try

        Return newPath
    End Function

    Private Sub AdvancedExpander_Expanded(sender As Object, e As RoutedEventArgs)
        SettingsScrollViewer.VerticalScrollBarVisibility = ScrollBarVisibility.Visible
    End Sub

    Private Sub AdvancedExpander_Collapsed(sender As Object, e As RoutedEventArgs)
        SettingsScrollViewer.VerticalScrollBarVisibility = ScrollBarVisibility.Hidden
    End Sub
End Class