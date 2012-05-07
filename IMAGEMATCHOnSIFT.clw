; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CShowImgDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IMAGEMATCHOnSIFT.h"

ClassCount=6
Class1=CIMAGEMATCHOnSIFTApp
Class2=CIMAGEMATCHOnSIFTDlg
Class3=CAboutDlg

ResourceCount=6
Resource1=IDD_DIALOGCLOSE
Resource2=IDR_MAINFRAME
Resource3=IDD_IMAGEMATCHONSIFT_DIALOG
Class4=CShowImgDlg
Resource4=IDD_IMGDISPLAYER
Class5=CDlgClose
Resource5=IDD_ABOUTBOX
Class6=CDlgMClose
Resource6=IDD_DIALOGMCLOSE

[CLS:CIMAGEMATCHOnSIFTApp]
Type=0
HeaderFile=IMAGEMATCHOnSIFT.h
ImplementationFile=IMAGEMATCHOnSIFT.cpp
Filter=N

[CLS:CIMAGEMATCHOnSIFTDlg]
Type=0
HeaderFile=IMAGEMATCHOnSIFTDlg.h
ImplementationFile=IMAGEMATCHOnSIFTDlg.cpp
Filter=D
LastObject=CIMAGEMATCHOnSIFTDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=IMAGEMATCHOnSIFTDlg.h
ImplementationFile=IMAGEMATCHOnSIFTDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308864

[DLG:IDD_IMAGEMATCHONSIFT_DIALOG]
Type=1
Class=CIMAGEMATCHOnSIFTDlg
ControlCount=37
Control1=IDC_BUTTONSELECTIMG1,button,1342246656
Control2=IDC_BUTTONSELECTIMG2,button,1342246656
Control3=IDC_EDITSELECTIMG1,edit,1350631824
Control4=IDC_EDITSELECTIMG2,edit,1350631824
Control5=IDC_BUTTONSHOWIMG,button,1342246656
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308864
Control8=IDC_COMBOGWS,combobox,1344471299
Control9=IDC_STATIC,static,1342308864
Control10=IDC_COMBOBD,combobox,1344340227
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMBOSDR,combobox,1344340227
Control13=IDC_STATIC,static,1342308864
Control14=IDC_COMBOMT,combobox,1478557955
Control15=IDC_STATIC,static,1342308352
Control16=IDC_SLIDERIS,msctls_trackbar32,1342242840
Control17=IDC_EDITIS,edit,1484849296
Control18=IDC_STATIC,static,1342308864
Control19=IDC_SLIDERCD,msctls_trackbar32,1342242840
Control20=IDC_EDITCD,edit,1484849296
Control21=IDC_BUTTONFD,button,1342246656
Control22=IDC_BUTTONMATCH,button,1342246656
Control23=IDC_BUTTONCLEAR,button,1342242816
Control24=IDC_BUTTONLOCATE,button,1342246656
Control25=IDC_STATIC,button,1342177287
Control26=IDC_STATIC,static,1342308864
Control27=IDC_STATIC,static,1342308864
Control28=IDC_STATIC,static,1342308352
Control29=IDC_EDITKEYPOINTSNUM1,edit,1350633600
Control30=IDC_EDITKEYPOINTSNUM2,edit,1350633600
Control31=IDC_EDITMATCHEDNUM,edit,1350633600
Control32=IDC_CHECKDBLBASEIMG,button,1342242819
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308864
Control35=IDC_COMBOMINIRES,combobox,1344339971
Control36=IDC_RADIO4,button,1476526089
Control37=IDC_RADIO5,button,1476395017

[DLG:IDD_IMGDISPLAYER]
Type=1
Class=CShowImgDlg
ControlCount=1
Control1=IDC_IMGDISPLAYER,static,1342177287

[CLS:CShowImgDlg]
Type=0
HeaderFile=ShowImgDlg.h
ImplementationFile=ShowImgDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CShowImgDlg

[DLG:IDD_DIALOGCLOSE]
Type=1
Class=CDlgClose
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BUTTONNO,button,1342242816
Control4=IDC_STATIC,static,1342308864

[CLS:CDlgClose]
Type=0
HeaderFile=DlgClose.h
ImplementationFile=DlgClose.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgClose
VirtualFilter=dWC

[DLG:IDD_DIALOGMCLOSE]
Type=1
Class=CDlgMClose
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308865
Control4=IDC_STATIC,button,1342177287

[CLS:CDlgMClose]
Type=0
HeaderFile=DlgMClose.h
ImplementationFile=DlgMClose.cpp
BaseClass=CDialog
Filter=D
LastObject=CDlgMClose

