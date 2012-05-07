#if !defined(AFX_DLGMCLOSE_H__0B5BC2CF_1510_49F8_94D1_1953A8B60692__INCLUDED_)
#define AFX_DLGMCLOSE_H__0B5BC2CF_1510_49F8_94D1_1953A8B60692__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMClose.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMClose dialog

class CDlgMClose : public CDialog
{
// Construction
public:
	CDlgMClose(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMClose)
	enum { IDD = IDD_DIALOGMCLOSE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMClose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMClose)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMCLOSE_H__0B5BC2CF_1510_49F8_94D1_1953A8B60692__INCLUDED_)
