Attribute VB_Name = "Module2"
Public Declare Function playa Lib "winmm.dll" Alias "sndPlaySoundA" (ByVal lpszSoundName As String, ByVal uFlags As Long) As Long

Public Sub PlayWav(sFile As String)
    If Dir(sFile$) <> "" Then Call playa(sFile, SND_FLAG)
End Sub
