Namespace Validators
    ''' <summary>
    ''' Provides for validation on textboxes that should contain text.
    ''' </summary>
    Friend NotInheritable Class EmptyStringValidationRule
        Inherits ValidationRule

        Public Overrides Function Validate(value As Object, cultureInfo As Globalization.CultureInfo) As ValidationResult
            Dim result As ValidationResult

            Dim inputString As String = CStr(value)

            If inputString = String.Empty Then
                result = New ValidationResult(False, Nothing)
            Else
                result = New ValidationResult(True, Nothing)
            End If

            Return result
        End Function
    End Class

    ''' <summary>
    ''' Provides for validation on textboxes that should contain numbers only.
    ''' </summary>
    Friend NotInheritable Class IsNotNumericValidationRule
        Inherits ValidationRule

        Public Overrides Function Validate(value As Object, cultureInfo As Globalization.CultureInfo) As ValidationResult
            Dim result As ValidationResult

            Dim inputString As String = CStr(value)

            If Not IsNumeric(inputString) Then
                result = New ValidationResult(False, Nothing)
            Else
                result = New ValidationResult(True, Nothing)
            End If

            Return result
        End Function
    End Class
End Namespace