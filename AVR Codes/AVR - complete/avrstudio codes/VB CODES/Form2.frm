VERSION 5.00
Begin VB.Form Form2 
   BackColor       =   &H00808080&
   Caption         =   "User Form"
   ClientHeight    =   3090
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   4680
   LinkTopic       =   "Form2"
   ScaleHeight     =   11010
   ScaleWidth      =   15240
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CommandButton Command1 
      Caption         =   "SIGN OUT"
      Height          =   495
      Left            =   11280
      TabIndex        =   3
      Top             =   5760
      Width           =   1815
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1
      Left            =   3960
      Top             =   600
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Your units are very low .please recharge immedietly !!"
      BeginProperty Font 
         Name            =   "OCR A Extended"
         Size            =   11.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFFFF&
      Height          =   255
      Left            =   2160
      TabIndex        =   7
      Top             =   4440
      Visible         =   0   'False
      Width           =   8100
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Welcome !"
      BeginProperty Font 
         Name            =   "Arial"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   330
      Left            =   600
      TabIndex        =   6
      Top             =   2040
      Width           =   1410
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label4"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   330
      Left            =   13320
      TabIndex        =   5
      Top             =   1320
      Width           =   735
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Label4"
      BeginProperty Font 
         Name            =   "Trebuchet MS"
         Size            =   12
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00800000&
      Height          =   330
      Left            =   11280
      TabIndex        =   4
      Top             =   1320
      Width           =   735
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "-------"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   14.25
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C00000&
      Height          =   330
      Left            =   6480
      TabIndex        =   2
      Top             =   3600
      Width           =   630
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "Total units available for usage is "
      BeginProperty Font 
         Name            =   "Microsoft Sans Serif"
         Size            =   14.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   360
      Left            =   2160
      TabIndex        =   1
      Top             =   3600
      Width           =   4035
   End
   Begin VB.Label Label1 
      Appearance      =   0  'Flat
      BackColor       =   &H00FFC0C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   " User info bar"
      BeginProperty Font 
         Name            =   "Times New Roman"
         Size            =   15.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H80000008&
      Height          =   390
      Left            =   240
      TabIndex        =   0
      Top             =   1320
      Width           =   14775
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim chk, pa, pb, pc, chk1, passchar As Integer

Private Sub Command1_Click()
Out pc, &H0
Timer1.Enabled = False
 Wait 1
 Call PlayWav("C:\manju\my program\phase 1\phase new\out.wav")
Form1.Text1 = ""
Form1.Text2 = ""
Form1.Text2.Visible = False
Form1.Text1.Visible = False
Form1.Label2.Visible = False
Form1.Text1.Visible = False
Load Form1
Form1.Show
Form2.Hide
End Sub

Private Sub Form_Load()
Label4.Caption = Date
pa = &H378
pb = &H379
pc = &H37A
Timer1.Enabled = True
Out pc, &H0
End Sub

Private Sub Timer1_Timer()
Label5.Caption = Time

 Out pc, &H21
 chk = Inp(pb)
 chk1 = chk And &H30
 
 '--------------------------will wait for d5 d4 = 1,1--------------------------------
  If chk1 = 48 Then
  
     
         passchar = Inp(pa)   ' input ROM value from data port
         If passchar = 255 Then
         GoTo Skip
         End If
         
         Label3.Caption = passchar
         
         If passchar < 10 Then
         Label7.Visible = True
         Call PlayWav("C:\manju\my program\phase 1\phase new\notify.wav")
         End If
     
Skip:
     Out pc, &H20  ' trisated
 End If
 '----------------------------------------------------------------------------------
 
 End Sub
 

