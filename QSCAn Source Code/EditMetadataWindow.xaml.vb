Imports System.Collections
Imports System.Collections.Specialized

Public Class EditMetadataWindow
    Friend Sub New()
        ' This call is required by the designer.
        InitializeComponent()

        ' Parse the metadata string and assign it to the DataContext
        Dim builder As MetadataBuilder = MetadataBuilder.Create(MySettings.Default.Metadata)
        DataContext = builder
    End Sub

    Shared Sub New()
        DataContextProperty.OverrideMetadata(GetType(EditMetadataWindow), New FrameworkPropertyMetadata(New MetadataBuilder, AddressOf OnDataContextChanged))
    End Sub

    Public Shared Sub OnDataContextChanged(d As DependencyObject, e As DependencyPropertyChangedEventArgs)
        DirectCast(d, EditMetadataWindow).AdjustHeight(DirectCast(e.NewValue, MetadataBuilder).Count)
    End Sub

    ''' <summary>
    ''' Calculate the height of the window. Unfortunately I could only get this to trigger the first time, so the height is adjusted manually when other items are added or removed.
    ''' </summary>
    ''' <param name="elementsCount">The number of elements to be displayed.</param>
    Private Sub AdjustHeight(ByVal elementsCount As Integer)
        Dim maxWindowHeight As Double = SystemParameters.FullPrimaryScreenHeight

        Dim requestedheight As Double = elementsCount * 41 + 175

        Me.Height = Math.Min(requestedheight, maxWindowHeight)
    End Sub

#Region "Control Button Event Handlers"
    Private Sub AddButton_Click() Handles AddButton.Click
        Dim builder As MetadataBuilder = DirectCast(DataContext, MetadataBuilder)
        Dim element As MetadataElement = DirectCast(MetadataElementsListBox.SelectedItem, MetadataElement)

        Dim newElement = New MetadataElement(builder)
        builder.Add(newElement)
        MetadataElementsListBox.SelectedItem = newElement
    End Sub

    Private Sub RemoveButton_Click() Handles RemoveButton.Click
        Dim builder As MetadataBuilder = DirectCast(DataContext, MetadataBuilder)
        Dim element As MetadataElement = DirectCast(MetadataElementsListBox.SelectedItem, MetadataElement)

        builder.Remove(element)
    End Sub

    Private Sub MoveUpButton_Click() Handles MoveUpButton.Click
        Dim builder As MetadataBuilder = DirectCast(DataContext, MetadataBuilder)
        Dim element As MetadataElement = DirectCast(MetadataElementsListBox.SelectedItem, MetadataElement)

        Dim elementStartIndex As Integer = builder.IndexOf(element)

        builder.RemoveAt(elementStartIndex)
        builder.Insert(elementStartIndex - 1, element)

        MetadataElementsListBox.SelectedIndex = elementStartIndex - 1
    End Sub

    Private Sub MoveDownButton_Click() Handles MoveDownButton.Click
        Dim builder As MetadataBuilder = DirectCast(DataContext, MetadataBuilder)
        Dim element As MetadataElement = DirectCast(MetadataElementsListBox.SelectedItem, MetadataElement)

        Dim elementStartIndex As Integer = MetadataElementsListBox.Items.IndexOf(element)

        builder.RemoveAt(elementStartIndex)
        builder.Insert(elementStartIndex + 1, element)

        MetadataElementsListBox.SelectedIndex = elementStartIndex + 1
    End Sub

    Private Sub SaveButton_Click(sender As Object, e As RoutedEventArgs) Handles SaveButton.Click
        Dim builder As MetadataBuilder = DirectCast(DataContext, MetadataBuilder)

        For Each element As MetadataElement In builder
            If element.MetadataType = MetadataElementTypes.Spacer Then
                If element.MatchExpression = "" Then
                    MsgBox("All separators must have content.")
                    Exit Sub
                End If
            Else
                If element.FieldName = "" Then
                    MsgBox("All metadata fields require a name.")
                    Exit Sub
                End If
            End If
        Next

        Me.DialogResult = True
        Me.Close()
    End Sub

    Private Sub CancelButton_Click(sender As Object, e As RoutedEventArgs) Handles CancelButton.Click
        Me.Close()
    End Sub
#End Region
End Class