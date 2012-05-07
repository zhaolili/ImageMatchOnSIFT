#if !defined(AFX_DLGCLOSE_H__BAE34D02_D53E_4275_BE7A_7AC31DDFD674__INCLUDED_)
#define AFX_DLGCLOSE_H__BAE34D02_D53E_4275_BE7A_7AC31DDFD674__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClose.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClose dialog

class CDlgClose : public CDialog
{
// Construction
public:
	CDlgClose(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgClose)
	enum { IDD = IDD_DIALOGCLOSE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClose)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClose)
	afx_msg void OnButtonno();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLOSE_H__BAE34D02_D53E_4275_BE7A_7AC31DDFD674__INCLUDED_)
