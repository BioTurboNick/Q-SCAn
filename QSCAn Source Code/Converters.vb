Imports System.Text

Namespace Converters
    ''' <summary>
    ''' Converts an array of Boolean values, in principle performing a NOR operation on them. All inputs must be False to output a value of True.
    ''' Intended to determine whether all of a number of validators have no errors so that a control can be disabled if there are errors.
    ''' </summary>
    Friend NotInheritable Class PassValidationConverter
        Implements IMultiValueConverter

        Friend Function Convert(values() As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IMultiValueConverter.Convert
            For Each value In values
                If value Is DependencyProperty.UnsetValue Then Return False
            Next

            For Each value In values
                If CBool(value) Then Return False
            Next

            Return True
        End Function

        Friend Function ConvertBack(value As Object, targetTypes() As Type, parameter As Object, culture As Globalization.CultureInfo) As Object() Implements IMultiValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Determines whether the Python path is needed or not.
    ''' </summary>
    Friend NotInheritable Class PythonNeededConverter
        Implements IValueConverter

        Public Function Convert(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.Convert
            If value Is DependencyProperty.UnsetValue Then Return False

            Dim cellProfilerPath As String = CStr(value)

            If cellProfilerPath.EndsWith(".py") Then
                Return True
            Else
                Return False
            End If
        End Function

        Public Function ConvertBack(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Converts a Boolean value to its inverse.
    ''' </summary>
    Friend NotInheritable Class InvertBooleanConverter
        Implements IValueConverter

        Public Function Convert(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.Convert
            If value Is DependencyProperty.UnsetValue Then Return False

            Return Not CBool(value)
        End Function

        Public Function ConvertBack(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Converts a MetadataElement into the string representation for it.
    ''' </summary>
    Friend NotInheritable Class MetadataFieldToStringConverter
        Implements IValueConverter

        Friend Function Convert(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.Convert
            If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return ""

            Dim field As MetadataElement = DirectCast(value, MetadataElement)

            Dim fieldString As String = ""

            Select Case field.MetadataType
                Case MetadataElementTypes.Field
                    Dim fieldBuilder As New StringBuilder()
                    fieldBuilder.Append("(?P<")
                    fieldBuilder.Append(field.FieldName)
                    fieldBuilder.Append(">")
                    fieldBuilder.Append(field.MatchExpression)
                    fieldBuilder.Append(")")
                    fieldString = fieldBuilder.ToString()
                Case MetadataElementTypes.Spacer
                    fieldString = field.MatchExpression
            End Select

            Return fieldString
        End Function

        Friend Function ConvertBack(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Converts to and from friendly representations of standard Regular Expression selectors.
    ''' </summary>
    Friend NotInheritable Class MatchExpressionConverter
        Implements IValueConverter

        Friend Function Convert(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.Convert
            If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return ""

            Select Case CStr(value)
                Case ".*"
                    Return "MatchAll"
                Case "\S*", "[^ \t\r\n\v\f]*"
                    Return "MatchNonSpace"
                Case "\w*", "[A-Za-z0-9_]*"
                    Return "MatchAlphanumeric"
                Case "[A-Za-z]*"
                    Return "MatchLetters"
                Case "\d*", "[0-9]*"
                    Return "MatchNumbers"
                Case Else
                    Return ""
            End Select
        End Function

        Friend Function ConvertBack(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.ConvertBack
            If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return ""

            Select Case CStr(value)
                Case "MatchAll"
                    Return ".*"
                Case "MatchNonSpace"
                    Return "\S*"
                Case "MatchAlphanumeric"
                    Return "\w*"
                Case "MatchLetters"
                    Return "[A-Za-z]*"
                Case "MatchNumbers"
                    Return "\d*"
                Case Else
                    Return ""
            End Select
        End Function
    End Class

    ''' <summary>
    ''' Compute whether a control should be visible or not based on the type of metadata element it represents.
    ''' </summary>
    Friend NotInheritable Class MetadataTypeVisibilityConverter
        Implements IValueConverter

        Friend Function Convert(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.Convert
            If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return ""

            Dim type As MetadataElementTypes = DirectCast(value, MetadataElementTypes)
            Dim invert As Boolean = CBool(parameter)

            If (type = MetadataElementTypes.Spacer AndAlso Not invert) OrElse (type = MetadataElementTypes.Field AndAlso invert) Then
                Return Visibility.Visible
            Else
                Return Visibility.Collapsed
            End If
        End Function

        Friend Function ConvertBack(value As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Compute whether the move up or move down controls should be enabled for this object. The parameter inverts the behavior for each of the controls.
    ''' </summary>
    Friend NotInheritable Class MoveEnabledConverter
        Implements IMultiValueConverter

        Friend Function Convert(values() As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IMultiValueConverter.Convert
            For Each value As Object In values
                If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return False
            Next

            Dim element As MetadataElement = DirectCast(values(0), MetadataElement)
            Dim builder As MetadataBuilder = DirectCast(values(1), MetadataBuilder)
            Dim invert As Boolean = CBool(parameter)

            If builder.IndexOf(element) = 0 OrElse (builder.IndexOf(element) = 1 AndAlso Not invert) OrElse (builder.IndexOf(element) = builder.Count - 1 AndAlso invert) Then
                Return False
            Else
                Return True
            End If

        End Function

        Friend Function ConvertBack(value As Object, targetTypes() As Type, parameter As Object, culture As Globalization.CultureInfo) As Object() Implements IMultiValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Disable the remove item control for the first item.
    ''' </summary>
    Friend NotInheritable Class RemoveEnabledConverter
        Implements IMultiValueConverter

        Friend Function Convert(values() As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IMultiValueConverter.Convert
            For Each value As Object In values
                If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return False
            Next

            Dim element As MetadataElement = DirectCast(values(0), MetadataElement)
            Dim builder As MetadataBuilder = DirectCast(values(1), MetadataBuilder)

            If builder.IndexOf(element) <= 0 Then
                Return False
            Else
                Return True
            End If
        End Function

        Friend Function ConvertBack(value As Object, targetTypes() As Type, parameter As Object, culture As Globalization.CultureInfo) As Object() Implements IMultiValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class

    ''' <summary>
    ''' Disable the ability to edit the fields for the first field.
    ''' </summary>
    Friend NotInheritable Class FirstItemDisabledConverter
        Implements IMultiValueConverter

        Friend Function Convert(values() As Object, targetType As Type, parameter As Object, culture As Globalization.CultureInfo) As Object Implements IMultiValueConverter.Convert
            For Each value As Object In values
                If value Is DependencyProperty.UnsetValue OrElse value Is Nothing Then Return False
            Next

            Dim element As MetadataElement = DirectCast(values(0), MetadataElement)
            Dim builder As MetadataBuilder = DirectCast(values(1), MetadataBuilder)

            Dim index As Integer = builder.IndexOf(element)

            If index = 0 Then
                Return False
            Else
                Return True
            End If
        End Function

        Friend Function ConvertBack(value As Object, targetTypes() As Type, parameter As Object, culture As Globalization.CultureInfo) As Object() Implements IMultiValueConverter.ConvertBack
            Throw New NotImplementedException
        End Function
    End Class
End Namespace