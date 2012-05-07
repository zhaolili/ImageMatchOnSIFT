// IMAGEMATCHOnSIFTDlg.h : header file
//

#if !defined(AFX_IMAGEMATCHONSIFTDLG_H__D33100F1_90C4_45F7_96B2_A1797478BB98__INCLUDED_)
#define AFX_IMAGEMATCHONSIFTDLG_H__D33100F1_90C4_45F7_96B2_A1797478BB98__INCLUDED_

#include "ShowImgDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sift/siftdll.h"			//added manually by author ZhaoLili

/////////////////////////////////////////////////////////////////////////////
// CIMAGEMATCHOnSIFTDlg dialog

class CIMAGEMATCHOnSIFTDlg : public CDialog
{
// Construction
public:
	void HeadStand(int width, int height, BYTE *imgbuf);
	int m_showdlgh;
	FeatureVect * featVect2;
	FeatureVect * featVect1;
	int (*matchedcos)[2][2];
	int m_matchednum;
	void DrawMatchedLine();
	void mem4D_free(double ****arr, int h, int w, int o);
	int mem4D_alloc(double *****arr, int h, int w, int o, int b);
	void mem3D_free(double ***arr, int h, int w);
	int mem3D_alloc(double ****arr, int h, int w, int o);
	void mem2D_free(double **arr, int h);
	int mem2D_alloc(double *** arr, int h, int w);
	CIMAGEMATCHOnSIFTDlg(CWnd* pParent = NULL);	// standard constructor

	int m_height2;
	int m_height1;
	int m_width2;
	int m_width1;

// Dialog Data
	//{{AFX_DATA(CIMAGEMATCHOnSIFTDlg)
	enum { IDD = IDD_IMAGEMATCHONSIFT_DIALOG };
	CComboBox	m_COMBOMiniRes;
	CEdit	m_EDITCD;
	CSliderCtrl	m_SLIDERCD;
	CEdit	m_EDITIS;
	CSliderCtrl	m_SLIDERIS;
	CEdit	m_EDITSLTIMG2;
	CEdit	m_EDITSLTIMG1;
	CComboBox	m_COMBOMT;
	CComboBox	m_COMBOSDR;
	CComboBox	m_COMBOBD;
	CComboBox	m_COMBOGWS;
	CString	m_sltImg1;
	CString	m_sltImg2;
	int		m_gws;
	int		m_bd;
	int		m_sdr;
	int		m_mt;
	CString	m_is;
	CString	m_cd;
	int		m_miniRes;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMAGEMATCHOnSIFTDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIMAGEMATCHOnSIFTDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonselectimg1();
	afx_msg void OnButtonselectimg2();
	afx_msg void OnMaxtextEditselectimg1();
	afx_msg void OnMaxtextEditselectimg2();
	afx_msg void OnCustomdrawSlideris(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlidercd(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg int OnButtonshowimg();
	afx_msg void OnButtonclear();
	afx_msg void OnButtonfd();
	afx_msg void OnSelchangeCombogws();
	afx_msg void OnSelchangeCombobd();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnDropdownCombogws();
	afx_msg void OnButtonmatch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	FeatureVect* CIMAGEMATCHOnSIFTDlg::sifting(int w, int h, BYTE *graydata, float wid, int db_img, float sigma0,\
										   float sigman, float contr_thr, int sift_border, float norm_thresh, int top_oct_res);
	void ShowKeypoints(int img);
	BYTE * m_graydata2;
	BYTE * m_graydata1;
	void ShowImage();
	CShowImgDlg dspDlg;
//	BYTE * m_newdata;
	BYTE * m_imgdata2;

	bool LoadSrcImg(CString fpathname, int img);
	BYTE * m_imgdata1;
	BYTE * m_orgdata2;
	BYTE * m_orgdata1;
	CString m_img2path;
	CString m_img1path;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEMATCHONSIFTDLG_H__D33100F1_90C4_45F7_96B2_A1797478BB98__INCLUDED_)
