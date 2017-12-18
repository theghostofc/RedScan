// AntiVirus.h : main header file for the ANTIVIRUS application
//

#if !defined(AFX_ANTIVIRUS_H__66A2CDAE_A381_437E_B4D4_12A761A8466D__INCLUDED_)
#define AFX_ANTIVIRUS_H__66A2CDAE_A381_437E_B4D4_12A761A8466D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <afxtempl.h>

struct _global_
{
	//Store the Current Path
	char buffer[_MAX_PATH];
	//No. of Files Scanned
	unsigned int scanned;
	//No. of Files infected by the Virus
	unsigned int infected;
	//No. of Files Repaired
	unsigned int repaired;
	//No. of Files Not Repaired
	unsigned int not_repaired;
	//No. of Files Deleted
	unsigned int deleted;
	//Pathname of the Temp File
	char s_path[_MAX_PATH];
	//Exefile Name
	CString efname;
	//Scroll Scan or not
	bool bScan;
	//Cancelled or Not
	bool bClose;
};
static _global_ glo;//={0, 0, 0, 0, 0, 0, 0};
//static CString efname;
/////////////////////////////////////////////////////////////////////////////
// CAntiVirusApp:
// See AntiVirus.cpp for the implementation of this class
//

class CAntiVirusApp : public CWinApp
{
public:
	CAntiVirusApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntiVirusApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAntiVirusApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTIVIRUS_H__66A2CDAE_A381_437E_B4D4_12A761A8466D__INCLUDED_)
