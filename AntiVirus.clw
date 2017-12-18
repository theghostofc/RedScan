; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CAntiVirusDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "AntiVirus.h"

ClassCount=3
Class1=CAntiVirusApp
Class2=CAntiVirusDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_DIALOG1
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_ANTIVIRUS_DIALOG

[CLS:CAntiVirusApp]
Type=0
HeaderFile=AntiVirus.h
ImplementationFile=AntiVirus.cpp
Filter=N
LastObject=CAntiVirusApp
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CAntiVirusDlg]
Type=0
HeaderFile=AntiVirusDlg.h
ImplementationFile=AntiVirusDlg.cpp
Filter=D
LastObject=IDC_LIST_REPORT
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=AntiVirusDlg.h
ImplementationFile=AntiVirusDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDOK,button,1342373889
Control3=IDC_STATIC_DESC,static,1342308352
Control4=IDC_STATIC_ABOUT,static,1342308352

[DLG:IDD_ANTIVIRUS_DIALOG]
Type=1
Class=CAntiVirusDlg
ControlCount=19
Control1=IDC_STATIC_PATH,static,1342308352
Control2=IDC_EDIT_PATH,edit,1350631552
Control3=IDC_BUTTON_BROWSE,button,1342242816
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_BUTTON_ABOUT,button,1342242816
Control7=IDC_LIST_REPORT,listbox,1085341955
Control8=IDC_STATIC_SCANNING_DATA,static,1342308352
Control9=IDC_STATIC_REPORT,button,1342177287
Control10=IDC_STATIC_SC,static,1342308352
Control11=IDC_STATIC_SCAN_DATA,static,1342308354
Control12=IDC_STATIC_IN,static,1342308352
Control13=IDC_STATIC_INFE_DATA,static,1342308354
Control14=IDC_STATIC_RE,static,1342308352
Control15=IDC_STATIC_REPA_DATA,static,1342308354
Control16=IDC_STATIC_NO,static,1342308352
Control17=IDC_STATIC_NREP_DATA,static,1342308354
Control18=IDC_STATIC_DELE,static,1342308352
Control19=IDC_STATIC_DELE_DATA,static,1342308354

[DLG:IDD_DIALOG1]
Type=1
Class=?
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1342242944

