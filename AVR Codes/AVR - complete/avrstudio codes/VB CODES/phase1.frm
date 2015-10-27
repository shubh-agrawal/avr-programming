VERSION 5.00
Begin VB.Form Form1 
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0C0&
   Caption         =   "CTU ALLAHABAD"
   ClientHeight    =   8820
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   11730
   DrawStyle       =   4  'Dash-Dot-Dot
   DrawWidth       =   3
   LinkTopic       =   "Form1"
   ScaleHeight     =   8820
   ScaleWidth      =   11730
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.TextBox Text2 
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
      Height          =   425
      IMEMode         =   3  'DISABLE
      Left            =   11760
      MaxLength       =   6
      PasswordChar    =   "*"
      TabIndex        =   13
      Top             =   3960
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.TextBox Text1 
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
      Height          =   425
      IMEMode         =   3  'DISABLE
      Left            =   4560
      MaxLength       =   4
      PasswordChar    =   "*"
      TabIndex        =   12
      Top             =   3960
      Visible         =   0   'False
      Width           =   1695
   End
   Begin VB.CommandButton Command3 
      Caption         =   "enter"
      Height          =   425
      Left            =   13680
      TabIndex        =   9
      Top             =   3960
      Visible         =   0   'False
      Width           =   975
   End
   Begin VB.Timer Timer2 
      Interval        =   1
      Left            =   12720
      Top             =   2760
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   5280
      Top             =   2760
   End
   Begin VB.CommandButton Command2 
      Caption         =   "EMPLOYEE LOGIN"
      Height          =   500
      Left            =   9120
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   2760
      Width           =   3255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "CUSTOMER LOGIN"
      Height          =   500
      Left            =   1680
      TabIndex        =   1
      Top             =   2760
      Width           =   3135
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "signing in..."
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   255
      Left            =   3960
      TabIndex        =   14
      Top             =   4920
      Visible         =   0   'False
      Width           =   2145
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "signing in..."
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   255
      Left            =   11880
      TabIndex        =   11
      Top             =   4920
      Visible         =   0   'False
      Width           =   2145
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Wrong Password"
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   255
      Left            =   11880
      TabIndex        =   10
      Top             =   4920
      Visible         =   0   'False
      Width           =   2310
   End
   Begin VB.Label Label7 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label7"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      Left            =   2040
      TabIndex        =   8
      Top             =   1560
      Width           =   765
   End
   Begin VB.Label Label6 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label6"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      Left            =   600
      TabIndex        =   7
      Top             =   1530
      Width           =   765
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0C0&
      Caption         =   "Wrong Password"
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF8080&
      Height          =   255
      Left            =   3960
      TabIndex        =   6
      Top             =   4920
      Visible         =   0   'False
      Width           =   2310
   End
   Begin VB.Label Label4 
      BackStyle       =   0  'Transparent
      Caption         =   $"phase1.frx":0000
      BeginProperty Font 
         Name            =   "Rockwell"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1095
      Left            =   1680
      TabIndex        =   5
      Top             =   7440
      Width           =   8415
      WordWrap        =   -1  'True
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "password"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   12.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   10200
      TabIndex        =   4
      Top             =   4080
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "password"
      BeginProperty Font 
         Name            =   "Verdana"
         Size            =   12.75
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   300
      Left            =   3000
      TabIndex        =   3
      Top             =   4080
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      BorderStyle     =   1  'Fixed Single
      Caption         =   " WELCOME to central transmission unit ( CTU ) , allahabad"
      BeginProperty Font 
         Name            =   "Stencil"
         Size            =   21
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   525
      Left            =   0
      TabIndex        =   0
      Top             =   840
      Width           =   15225
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Dim pa, pb, pc, inval, outval, i, chk, chk1, passchar As Integer
Private Sub Command1_Click()

Label2.Visible = True
Text1.Visible = True
Label3.Visible = False
Text2.Visible = False
Out pc, &H23        'sending  d1 d0 = 1,1 to indicate ready to accept frm remote
Timer1.Enabled = True
End Sub

Private Sub Command2_Click()
Label3.Visible = True
Text2.Visible = True
Label2.Visible = False
Text1.Visible = False
Command3.Visible = True

End Sub

Private Sub Command3_Click()

If Text2.Text = "12345" Then
 Label9.Visible = True
 Wait 1
 Call PlayWav("C:\manju\my program\phase 1\phase new\login.wav")

Form3.Visible = True
Label9.Visible = False
Form1.Hide
Else: Label8.Visible = True
Text2.Text = ""
Text2.SetFocus
End If

End Sub


Private Sub Form_Load()

Text1.Text = ""
Text2.Text = ""
Label6.Caption = Date

pa = &H378
pb = &H379
pc = &H37A
Out pc, &H0
End Sub



Private Sub Timer1_Timer()  '  remote login

 chk = Inp(pb) ' getting data  frm port 379
 chk1 = chk And &H30
 
 '--------------------------will wait for d5, d4 = 1,0--------------------------------
  If chk1 = 32 Then
        
     passchar = Inp(pa)
     Out pc, &H20
     Text1.Text = Text1.Text & passchar
     Wait 1  ' wait for 1 s
     Out pc, &H23
 End If
 '-----------------------------------------------------------------------------------
 
 '---------------entered password to be validated as d5 ,d4 = 1 ,1-----------------------
 If chk1 = 48 Then
 
               If Text1.Text = "4444" Then
               Label10.Visible = True
               Wait 1
               Call PlayWav("C:\manju\my program\phase 1\phase new\login.wav")
               Out pc, &H20
               Timer1.Enabled = False
               Label10.Visible = False
               Form2.Visible = True
               Form1.Hide
           Else
               Label5.Visible = True
               Text1.Text = ""
               Form1.Refresh
               Out pc, &H20
               Wait 1
               Out pc, &H3
              
          End If
                   
  End If
  '------------------------------------------------------------------------------------
  
End Sub

Private Sub Timer2_Timer()
Label7.Caption = Time
End Sub
