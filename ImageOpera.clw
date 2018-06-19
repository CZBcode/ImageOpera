; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CImageCYDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ImageOpera.h"
LastPage=0

ClassCount=6
Class1=CImageOperaApp
Class2=CImageOperaDoc
Class3=CImageOperaView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDR_CNTR_INPLACE
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX
Class6=CImageCYDlg
Resource4=IDD_DIALOG_CY

[CLS:CImageOperaApp]
Type=0
HeaderFile=ImageOpera.h
ImplementationFile=ImageOpera.cpp
Filter=N

[CLS:CImageOperaDoc]
Type=0
HeaderFile=ImageOperaDoc.h
ImplementationFile=ImageOperaDoc.cpp
Filter=N

[CLS:CImageOperaView]
Type=0
HeaderFile=ImageOperaView.h
ImplementationFile=ImageOperaView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CImageOperaView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EDIT_COPY
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ImageOpera.cpp
ImplementationFile=ImageOpera.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=ID_FILE_SAVE_AS
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_PASTE_SPECIAL
Command10=ID_OLE_INSERT_NEW
Command11=ID_OLE_EDIT_LINKS
Command12=ID_OLE_VERB_FIRST
Command13=ID_SHOW_TWO
Command14=ID_SHOW_HD
Command15=ID_LH_2
Command16=ID_LH_4
Command17=ID_LH_8
Command18=ID_LH_16
Command19=ID_LH_32
Command20=ID_LH_64
Command21=ID_APP_ABOUT
Command22=ID_CY
CommandCount=22

[MNU:IDR_CNTR_INPLACE]
Type=1
Class=CImageOperaView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
CommandCount=9

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CANCEL_EDIT_CNTR
CommandCount=15

[ACL:IDR_CNTR_INPLACE]
Type=1
Class=CImageOperaView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_CANCEL_EDIT_CNTR
CommandCount=7

[DLG:IDD_DIALOG_CY]
Type=1
Class=CImageCYDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_CYX,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_CYY,edit,1350631552

[CLS:CImageCYDlg]
Type=0
HeaderFile=ImageCYDlg.h
ImplementationFile=ImageCYDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_CYX
VirtualFilter=dWC

