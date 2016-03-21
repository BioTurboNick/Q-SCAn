Imports System.Collections.ObjectModel
Imports System.Collections.Specialized
Imports System.ComponentModel
Imports System.Text

Friend NotInheritable Class MetadataBuilder
    Inherits ObservableCollection(Of MetadataElement)

    ''' <summary>
    ''' Trigger CollectionChanged so that items can notify any databound controls are properly updated.
    ''' </summary>
    Friend Sub OnItemPropertyChanged()
        OnCollectionChanged(New NotifyCollectionChangedEventArgs(NotifyCollectionChangedAction.Reset))
    End Sub

    ''' <summary>
    ''' Create a new MetadataBuilder object by parsing a metadata string.
    ''' </summary>
    ''' <param name="metadata">String containing the metadata expression.</param>
    ''' <returns>MetadataBuilder object containing a collection of ordered elements.</returns>
    Friend Shared Function Create(ByVal metadata As String) As MetadataBuilder
        Dim builder As New MetadataBuilder

        If metadata.IndexOf("(?P<") > 0 Then
            ' Metadata fields detected. Loop through the string to find and extract them.
            ' Example for first round: *.\\Strain (?P<Strain>.*) - (?P<Field>.*).lsm
            Do
                Dim index As Integer = metadata.IndexOf("(?P<")
                Dim prefix As String = metadata.Remove(index) ' "*.\\Strain "

                If prefix <> "" Then
                    builder.Add(New MetadataElement(MetadataElementTypes.Spacer, Nothing, prefix, builder))
                End If

                metadata = metadata.Substring(index + 4) ' "Strain>.*) - (?P<Field>.*).lsm
                index = metadata.IndexOf(">")
                Dim field As String = metadata.Remove(index) ' "Strain"
                metadata = metadata.Substring(index + 1) ' ".*) - (?P<Field>.*).lsm"
                index = metadata.IndexOf(")")
                Dim expression As String = metadata.Remove(index) ' ".*"

                builder.Add(New MetadataElement(MetadataElementTypes.Field, field, expression, builder))
                If metadata.Length > index + 1 Then
                    metadata = metadata.Substring(index + 1)
                End If

            Loop Until metadata.Length = 0 OrElse metadata.IndexOf("(?P<") < 0

            If metadata.Length > 0 Then
                builder.Add(New MetadataElement(MetadataElementTypes.Spacer, Nothing, metadata, builder))
            End If
        End If

        Return builder
    End Function

    ''' <summary>
    ''' Convert the MetadataBuilder object back into its string representation
    ''' </summary>
    ''' <returns></returns>
    ''' <remarks></remarks>
    Public Overrides Function ToString() As String
        Dim metadataStringBuilder As New StringBuilder()

        For Each element As MetadataElement In Me.Items
            Select Case element.MetadataType
                Case MetadataElementTypes.Field
                    metadataStringBuilder.Append("(?P<")
                    metadataStringBuilder.Append(element.FieldName)
                    metadataStringBuilder.Append(">")
                    metadataStringBuilder.Append(element.MatchExpression)
                    metadataStringBuilder.Append(")")
                Case MetadataElementTypes.Spacer
                    metadataStringBuilder.Append(element.MatchExpression)
            End Select
        Next

        Return metadataStringBuilder.ToString()
    End Function
End Class

Friend NotInheritable Class MetadataElement
    Implements INotifyPropertyChanged

    Dim metadataTypePrivate As MetadataElementTypes
    Dim fieldNamePrivate As String
    Dim matchExpressionPrivate As String
    Dim parent As New MetadataBuilder ' Holds the parent collection so that its CollectionChanged event can be raised.

    Public Property MetadataType As MetadataElementTypes
        Get
            Return metadataTypePrivate
        End Get
        Set(value As MetadataElementTypes)
            If metadataTypePrivate <> value Then
                metadataTypePrivate = value
                NotifyPropertyChanged("MetadataType")
            End If
        End Set
    End Property

    Public Property FieldName As String
        Get
            Return fieldNamePrivate
        End Get
        Set(value As String)
            If fieldNamePrivate <> value Then
                fieldNamePrivate = value
                NotifyPropertyChanged("FieldName")
            End If
        End Set
    End Property

    Public Property MatchExpression As String
        Get
            Return matchExpressionPrivate
        End Get
        Set(value As String)
            If matchExpressionPrivate <> value Then
                matchExpressionPrivate = value
                NotifyPropertyChanged("MatchExpression")
            End If
        End Set
    End Property

    Friend Sub New(ByVal builder As MetadataBuilder)
        parent = builder
    End Sub

    Friend Sub New(ByVal type As MetadataElementTypes, ByVal field As String, ByVal expression As String, ByVal builder As MetadataBuilder)
        metadataTypePrivate = type
        If type = MetadataElementTypes.Field Then
            If Not String.IsNullOrWhiteSpace(field) Then
                fieldNamePrivate = field
            Else
                Throw New ArgumentException("The Field type requires a field name to be set.")
            End If
        End If
        matchExpressionPrivate = expression
        parent = builder
    End Sub

    Private Sub NotifyPropertyChanged(ByVal propertyName As String)
        RaiseEvent PropertyChanged(Me, New PropertyChangedEventArgs(propertyName))
        parent.OnItemPropertyChanged() ' Notify parent collection that an item has changed.
    End Sub

    Friend Event PropertyChanged(sender As Object, e As PropertyChangedEventArgs) Implements INotifyPropertyChanged.PropertyChanged
End Class

Enum MetadataElementTypes As Integer
    Field
    Spacer
End Enum