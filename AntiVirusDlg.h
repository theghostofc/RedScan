// AntiVirusDlg.h : header file
//

#if !defined(AFX_ANTIVIRUSDLG_H__60472FAD_9AFD_4334_8D43_913500FF57FD__INCLUDED_)
#define AFX_ANTIVIRUSDLG_H__60472FAD_9AFD_4334_8D43_913500FF57FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <io.h>
#include <fstream.h>

#define error -1
#define ok 1
#define novirus 4
#define rdonly 2
#define dleted 3

/////////////////////////////////////////////////////////////////////////////
// CAntiVirusDlg dialog

class CAntiVirusDlg : public CDialog
{
// Construction
public:
	CAntiVirusDlg(CWnd* pParent = NULL);	// standard constructor
	static void GetEFName(const char * ename);
	void Update(int retval);
	int Repair(_finddata_t f);
	void SearchDirectory();
	void ScanReport();
// Dialog Data
	//{{AFX_DATA(CAntiVirusDlg)
	enum { IDD = IDD_ANTIVIRUS_DIALOG };
	CStatic	m_de;
	CStatic	m_notrdata;
	CButton	m_btnOk;
	CButton	m_btnCancel;
	CStatic	m_deledata;
	CStatic	m_sc;
	CStatic	m_re;
	CStatic	m_no;
	CStatic	m_in;
	CButton	m_stReport;
	CButton	m_btnBrowse;
	CStatic	m_stPath;
	CListBox	m_lstScan;
	CStatic	m_stScan;
	CStatic	m_scandata;
	CStatic	m_repadata;
	CStatic	m_infedata;
	CEdit	m_path;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAntiVirusDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	char *virdata;
	CWinThread* m_pthread;
	void InitDialog();
	void ScanDll();
	int Del(_finddata_t fb);
	BOOL Init(UINT uIDRMap);
	// Generated message map functions
	//{{AFX_MSG(CAntiVirusDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	afx_msg void OnAbout();
	afx_msg void OnDblclkListReport();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEditPath();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANTIVIRUSDLG_H__60472FAD_9AFD_4334_8D43_913500FF57FD__INCLUDED_)
