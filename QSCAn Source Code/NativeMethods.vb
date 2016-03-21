Imports System.Windows.Interop

Friend NotInheritable Class NativeMethods
#Region "SetExecutionState"
    ''' <summary>
    ''' Windows API call to tell the operating system whether this program needs to keep the computer running.
    ''' </summary>
    ''' <param name="flags"></param>
    Private Declare Auto Function SetThreadExecutionState Lib "kernel32.dll" (ByVal flags As EXECUTION_STATE) As UInteger

    ''' <summary>
    ''' Set whether the computer can sleep while the program is running.
    ''' </summary>
    ''' <param name="sleepless">Tell the computer whether it should stay awake.</param>
    Friend Shared Sub SetSleeplessState(ByVal sleepless As Boolean)
        Dim flags As EXECUTION_STATE

        If sleepless Then
            ' Performs an "or" operation on the two UIntegers, returning 0x80000001
            flags = EXECUTION_STATE.ES_CONTINUOUS Or EXECUTION_STATE.ES_SYSTEM_REQUIRED ' Stay awake until otherwise notified
        Else
            flags = EXECUTION_STATE.ES_CONTINUOUS ' Re-enable sleep
        End If

        SetThreadExecutionState(flags)
    End Sub

    Private Enum EXECUTION_STATE As UInteger
        ES_SYSTEM_REQUIRED = 1     ' 0x00000001, tells the computer it needs to stay awake
        ES_CONTINUOUS = 2147483648 ' 0x80000000, tells the computer to retain the setting until otherwise notified
    End Enum
#End Region

#Region "FlashWindowEx"
    ''' <summary>
    ''' Windows API call to tell the operating system to flash the window and taskbar icon.
    ''' </summary>
    ''' <param name="pwfi"></param>
    Private Declare Auto Function FlashWindowEx Lib "user32.dll" (ByRef pwfi As FLASHWINFO) As UInteger

    ''' <summary>
    ''' Send a message to Windows to get the user's attention by flashing the window and taskbar icon.
    ''' </summary>
    ''' <remarks></remarks>
    Friend Shared Sub FlashWindow(ByVal windowHelper As WindowInteropHelper)
        Dim flashInfo As FLASHWINFO
        flashInfo.cbSize = CUInt(Runtime.InteropServices.Marshal.SizeOf(flashInfo))
        flashInfo.hwind = windowHelper.Handle
        flashInfo.dwFlags = FLASHW.FLASHW_ALL Or FLASHW.FLASHW_TIMERNOFG
        flashInfo.uCount = UInteger.MaxValue
        flashInfo.dwTimeout = 0
        FlashWindowEx(flashInfo)
    End Sub

    ''' <summary>
    ''' Send a message to Windows to stop flashing the window
    ''' </summary>
    ''' <remarks></remarks>
    Friend Shared Sub FlashWindowStop(ByVal windowHelper As WindowInteropHelper)
        Dim flashInfo As FLASHWINFO
        flashInfo.cbSize = CUInt(Runtime.InteropServices.Marshal.SizeOf(flashInfo))
        flashInfo.hwind = windowHelper.Handle
        flashInfo.dwFlags = FLASHW.FLASHW_STOP
        flashInfo.uCount = UInteger.MaxValue
        flashInfo.dwTimeout = 0
        FlashWindowEx(flashInfo)
    End Sub

    Private Structure FLASHWINFO
        Public cbSize As UInteger
        Public hwind As IntPtr
        Public dwFlags As UInteger
        Public uCount As UInteger
        Public dwTimeout As UInteger
    End Structure

    Private Enum FLASHW As UInteger
        FLASHW_STOP = 0       ' 0x00000000, stop any current flashing
        FLASHW_ALL = 3        ' 0x00000003, flash the window caption and taskbar icon
        FLASHW_TIMERNOFG = 12 ' 0x00000012, flash continuously until user interaction stops it
    End Enum
#End Region

#Region "SuspendThread/ResumeThread"
    Private Declare Auto Function OpenThread Lib "kernel32.dll" (ByVal dwDesiredAccess As ThreadAccess, ByVal bInheritHandle As Boolean, ByVal dwThreadId As UInteger) As IntPtr

    Private Declare Auto Function SuspendThread Lib "kernel32.dll" (ByVal hThread As IntPtr) As UInteger

    Private Declare Auto Function ResumeThread Lib "kernel32.dll" (ByVal hThread As IntPtr) As UInteger

    Friend Shared Sub SuspendProcess(ByVal proc As Process)
        For Each thread As ProcessThread In proc.Threads
            Dim OpenThreadPointer As IntPtr = OpenThread(ThreadAccess.SUSPEND_RESUME, False, CUInt(thread.Id))

            If OpenThreadPointer = IntPtr.Zero Then
                Exit Sub
            End If

            SuspendThread(OpenThreadPointer)
        Next
    End Sub

    Friend Shared Sub ResumeProcess(ByVal proc As Process)
        For Each thread As ProcessThread In proc.Threads
            Dim OpenThreadPointer As IntPtr = OpenThread(ThreadAccess.SUSPEND_RESUME, False, CUInt(thread.Id))

            If OpenThreadPointer = IntPtr.Zero Then
                Exit Sub
            End If

            ResumeThread(OpenThreadPointer)
        Next
    End Sub

    Private Enum ThreadAccess As Integer
        SUSPEND_RESUME = 2 ' 0x0002, want access to suspend or resume the thread
    End Enum
#End Region
End Class
