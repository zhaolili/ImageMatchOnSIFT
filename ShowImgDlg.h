#if !defined(AFX_SHOWIMGDLG_H__059AD8BC_5155_4D57_BA79_3E7F9AF363BC__INCLUDED_)
#define AFX_SHOWIMGDLG_H__059AD8BC_5155_4D57_BA79_3E7F9AF363BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowImgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowImgDlg dialog

class CShowImgDlg : public CDialog
{
// Construction
public:
	bool m_matched;
	bool m_sifted;
	void SetImgInfo(int nw, int nh, int imgsize, BYTE *nimgdata, BYTE *rgbdata );
	CShowImgDlg(CWnd* pParent = NULL);   // standard constructor
	BYTE * nrgbdata;

// Dialog Data
	//{{AFX_DATA(CShowImgDlg)
	enum { IDD = IDD_IMGDISPLAYER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowImgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowImgDlg)
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BYTE * nimgdata;
	int nheight;
	int nwidth;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWIMGDLG_H__059AD8BC_5155_4D57_BA79_3E7F9AF363BC__INCLUDED_)
