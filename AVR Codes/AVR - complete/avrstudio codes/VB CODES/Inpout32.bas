Attribute VB_Name = "InpOut32_Declarations"

'Inp and Out declarations for port I/O using inpout32.dll.

Public Declare Function Inp Lib "inpout32.dll" Alias "Inp32" _
    (ByVal PortAddress As Integer) _
    As Integer
    
Public Declare Sub Out Lib "inpout32.dll" Alias "Out32" _
    (ByVal PortAddress As Integer, _
    ByVal value As Integer)

