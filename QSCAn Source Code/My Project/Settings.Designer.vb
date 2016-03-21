﻿'------------------------------------------------------------------------------
' <auto-generated>
'     This code was generated by a tool.
'     Runtime Version:4.0.30319.34014
'
'     Changes to this file may cause incorrect behavior and will be lost if
'     the code is regenerated.
' </auto-generated>
'------------------------------------------------------------------------------

Option Strict On
Option Explicit On



<Global.System.Runtime.CompilerServices.CompilerGeneratedAttribute(),  _
 Global.System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.VisualStudio.Editors.SettingsDesigner.SettingsSingleFileGenerator", "12.0.0.0"),  _
 Global.System.ComponentModel.EditorBrowsableAttribute(Global.System.ComponentModel.EditorBrowsableState.Advanced)>  _
Partial Friend NotInheritable Class MySettings
    Inherits Global.System.Configuration.ApplicationSettingsBase
    
    Private Shared defaultInstance As MySettings = CType(Global.System.Configuration.ApplicationSettingsBase.Synchronized(New MySettings()),MySettings)
    
#Region "My.Settings Auto-Save Functionality"
#If _MyType = "WindowsForms" Then
    Private Shared addedHandler As Boolean

    Private Shared addedHandlerLockObject As New Object

    <Global.System.Diagnostics.DebuggerNonUserCodeAttribute(), Global.System.ComponentModel.EditorBrowsableAttribute(Global.System.ComponentModel.EditorBrowsableState.Advanced)> _
    Private Shared Sub AutoSaveSettings(ByVal sender As Global.System.Object, ByVal e As Global.System.EventArgs)
        If My.Application.SaveMySettingsOnExit Then
            My.Settings.Save()
        End If
    End Sub
#End If
#End Region
    
    Public Shared ReadOnly Property [Default]() As MySettings
        Get
            
#If _MyType = "WindowsForms" Then
               If Not addedHandler Then
                    SyncLock addedHandlerLockObject
                        If Not addedHandler Then
                            AddHandler My.Application.Shutdown, AddressOf AutoSaveSettings
                            addedHandler = True
                        End If
                    End SyncLock
                End If
#End If
            Return defaultInstance
        End Get
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("")>  _
    Public Property ImageJPath() As String
        Get
            Return CType(Me("ImageJPath"),String)
        End Get
        Set
            Me("ImageJPath") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("")>  _
    Public Property CellProfilerPath() As String
        Get
            Return CType(Me("CellProfilerPath"),String)
        End Get
        Set
            Me("CellProfilerPath") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("")>  _
    Public Property SourceImageRootPath() As String
        Get
            Return CType(Me("SourceImageRootPath"),String)
        End Get
        Set
            Me("SourceImageRootPath") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Brightfield Shading")>  _
    Public Property ShadingCorrectionPrefix() As String
        Get
            Return CType(Me("ShadingCorrectionPrefix"),String)
        End Get
        Set
            Me("ShadingCorrectionPrefix") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Dark Current")>  _
    Public Property DarkCurrentCorrectionPrefix() As String
        Get
            Return CType(Me("DarkCurrentCorrectionPrefix"),String)
        End Get
        Set
            Me("DarkCurrentCorrectionPrefix") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute(" Analysis")>  _
    Public Property AnalysisSuffix() As String
        Get
            Return CType(Me("AnalysisSuffix"),String)
        End Get
        Set
            Me("AnalysisSuffix") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Input Images")>  _
    Public Property InputImagesDirName() As String
        Get
            Return CType(Me("InputImagesDirName"),String)
        End Get
        Set
            Me("InputImagesDirName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Output Data")>  _
    Public Property OutputDataDirName() As String
        Get
            Return CType(Me("OutputDataDirName"),String)
        End Get
        Set
            Me("OutputDataDirName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("OpenAndExportChannels.ijm")>  _
    Public Property ImageJ_OpenAndExportChannelsFileName() As String
        Get
            Return CType(Me("ImageJ_OpenAndExportChannelsFileName"),String)
        End Get
        Set
            Me("ImageJ_OpenAndExportChannelsFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("CalculateMedianImage.ijm")>  _
    Public Property ImageJ_CalculateMedianImageFileName() As String
        Get
            Return CType(Me("ImageJ_CalculateMedianImageFileName"),String)
        End Get
        Set
            Me("ImageJ_CalculateMedianImageFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("0 - Background Correction.cp")>  _
    Public Property CellProfiler_BackgroundCorrectionFileName() As String
        Get
            Return CType(Me("CellProfiler_BackgroundCorrectionFileName"),String)
        End Get
        Set
            Me("CellProfiler_BackgroundCorrectionFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("1 - Identify Cells and Background.cp")>  _
    Public Property CellProfiler_IdentifyCellsFileName() As String
        Get
            Return CType(Me("CellProfiler_IdentifyCellsFileName"),String)
        End Get
        Set
            Me("CellProfiler_IdentifyCellsFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("2 - Measure Image Intensities and Finish Correction.cp")>  _
    Public Property CellProfiler_MeasureImageIntensitiesFileName() As String
        Get
            Return CType(Me("CellProfiler_MeasureImageIntensitiesFileName"),String)
        End Get
        Set
            Me("CellProfiler_MeasureImageIntensitiesFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("3 - Filter Cells and Identify Compartments.cp")>  _
    Public Property CellProfiler_FilterCellsAndIdentifyCompartmentsFileName() As String
        Get
            Return CType(Me("CellProfiler_FilterCellsAndIdentifyCompartmentsFileName"),String)
        End Get
        Set
            Me("CellProfiler_FilterCellsAndIdentifyCompartmentsFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("4 - Calculate Localization Index and Export Intensity Data.cp")>  _
    Public Property CellProfiler_CalculateLocalizationIndicesAndExportIntensitiesFileName() As String
        Get
            Return CType(Me("CellProfiler_CalculateLocalizationIndicesAndExportIntensitiesFileName"),String)
        End Get
        Set
            Me("CellProfiler_CalculateLocalizationIndicesAndExportIntensitiesFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("True")>  _
    Public Property BeepOnComplete() As Boolean
        Get
            Return CType(Me("BeepOnComplete"),Boolean)
        End Get
        Set
            Me("BeepOnComplete") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("False")>  _
    Public Property DarkCurrentIsTimeSeries() As Boolean
        Get
            Return CType(Me("DarkCurrentIsTimeSeries"),Boolean)
        End Get
        Set
            Me("DarkCurrentIsTimeSeries") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("CalculateMedianImageFromTimeSeries.ijm")>  _
    Public Property ImageJ_CalculateMedianImageTimeSeriesFileName() As String
        Get
            Return CType(Me("ImageJ_CalculateMedianImageTimeSeriesFileName"),String)
        End Get
        Set
            Me("ImageJ_CalculateMedianImageTimeSeriesFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("")>  _
    Public Property CellProfilerPluginsPath() As String
        Get
            Return CType(Me("CellProfilerPluginsPath"),String)
        End Get
        Set
            Me("CellProfilerPluginsPath") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("True")>  _
    Public Property KeepAwake() As Boolean
        Get
            Return CType(Me("KeepAwake"),Boolean)
        End Get
        Set
            Me("KeepAwake") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("True")>  _
    Public Property CheckPipelineSuccess() As Boolean
        Get
            Return CType(Me("CheckPipelineSuccess"),Boolean)
        End Get
        Set
            Me("CheckPipelineSuccess") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("1")>  _
    Public Property NumberOfOtherCompartments() As Integer
        Get
            Return CType(Me("NumberOfOtherCompartments"),Integer)
        End Get
        Set
            Me("NumberOfOtherCompartments") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute(".*\\(?P<Strain>.*) - (?P<Condition>.*) - Field (?P<Field>\S*).lsm")>  _
    Public Property Metadata() As String
        Get
            Return CType(Me("Metadata"),String)
        End Get
        Set
            Me("Metadata") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("3")>  _
    Public Property NumberOfFluorescenceChannels() As Integer
        Get
            Return CType(Me("NumberOfFluorescenceChannels"),Integer)
        End Get
        Set
            Me("NumberOfFluorescenceChannels") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("False")>  _
    Public Property SetMetadataManually() As Boolean
        Get
            Return CType(Me("SetMetadataManually"),Boolean)
        End Get
        Set
            Me("SetMetadataManually") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Within-Cell Image Intensities for Normalization.csv")>  _
    Public Property Output_NormalizationFileName() As String
        Get
            Return CType(Me("Output_NormalizationFileName"),String)
        End Get
        Set
            Me("Output_NormalizationFileName") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("Compartment Localization Data.csv")>  _
    Public Property Output_CompartmentLocalizationData() As String
        Get
            Return CType(Me("Output_CompartmentLocalizationData"),String)
        End Get
        Set
            Me("Output_CompartmentLocalizationData") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("False")>  _
    Public Property ShowCPActivity() As Boolean
        Get
            Return CType(Me("ShowCPActivity"),Boolean)
        End Get
        Set
            Me("ShowCPActivity") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("")>  _
    Public Property PythonPath() As String
        Get
            Return CType(Me("PythonPath"),String)
        End Get
        Set
            Me("PythonPath") = value
        End Set
    End Property
    
    <Global.System.Configuration.UserScopedSettingAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Configuration.DefaultSettingValueAttribute("QSCAn CellProfiler Log.txt")>  _
    Public Property CellProfilerLogFileName() As String
        Get
            Return CType(Me("CellProfilerLogFileName"),String)
        End Get
        Set
            Me("CellProfilerLogFileName") = value
        End Set
    End Property
End Class

Namespace My
    
    <Global.Microsoft.VisualBasic.HideModuleNameAttribute(),  _
     Global.System.Diagnostics.DebuggerNonUserCodeAttribute(),  _
     Global.System.Runtime.CompilerServices.CompilerGeneratedAttribute()>  _
    Friend Module MySettingsProperty
        
        <Global.System.ComponentModel.Design.HelpKeywordAttribute("My.Settings")>  _
        Friend ReadOnly Property Settings() As Global.QSCAn.MySettings
            Get
                Return Global.QSCAn.MySettings.Default
            End Get
        End Property
    End Module
End Namespace
