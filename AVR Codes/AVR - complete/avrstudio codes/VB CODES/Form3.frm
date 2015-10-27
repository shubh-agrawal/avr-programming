VERSION 5.00
Begin VB.Form Form3 
   Appearance      =   0  'Flat
   BackColor       =   &H00C0C000&
   Caption         =   "Monitoring system"
   ClientHeight    =   7860
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   12840
   ForeColor       =   &H00808080&
   LinkTopic       =   "Form3"
   ScaleHeight     =   11115
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton Command4 
      Caption         =   "LOGOUT"
      Height          =   375
      Left            =   12240
      TabIndex        =   11
      Top             =   7320
      Width           =   1815
   End
   Begin VB.Timer Timer3 
      Enabled         =   0   'False
      Interval        =   10
      Left            =   2040
      Top             =   6240
   End
   Begin VB.CommandButton Command3 
      Caption         =   "STATUS MONITORING"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1440
      TabIndex        =   8
      Top             =   5160
      Width           =   3855
   End
   Begin VB.Timer Timer2 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   1800
      Top             =   3600
   End
   Begin VB.CommandButton Command2 
      Caption         =   "RECHARGE"
      Height          =   375
      Left            =   9000
      TabIndex        =   6
      Top             =   3600
      Visible         =   0   'False
      Width           =   1935
   End
   Begin VB.TextBox Text1 
      Alignment       =   1  'Right Justify
      Appearance      =   0  'Flat
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   6720
      TabIndex        =   5
      Top             =   3600
      Visible         =   0   'False
      Width           =   1815
   End
   Begin VB.CommandButton Command1 
      Caption         =   "FLASH CARD UPDATE/RECHARGE"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   8.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   1320
      TabIndex        =   3
      Top             =   2520
      Width           =   3975
   End
   Begin VB.Timer Timer1 
      Interval        =   1000
      Left            =   12480
      Top             =   120
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   ".........."
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00000080&
      Height          =   330
      Left            =   6840
      TabIndex        =   10
      Top             =   6240
      Visible         =   0   'False
      Width           =   900
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Number of units remaining :"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   2880
      TabIndex        =   9
      Top             =   6240
      Visible         =   0   'False
      Width           =   3420
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "SUCCESSFULLY CHARGED !!!!!"
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00404080&
      Height          =   255
      Left            =   6720
      TabIndex        =   7
      Top             =   4200
      Visible         =   0   'False
      Width           =   4290
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Enter units to be recharged :"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   2880
      TabIndex        =   4
      Top             =   3600
      Visible         =   0   'False
      Width           =   3495
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label3"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   13080
      TabIndex        =   2
      Top             =   800
      Width           =   735
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label2"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   11520
      TabIndex        =   1
      Top             =   800
      Width           =   735
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFC0C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "  CTU Allahabad - Energy monitoring system"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   15.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   450
      Left            =   240
      TabIndex        =   0
      Top             =   720
      Width           =   14850
   End
End
Attribute VB_Name = "Form3"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim pa, pb, pc, inval, outval, passchar, i, chk, chk1, chk2, rechargevalue As Integer

Private Sub Command1_Click()
Label7.Visible = False
Label6.Visible = False
Label4.Visible = True
Text1.Visible = True
Command2.Visible = True
Out pc, &H0
End Sub

Private Sub Command2_Click()

Out pc, &H0  ' disable tristate
rechargevalue = Text1.Text
Out pa, rechargevalue
Out pc, &H2                          ' data valid
Timer2.Enabled = True

End Sub

Private Sub Command3_Click() ' ROM reading
Label4.Visible = False
Text1.Visible = False
Command2.Visible = False
Label7.Visible = True
Label6.Visible = True
Timer3.Enabled = True
Out pc, &H0
End Sub

Private Sub Command4_Click()
Timer2.Enabled = False
Timer3.Enabled = False
Call PlayWav("C:\Documents and Settings\Manjunath.MANJU---81-223\Desktop\VB parallel port\phase 1\phase new\out.wav")
Load Form1
Form1.Text1 = ""
Form1.Text2 = ""
Form1.Text2.Visible = False
Form1.Text1.Visible = False
Form1.Label3.Visible = False
Form1.Command3.Visible = False

Form1.Show
Form3.Hide
End Sub

Private Sub Form_Load()
Out pc, &H0
pa = &H378
pb = &H379
pc = &H37A
Out pc, &H0
Label2.Caption = Date
End Sub


Private Sub Timer1_Timer()
Label3.Caption = Time
End Sub

Private Sub Timer2_Timer()                ' EEPROM writing
 
pa = &H378
pb = &H379
pc = &H37A

 chk1 = Inp(pb)
 
 chk2 = chk1 And &H30
 
 '---------------entered units to be validated as  d5,d4 = 1 ,1-----------------------
 If chk2 = 48 Then
 
         Label5.Visible = True
         Out pc, &H0
         Wait 1
         Timer2.Enabled = False
         Out pc, &H0                ' d2 d1 = 00
         Wait 2
         Label5.Visible = False
  End If
  '------------------------------------------------------------------------------------
 End Sub
 
Private Sub Timer3_Timer()           ' EEPROM reading again

pa = &H378
pb = &H379
pc = &H37A

 Out pc, &H21
 chk = Inp(pb)
 chk1 = chk And &H30
 
 '--------------------------will wait for d5 d4 = 1,1--------------------------------
  If chk1 = 48 Then
  
     
     passchar = Inp(pa)   ' input ROM value from data port
         If passchar = 255 Then
         GoTo Skip
         End If
     
     Label7.Caption = passchar
     
Skip:
     Out pc, &H20  ' trisated
 End If
 '----------------------------------------------------------------------------------
 
End Sub
