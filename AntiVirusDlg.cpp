// AntiVirusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AntiVirus.h"
#include "AntiVirusDlg.h"
#include <direct.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}
	
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntiVirusDlg dialog

CAntiVirusDlg::CAntiVirusDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntiVirusDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAntiVirusDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	if(Init(IDR_VIRDATA) == FALSE)
	{
		MessageBox("Error Loading Application. Exitting...",
			"Error", MB_OK|MB_ICONSTOP);
		exit(0);
	}
}

void CAntiVirusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAntiVirusDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAntiVirusDlg, CDialog)
	//{{AFX_MSG_MAP(CAntiVirusDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_BUTTON_ABOUT, OnAbout)
	ON_LBN_DBLCLK(IDC_LIST_REPORT, OnDblclkListReport)
	ON_EN_CHANGE(IDC_EDIT_PATH, OnChangeEditPath)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAntiVirusDlg message handlers
BOOL CAntiVirusDlg::Init(UINT uIDRMap)
{	
	CString Error;
	strcpy(glo.s_path,getenv("TEMP"));
	strcat(glo.s_path,"\\Temp.rep");
	HRSRC hRes;
	HINSTANCE hInst = AfxGetResourceHandle();
	HGLOBAL hGlob;
	LPVOID lpData;
	
	hRes = FindResource(hInst, MAKEINTRESOURCE(uIDRMap), "BINARYDATA");
	if (hRes == NULL)
		return FALSE;
	hGlob = LoadResource(hInst, hRes);
	if (hGlob == NULL)
		return FALSE;
	lpData = LockResource(hGlob);
	if (lpData != NULL)
	{
		virdata = new char [75];
		memcpy(virdata, lpData, 75);
	}
	FreeResource(hGlob);
	return TRUE;
}
void GetFixedDrives()
{
	char drives[_MAX_PATH]={0};
	char temp[]="A:\\";
	GetLogicalDriveStrings(_MAX_PATH,drives);
	int i=0,j=0;
	while(!j)
	{
		temp[0]=drives[i];
		if(GetDriveType(temp)==DRIVE_FIXED)
		{
			glo.localDrives+=temp;
			glo.localDrives+=";";
			i+=3;
		}
		if(drives[i]==NULL && drives[i+1]==NULL)
			j=1;
		i++;
	}
}
BOOL CAntiVirusDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->EnableMenuItem(61440,MF_GRAYED);//Size
			pSysMenu->EnableMenuItem(61488,MF_GRAYED);//Max
		}
	}
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetFixedDrives();
	InitDialog();
	SetWindowText("Red Scan - v3.27");
	SetDlgItemText(IDC_STATIC_SC,"Scanned");
	SetDlgItemText(IDC_STATIC_IN,"Infected");
	SetDlgItemText(IDC_STATIC_RE,"Repaired");
	SetDlgItemText(IDC_STATIC_NO,"Not Repaired");
	SetDlgItemText(IDC_STATIC_DELE,"Deleted");
	SetDlgItemText(IDC_STATIC_PATH,"Folder to Scan");
	if (AfxGetApp()->m_lpCmdLine[0] != _T('\0'))
	{
		SetDlgItemText(IDC_EDIT_PATH,AfxGetApp()->m_lpCmdLine);
		OnOK();
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CAntiVirusDlg::InitDialog()
{
	GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	
	SetDlgItemText(IDC_STATIC_SCAN_DATA,"0");
	SetDlgItemText(IDC_STATIC_INFE_DATA,"0");
	SetDlgItemText(IDC_STATIC_REPA_DATA,"0");
	SetDlgItemText(IDC_STATIC_NREP_DATA,"0");
	SetDlgItemText(IDC_STATIC_DELE_DATA,"0");
	glo.scanned = 0;
	glo.infected = 0;
	glo.repaired = 0;
	glo.not_repaired = 0;
	glo.deleted = 0;
	glo.bScan=true;
	glo.bClose=true;
	strcpy(glo.buffer, "C:\\");
	SetDlgItemText(IDOK,"&Scan");
	SetDlgItemText(IDCANCEL,"&Close");

	GetDlgItem(IDC_EDIT_PATH)->EnableWindow();
	GetDlgItem(IDC_STATIC_PATH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON_BROWSE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_REPORT)->ShowWindow(SW_SHOW);
	SetDlgItemText(IDC_STATIC_SCANNING_DATA,"Red Scan - v3.27 - by Vivek Jain - TheGhostOfC");
	SendDlgItemMessage(IDC_LIST_REPORT,LB_RESETCONTENT);

	GetDlgItem(IDC_LIST_REPORT)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_SCAN_DATA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_INFE_DATA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_REPA_DATA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_NREP_DATA)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DELE_DATA)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_STATIC_SC)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_IN)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_RE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_NO)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC_DELE)->ShowWindow(SW_SHOW);
	SendDlgItemMessage(IDC_EDIT_PATH,EN_SETFOCUS);
}

void CAntiVirusDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAntiVirusDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
		CDialog::OnPaint();
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CAntiVirusDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//Create the Browse for Folder Dialog Box
LPITEMIDLIST PidlBrowse(HWND hwnd, LPSTR pszDisplayName)
{
	LPITEMIDLIST pidlRoot = NULL;
    LPITEMIDLIST pidlSelected = NULL;
    BROWSEINFO bi = {0};
    LPMALLOC pMalloc = NULL;

    SHGetMalloc(&pMalloc);
	
	bi.hwndOwner = hwnd;
    bi.pidlRoot = pidlRoot;
    bi.pszDisplayName = pszDisplayName;
    bi.lpszTitle = "Choose a folder to Scan";
    bi.ulFlags = BIF_RETURNONLYFSDIRS;
    bi.lpfn = NULL;
    bi.lParam = 0;
	pidlSelected = SHBrowseForFolder(&bi);
	pMalloc->Release();
    return pidlSelected;
}

//Get the Destn folder from Browse for Folder Dialog Box
void CAntiVirusDlg::OnBrowse() 
{
	InitDialog();
	LPITEMIDLIST pidlRoot = NULL;
	HWND hwnd = GetSafeHwnd();
	char pszDisplayName[MAX_PATH] = {0};
	BOOL bPath = TRUE;
	HRESULT hResult;
	LPVOID pvReserved = NULL;
	hResult = CoInitialize( pvReserved );
	pidlRoot = PidlBrowse( hwnd, pszDisplayName);
	bPath = SHGetPathFromIDList(pidlRoot, pszDisplayName);
	CString temp;
	GetDlgItemText(IDC_EDIT_PATH,temp);
	if(bPath==TRUE)
	{
		if(temp.GetLength()>0)
			temp.Insert(0,";");
		SetDlgItemText(IDC_EDIT_PATH,pszDisplayName+temp);
	}
	else
	{
		if(temp.GetLength()==0)
			SetDlgItemText(IDC_EDIT_PATH,glo.localDrives+temp);
	}
	CoUninitialize();
	GetDlgItem(IDOK)->EnableWindow();
	GetDlgItem(IDOK)->SetFocus();
}

void CAntiVirusDlg::OnChangeEditPath() 
{
	CString s;
	GetDlgItemText(IDC_EDIT_PATH,s);
	int Len = s.GetLength();
	if(Len > 0)
	{
		GetDlgItemText(IDC_EDIT_PATH,s);
		s.TrimLeft();
		s.TrimRight();
		if(s.GetLength()>0)
			GetDlgItem(IDOK)->EnableWindow();
		else
			SetDlgItemText(IDC_EDIT_PATH,s);
	}
	else
		GetDlgItem(IDOK)->EnableWindow(FALSE);
}

void DeleteKey(const HKEY hKey, char *cKey, char *cSubKey=NULL)
{
	HKEY hRead;
	if(cSubKey==NULL)
	{
		RegDeleteKey(hKey, cKey);
		return;
	}
	if(RegOpenKeyEx(hKey, cKey, 0, KEY_EXECUTE|KEY_READ, &hRead)==ERROR_SUCCESS)
		RegDeleteKey(hRead, cSubKey);
	RegCloseKey(hRead);
}
void DeleteValue(const HKEY hKey, char *cKey, char *cValue)
{
	HKEY hRead;
	DWORD dw=0, Size=_MAX_PATH;
	BYTE Data[_MAX_PATH]={0};
	if(RegOpenKeyEx(hKey, cKey, 0, KEY_EXECUTE|KEY_READ, &hRead)==ERROR_SUCCESS)
		if(RegQueryValueEx(hRead,cValue,NULL,&dw,Data, &Size)==ERROR_SUCCESS)
			RegDeleteValue(hRead, cValue);
	RegCloseKey(hRead);
}
void DeleteHKCU()
{
	HKEY hRead;
	RegOpenKeyEx(HKEY_CURRENT_USER, "Identities", 0, KEY_EXECUTE|KEY_READ, &hRead);
	char KeyName[_MAX_PATH];
	char ClassName[_MAX_PATH] = "";
	DWORD dwcClassLen = _MAX_PATH;
	DWORD dwcSubKeys;
	DWORD dwcMaxSubKey;
	DWORD dwcMaxClass;
	DWORD dwcValues;
	DWORD dwcMaxValueName;
	DWORD dwcMaxValueData;
	DWORD dwcSecDesc;
	FILETIME ftLastWriteTime;
	char Key[_MAX_PATH]={"Identities"};

	if(RegOpenKeyEx(HKEY_CURRENT_USER, Key, 0, KEY_EXECUTE|KEY_READ, &hRead)==ERROR_SUCCESS)
		RegQueryInfoKey (hRead, ClassName, &dwcClassLen, NULL, &dwcSubKeys,
			&dwcMaxSubKey, &dwcMaxClass, &dwcValues, &dwcMaxValueName,
			&dwcMaxValueData, &dwcSecDesc, &ftLastWriteTime);
	RegEnumKey (hRead, 0, KeyName, _MAX_PATH);
	RegCloseKey(hRead);
	strcat(Key, KeyName);
	strcat(Key, "\\Software\\Microsoft\\Outlook Express");
	if(RegOpenKeyEx(HKEY_CURRENT_USER, Key, 0, KEY_EXECUTE|KEY_READ, &hRead)==ERROR_SUCCESS)
	{
		RegQueryInfoKey (hRead, ClassName, &dwcClassLen, NULL, &dwcSubKeys,
			&dwcMaxSubKey, &dwcMaxClass, &dwcValues, &dwcMaxValueName,
			&dwcMaxValueData, &dwcSecDesc, &ftLastWriteTime);
		RegEnumKey (hRead, 0, KeyName, _MAX_PATH);
		RegCloseKey(hRead);
		strcat(Key, "\\");
		strcat(Key, KeyName);
		strcat(Key, "\\Mail");
		DeleteValue(HKEY_CURRENT_USER, Key, "Compose Use Stationery");
		DeleteValue(HKEY_CURRENT_USER, Key, "Stationery Name");
		DeleteValue(HKEY_CURRENT_USER, Key, "Wide Stationery Name");
	}
	if(RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Office", 0, KEY_EXECUTE|KEY_READ, &hRead)==ERROR_SUCCESS)
		RegQueryInfoKey (hRead, ClassName, &dwcClassLen, NULL, &dwcSubKeys,
			&dwcMaxSubKey, &dwcMaxClass, &dwcValues, &dwcMaxValueName,
			&dwcMaxValueData, &dwcSecDesc, &ftLastWriteTime);
	RegEnumKey (hRead, 0, KeyName, _MAX_PATH);
	RegCloseKey(hRead);
	strcat(Key, "\\");
	strcat(Key, KeyName);
	strcat(Key, "\\Outlook\\Options\\Mail");

	DeleteValue(HKEY_CURRENT_USER, Key, "EditorPreference");
}
void ScanReg() 
{
	//hkcr
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile", "ScriptEngine");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile", "ScriptHostEncode");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile\\Shell\\Open", "Command");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile\\Shell", "Open");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile", "Shell");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile\\ShellEx\\PropertySheetHandlers", "WSHProps");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile\\ShellEx", "PropertySheetHandlers");
	DeleteKey(HKEY_CLASSES_ROOT, "dllfile", "ShellEx");
	
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile", "ScriptEngine");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile", "ScriptHostEncode");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile\\Shell\\Open", "Command");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile\\Shell", "Open");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile\\ShellEx\\PropertySheetHandlers", "WSHProps");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile\\ShellEx", "PropertySheetHandlers");
	DeleteKey(HKEY_CLASSES_ROOT, "jsfile", "ShellEx");
	
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile", "ScriptEngine");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile", "ScriptHostEncode");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile\\Shell\\Open", "Command");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile\\Shell", "Open");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile\\ShellEx\\PropertySheetHandlers", "WSHProps");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile\\ShellEx", "PropertySheetHandlers");
	DeleteKey(HKEY_CLASSES_ROOT, "vbsfile", "ShellEx");
	
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile", "ScriptEngine");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile", "ScriptHostEncode");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile\\Shell\\Open", "Command");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile\\Shell", "Open");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile\\ShellEx\\PropertySheetHandlers", "WSHProps");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile\\ShellEx", "PropertySheetHandlers");
	DeleteKey(HKEY_CLASSES_ROOT, "wshfile", "ShellEx");
		
	DeleteKey(HKEY_CLASSES_ROOT, "clsid\\{60254CA5-953B-11CF-8C96-00AA00B8708C}","inprocserver32");
	DeleteKey(HKEY_CLASSES_ROOT, "clsid","{60254CA5-953B-11CF-8C96-00AA00B8708C}");

	//hklm
	DeleteValue(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", "Kernel32");
	DeleteValue(HKEY_LOCAL_MACHINE, "Software\\microsoft\\windows\\currentversion\\shell extensions\\approved", "{60254CA5-953B-11CF-8C96-00AA00B8708C}");

	DeleteValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows Messaging Subsystem\\Profiles\\Microsoft Outlook\\Internet Settings", "0a0d020000000000c000000000000046");
	DeleteValue(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows NT\\CurrentVersion\\Windows Messaging Subsystem\\Profiles\\Microsoft Outlook\\Internet Settings", "0a0d020000000000c000000000000046");

	DeleteHKCU();
}

//Search for kernel/kernel32.dll
void CAntiVirusDlg::ScanDll()
{
	char s_path[_MAX_PATH];
	strcpy(s_path,getenv("WINDIR"));
	strcat(s_path,"\\System\\kernel.dll");
	fstream ifile;
	ifile.open(s_path, ios::in|ios::nocreate|ios::binary);
	if(! ifile.good())
	{
		strcpy(s_path,getenv("WINDIR"));
		strcat(s_path,"\\System\\kernel32.dll");
		ifile.open(s_path, ios::in|ios::nocreate|ios::binary);
		if(! ifile.good())
			return;
	}
	char *infdata;
	infdata=new char [15];
	if(infdata==NULL)
	{
		ifile.close();
		return;
	}
	char *temp = infdata;
	ifile.read(temp, 15);
	ifile.close();
	DWORD lAttrib;
	if(!strncmp(infdata,"ExeString = ",10))
	{
		lAttrib = GetFileAttributes(s_path);
		SetFileAttributes(s_path, lAttrib & (~FILE_ATTRIBUTE_READONLY));
		remove(s_path);
		Update(dleted);
	}
	else
		Update(0);
	delete [] infdata;
	_finddata_t filestruct;
	long hnd=_findfirst(
		"C:\\Program Files\\Common Files\\Microsoft Shared\\Stationery\\Blank.htm",
		&filestruct);
	if(hnd != -1)
		Update(Repair(filestruct));
	strcpy(s_path,getenv("WINDIR"));
	strcat(s_path,"\\Web\\Folder.htt");
	hnd = _findfirst(s_path,&filestruct);
	if(hnd != -1)
		Update(Repair(filestruct));
}

void CAntiVirusDlg::ScanReport()
{
	CString szReport;
	CString szTemp;
	SetDlgItemText(IDC_EDIT_PATH,NULL);
	GetDlgItem(IDC_EDIT_PATH)->EnableWindow();
	SetDlgItemText(IDC_STATIC_SCANNING_DATA,"Done");
	GetDlgItemText(IDC_STATIC_SCAN_DATA,szReport);
	glo.bClose=true;
	SetDlgItemText(IDCANCEL,"&Close");
	GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow();
	if(glo.scanned == 0)
	{
			MessageBox("No File to Scan", "Sorry", MB_OK|MB_ICONEXCLAMATION);
			return;
	}
	GetDlgItemText(IDC_STATIC_INFE_DATA,szReport);
		if(glo.infected == 0)
	{
		MessageBox("No Virus Found in the Scan", "!! Congrats !!", MB_OK|MB_ICONINFORMATION);
		return;
	}
	szReport = "Repaired ";
	GetDlgItemText(IDC_STATIC_REPA_DATA,szTemp);
	szReport+=szTemp;
	szReport+=", Deleted ";
	GetDlgItemText(IDC_STATIC_DELE_DATA,szTemp);
	szReport+=szTemp;
	szReport.Insert(szReport.GetLength(), " Files of ");
	szReport+=" Files of ";
	GetDlgItemText(IDC_STATIC_INFE_DATA,szTemp);
	szReport+=szTemp;
	szReport+=" Infected Files.";
	MessageBox(szReport, "Result", MB_OK|MB_ICONINFORMATION);
	if(glo.not_repaired > 0)
	{
		SetDlgItemText(IDOK,"&Back");
		GetDlgItem(IDC_STATIC_PATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_BROWSE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_REPORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_SCAN_DATA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_INFE_DATA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_REPA_DATA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NREP_DATA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DELE_DATA)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_SC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_IN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_RE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_NO)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_DELE)->ShowWindow(SW_HIDE);

		GetDlgItem(IDOK)->EnableWindow();
		SetDlgItemText(IDC_STATIC_SCANNING_DATA,"One or More of these Files are still infected...");
		GetDlgItem(IDC_LIST_REPORT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDOK)->SetFocus();
		glo.bScan = false;
	}
	SendDlgItemMessage(IDC_EDIT_PATH,EN_SETFOCUS);
}
//The Main Thread Function
UINT MainScan(LPVOID pParam)
{
	_finddata_t fb={0};
	CAntiVirusDlg *cavd=(CAntiVirusDlg*)pParam;
	for(int i=0;i<glo.sz_pathList.GetSize();i++)
	{
		if(GetFileAttributes(glo.sz_pathList.GetAt(i)) & 
			FILE_ATTRIBUTE_DIRECTORY)
		{
			if(!_chdir(glo.sz_pathList.GetAt(i)))
				cavd->SearchDirectory();
		}
		else
		{
			long hnd=_findfirst(glo.sz_pathList.GetAt(i),&fb);
			if(hnd != -1)
				cavd->Update(cavd->Repair(fb));
		}
	}
	cavd->ScanReport();
	AfxEndThread(0);
	return 0;
}

void CAntiVirusDlg::OnAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();	
}

//Update the Scanning Report
void CAntiVirusDlg::Update(int retval)
{
	CString temp;
	switch(retval)
	{
	case ok:
		glo.scanned++;
		glo.infected++;
		glo.repaired++;
		SetDlgItemInt(IDC_STATIC_INFE_DATA,glo.infected,FALSE);
		SetDlgItemInt(IDC_STATIC_REPA_DATA,glo.repaired,FALSE);
		break;
	case novirus:
		glo.scanned++;
		break;
	case dleted:
		glo.scanned++;
		glo.infected++;
		glo.deleted++;
		SetDlgItemInt(IDC_STATIC_INFE_DATA,glo.infected,FALSE);
		SetDlgItemInt(IDC_STATIC_DELE_DATA,glo.deleted,FALSE);
		break;
	case error:
		break;
	case rdonly:
		glo.scanned++;
		glo.infected++;
		glo.not_repaired++;
		SetDlgItemInt(IDC_STATIC_INFE_DATA,glo.infected,FALSE);
		SetDlgItemInt(IDC_STATIC_NREP_DATA,glo.not_repaired,FALSE);
		SendDlgItemMessage(IDC_LIST_REPORT,LB_ADDSTRING,0,(LPARAM)glo.buffer);
		break;
	default:
		glo.scanned++;
	}
	SetDlgItemInt(IDC_STATIC_SCAN_DATA,glo.scanned,FALSE);
}

//Scan the Directory Tree 2 get files
void CAntiVirusDlg::SearchDirectory()
{
	_finddata_t filestruct;
	long hnd;
	CString szMess;
	hnd = _findfirst("*",&filestruct);
	if(hnd == -1)
		return;
	do
	{
		if(GetFileAttributes(filestruct.name) & 
               FILE_ATTRIBUTE_DIRECTORY )
		{
			if(*filestruct.name != '.')
			{
				if(! _chdir(filestruct.name))
				{
					SearchDirectory();
					_chdir("..");
				}
            }
		}
		else
		{
			_getcwd(glo.buffer,_MAX_PATH);
			if(strlen(glo.buffer)==3)
				glo.buffer[2]='\0';
			strcat(glo.buffer,"\\");
			strcat(glo.buffer,filestruct.name);
			strupr(glo.buffer);
			szMess.Format("Scanning\n%s ...", glo.buffer);
			SetDlgItemText(IDC_STATIC_SCANNING_DATA,szMess);
			Update(Repair(filestruct));
		}
	}while(!(_findnext(hnd,&filestruct)));
}

//Repair the Infected File by Copying it to a New Temp File
int CAntiVirusDlg::Repair(_finddata_t fb)
{
	const unsigned long datsize = 11516;//The size of the Virus Code
	fstream ifile, rfile;
	if(fb.size<11160)
		return novirus;
	if(glo.efname.Find(glo.buffer,0)!=-1)
		return 0;
	ifile.open(glo.buffer, ios::in|ios::nocreate|ios::binary);
	if(! ifile.good())
		return error;
	rfile.open(glo.s_path, ios::out|ios::binary);
	if(! rfile.good())
	{
		ifile.close();
		return error;
	}
	char *infdata=new char [75];
	if(infdata==NULL)
	{
		ifile.close();
		rfile.close();
		return error;
	}
	char *temp = infdata;
	int retval=novirus;
	unsigned int j = 0;
	char httvirdat[] = "<BODY onload=\"vbscript:KJ_start()\">";
	char vbsvirdat[] = "ExeString = ";
	
	//1. Search for VBS type
	ifile.seekg(fb.size-11160, ios::beg);
	temp = infdata;
	ifile.read(temp, 15);
	ifile.seekg(0, ios::beg);
	retval=strncmp(infdata,vbsvirdat, 10);
	if(!retval)
	{
		delete []infdata;
		infdata=new char [fb.size - 11160];
		if(infdata==NULL)
		{
			ifile.close();
			rfile.close();
			return error;
		}
		ifile.read(infdata, fb.size - 11160);
		rfile.write(infdata, fb.size - 11160);
		rfile.close();
		ifile.close();
		retval=Del(fb);
	}
	else
	{
		//2. Search for HTM type
		ifile.seekg(fb.size-datsize, ios::beg);
		ifile.read(temp, 73);
		ifile.seekg(0, ios::beg);
		retval=strncmp(infdata,virdata,72);
		if(!retval)
		{
			delete []infdata;
			infdata=new char [fb.size - datsize];
			if(infdata==NULL)
			{
				ifile.close();
				rfile.close();
				return error;
			}
			ifile.read(infdata, fb.size - datsize);
			rfile.write(infdata, fb.size - datsize);
			rfile.close();
			ifile.close();
			retval=Del(fb);
		}
		//3. Search for HTT type
		else
		{
			ifile.seekg(0, ios::beg);
			temp = infdata;
			ifile.read(temp, 35);
			ifile.seekg(37, ios::beg);
			retval=strncmp(infdata,httvirdat, 35);
			if(!retval)
			{
				delete []infdata;
				infdata=new char [(fb.size - datsize) + 8];
				if(infdata==NULL)
				{
					ifile.close();
					rfile.close();
					return error;
				}
				ifile.read(infdata, (fb.size - datsize) + 8);
				rfile.write(infdata, (fb.size - datsize) + 8);
				ifile.close();
				rfile.close();
				retval=Del(fb);
			}
			//4. Search for DLL type
			else
			{
				retval=strncmp(infdata,"ExeString = ",10);
				if(!retval)
				{
					rfile.close();
					ifile.close();
					remove(glo.s_path);
					if(! remove(fb.name))
						retval=dleted;
					else
						retval=rdonly;
				}
				//The file is ! Infected
				else
				{
					ifile.close();
					rfile.close();
					remove(glo.s_path);
					retval=novirus;
				}
			}
		}
	}
	delete [] infdata;
	remove(glo.s_path);
	return retval;
}

//Delete the Infected File and Restore the Temp File with its Name
int CAntiVirusDlg::Del(_finddata_t fb)
{
	DWORD lAttrib;
	int retval=ok;
	lAttrib = GetFileAttributes(fb.name);
	SetFileAttributes(fb.name, lAttrib & (~FILE_ATTRIBUTE_READONLY));
	if( ! remove(fb.name))
	{
		rename(glo.s_path,fb.name);
		SetFileAttributes(fb.name, lAttrib);
	}
	else
	{
		remove(glo.s_path);
		retval=rdonly;
	}
	return retval;
}

//Get the Name of the Application
void CAntiVirusDlg::GetEFName(const char * ename)
{
	_getcwd(glo.buffer,_MAX_PATH);
	glo.efname.Format("%s\\%s.EXE", glo.buffer, ename);
	glo.efname.MakeUpper();
}

void CAntiVirusDlg::OnDblclkListReport() 
{
	int nSelection = SendDlgItemMessage(IDC_LIST_REPORT,LB_GETCURSEL);
	if( nSelection != LB_ERR )
	{
		CString szSelection;
		//m_lstScan.GetText( nSelection, szSelection );
		GetDlgItemText(IDC_LIST_REPORT,szSelection);
		MessageBox( szSelection, "Red Scan - v3.27 - by Vivek Jain - TheGhostOfC", MB_OK|MB_ICONINFORMATION);
	}
}

void CAntiVirusDlg::OnCancel() 
{
	if(!glo.bClose)
	{
		SuspendThread(m_pthread->m_hThread);
		if(MessageBox("This will Stop the Current Scanning, some or all of your files may still be infected by the Deadly HTML.RedLof.A Virus. Are you sure ?", "Are you sure ?", MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2)==IDYES)
		{
			TerminateThread(m_pthread->m_hThread, 0);
			InitDialog();
			SetDlgItemText(IDC_EDIT_PATH,"");
		}
		else
			ResumeThread(m_pthread->m_hThread);
		return;
	}
	CDialog::OnCancel();
}

//Scan the Destn folder
void CAntiVirusDlg::OnOK() 
{
	if(glo.bScan)
	{
		CString s, t;
		GetDlgItemText(IDC_EDIT_PATH,s);
		glo.sz_pathList.RemoveAll();
		while(s.Find(";",0)!=-1)
		{
			t=s.SpanExcluding(";");
			t.TrimRight();
			t.TrimLeft();
			glo.sz_pathList.Add(t);
			s.Delete(0,s.Find(";",0)+1);
		}
		if(s.GetLength()>0)
			glo.sz_pathList.Add(s);
		InitDialog();
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow(FALSE);
		SetDlgItemText(IDCANCEL,"S&top");
		GetDlgItem(IDC_BUTTON_BROWSE)->EnableWindow(FALSE);
		GetDlgItem(IDCANCEL)->SetFocus();
		glo.bClose=false;
		//Three Main Fn()s to Scan for the Virus
		ScanReg();//1 - Registry
		ScanDll();//2 - Kernel.Dll
		//SearchDirectory();//3 - Scan the Destn Folder
		m_pthread=AfxBeginThread(MainScan,(LPVOID)this,THREAD_PRIORITY_HIGHEST);
	}
	else
		InitDialog();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetWindowText("About Red Scan - v3.27");
	SetDlgItemText(IDC_STATIC_ABOUT,
		"Made by Vivek Jain - theGhostofC\n\nReport Bugs to vivek@vivek-jain.com\n\nCopyright (C) 2004");
	SetDlgItemText(IDC_STATIC_DESC,
		"This Product will protect You from the Deadly HTML.RedLof.A Virus\nJust select the Folder to Scan and Click on the &Scan Button\n\n(For Best Results, First Scan all the Disk Drives of your Computer)\nSo, Safe Protection and Happy Scanning - bye \t theGhostofC");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

LRESULT CAntiVirusDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	NOTIFYICONDATA nid;
	if(message==WM_USER && (UINT)lParam==WM_LBUTTONUP)
	{
		nid.cbSize=sizeof(nid);
		nid.hWnd=GetSafeHwnd();
		nid.uID=1;
		nid.uFlags=0;
		Shell_NotifyIcon(NIM_DELETE,&nid);
		ShowWindow(SW_RESTORE);
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CAntiVirusDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	NOTIFYICONDATA nid;
	nid.cbSize=sizeof(nid);
	nid.hWnd=GetSafeHwnd();
	nid.uID=1;
	nid.uFlags=0;
	Shell_NotifyIcon(NIM_DELETE,&nid);
	delete [] virdata;
	PostQuitMessage(0);	
}

void CAntiVirusDlg::OnSize(UINT nType, int cx, int cy) 
{
	NOTIFYICONDATA nid;
	if(nType==SIZE_MINIMIZED)
	{		
		nid.cbSize=sizeof(nid);
		nid.hWnd=GetSafeHwnd();
		nid.uID=1;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
		nid.uCallbackMessage=WM_USER;
		nid.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		strcpy(nid.szTip,"RedScan v3.27");
		ShowWindow(SW_HIDE);
		Shell_NotifyIcon(NIM_ADD,&nid);
	}
	else	
		CDialog::OnSize(nType, cx, cy);
}
