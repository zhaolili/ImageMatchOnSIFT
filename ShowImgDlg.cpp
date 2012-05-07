// ShowImgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IMAGEMATCHOnSIFT.h"
#include "ShowImgDlg.h"
#include "DlgClose.h"
#include "IMAGEMATCHOnSIFTDlg.h"
#include <math.h>

#include "sift\siftdll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowImgDlg dialog


CShowImgDlg::CShowImgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShowImgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowImgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	nimgdata = NULL;
	nrgbdata = NULL;
	m_sifted = false;
	m_matched = false;
}


void CShowImgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowImgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowImgDlg, CDialog)
	//{{AFX_MSG_MAP(CShowImgDlg)
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowImgDlg message handlers

void CShowImgDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CWnd *pWnd = GetDlgItem(IDC_IMGDISPLAYER);		//得到图像控件的指针
	if (pWnd==NULL)
	{
		MessageBox("图像控件出错!");
		return;
	}
	CRect rect;
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	pWnd->MoveWindow(rect.left, rect.top, nwidth, nheight, true);
	
	CPaintDC pdc(pWnd);
	::SetStretchBltMode(pdc, COLORONCOLOR);

	//显示图像
	BITMAPINFOHEADER *bmpinfo = (BITMAPINFOHEADER *)(nimgdata + sizeof(BITMAPFILEHEADER));
	LPBITMAPINFO lpbmp = new BITMAPINFO;
	ZeroMemory(lpbmp, sizeof(BITMAPINFO));
	lpbmp->bmiHeader = *bmpinfo;
	//以下修改部分信息以适应新图像
	lpbmp->bmiHeader.biWidth = nwidth;
	lpbmp->bmiHeader.biHeight = nheight;
	lpbmp->bmiHeader.biSizeImage = 0;		//以BI_RGB压缩,而不管原始图像是gray还是RGB
	StretchDIBits(pdc.GetSafeHdc(),  0,  0, nwidth, nheight,0,0, nwidth, nheight, nrgbdata, lpbmp, DIB_RGB_COLORS,  SRCCOPY);  

	//将keypoint处显示出来
	if (m_sifted)
	{
		CIMAGEMATCHOnSIFTDlg *pPDlg = (CIMAGEMATCHOnSIFTDlg *)GetParent();
		int w1 = pPDlg->m_width1;
		int w2 = pPDlg->m_width2;
		int h1 = pPDlg->m_height1;
		int h2 = pPDlg->m_height2;
		int nhco = h1+h2-1;		//最后一行的行号
		int nw = (w1>w2) ? w1 : w2;

		CWnd *pWnd = GetDlgItem(IDC_IMGDISPLAYER);
		CClientDC dc(pWnd);
		CPen pen(PS_SOLID, 1, RGB(0,255,0));
		CPen *pOldpen = dc.SelectObject(&pen);
		dc.SelectStockObject(HOLLOW_BRUSH); 
	
		
		FeatureNode *node;
		Feature		*feat;
		int x,y,r;
		int bx, by, ex, ey;
		float len;
		r = 4;
		//image1
		node = pPDlg->featVect1->first;
		while (node!=NULL)
		{
			feat = node->feat;
/*			len = r*feat->sig_space;*/
			x = (int)(feat->ox+0.5);
			y = (int)(feat->oy+0.5);

			dc.MoveTo(x-r, y+h2);
			dc.LineTo(x+r, y+h2);
			dc.MoveTo(x, (y-r)+h2);
			dc.LineTo(x, (y+r)+h2);

// 			bx = x;
// 			by = nhco-y;
// 			ex = (int)(x+len*cos(feat->orient));
// 			ey = (int)(y-len*sin(feat->orient));
// 			ey = nhco-ey;
// 
// 			dc.MoveTo(bx, by);
// 			dc.LineTo(ex, ey);

// 			dc.MoveTo(x-r, nhco-y);
// 			dc.LineTo(x+r, nhco-y);
// 			dc.MoveTo(x, nhco-(y-r));
// 			dc.LineTo(x, nhco-(y+r));

			node = node->next;
		}		
		//image 2
		nhco = h2-1;
		node = pPDlg->featVect2->first;
		while (node!=NULL)
		{
			feat = node->feat;
		//	len = r*feat->sig_space;
			x = (int)(feat->ox+0.5);
			y = (int)(feat->oy+0.5);

			dc.MoveTo(x-r, y);
			dc.LineTo(x+r, y);
			dc.MoveTo(x, y-r);
			dc.LineTo(x, y+r);

// 			bx = x;
// 			by = nhco-y;
// 			ex = (int)(x+len*cos(feat->orient));
// 			ey = (int)(y-len*sin(feat->orient));
// 			ey = nhco-ey;
// 			
// 			dc.MoveTo(bx, by);
// 			dc.LineTo(ex, ey);
			
// 			dc.MoveTo(x-r, nhco-y);
// 			dc.LineTo(x+r, nhco-y);
// 			dc.MoveTo(x, nhco-(y-r));
// 			dc.LineTo(x, nhco-(y+r));

			node = node->next;
		}
		if (m_matched)
		{
			int k;
			int nhnum = pPDlg->m_height1 + pPDlg->m_height2 -1;
			int y10;
			int x10;
			int y20;
			int x20;
			
			CPen pen1(PS_SOLID, 1, RGB(255,0,0));
			CPen *pOldpen1 = dc.SelectObject(&pen1);
			for (k=0; k<pPDlg->m_matchednum; k++)
			{
				y10 = pPDlg->matchedcos[k][0][0];
				x10 = pPDlg->matchedcos[k][0][1];
				y20 = pPDlg->matchedcos[k][1][0];
				x20 = pPDlg->matchedcos[k][1][1];

				dc.MoveTo(x10, h2+y10);
				dc.LineTo(x20, y20);
				
// 				dc.MoveTo(x10, nhnum-y10);
// 				dc.LineTo(x20, pPDlg->m_height2-1-y20);
			}
			dc.SelectObject(pOldpen1);
		}
		dc.SelectObject(pOldpen);
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CShowImgDlg::SetImgInfo(int nw, int nh, int imgsize, BYTE *imgdata, BYTE *rgbdata)
{
	nwidth	= nw;
	nheight = nh;
	if (nrgbdata)
		delete[] nrgbdata;
	nrgbdata = new BYTE[imgsize];
	memcpy(nrgbdata, rgbdata, imgsize*sizeof(BYTE));		//拷贝图像数据

	nimgdata = imgdata;		//此处并不对nimgdata分配空间，只是让其指向imgdata
}

void CShowImgDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//
	CDlgClose dlg;
	int ret = dlg.DoModal();
	if (ret == IDCANCEL)
		return;
	if (ret == IDOK)
		;//do something on saving
	::DestroyWindow(this->m_hWnd);
	CDialog::OnClose();
}

void CShowImgDlg::OnDestroy() 
{
	/*释放空间*/
	if (nrgbdata)
		delete[] nrgbdata;
	nrgbdata = NULL;		//在删除了一个变量后，一定要让其指向null
	nimgdata = NULL;

	CIMAGEMATCHOnSIFTDlg *pPDlg = (CIMAGEMATCHOnSIFTDlg *)GetParent();
	if (pPDlg->featVect1)
	{
		free_feature_nodes(pPDlg->featVect1);
		pPDlg->featVect1 = NULL;
	}		
	if (pPDlg->featVect2)
	{
		free_feature_nodes(pPDlg->featVect2);
		pPDlg->featVect2 = NULL;
	}
		

	//将父对话框中的文本编辑框设为可写状态
	CWnd *pWnd = (CWnd *)GetWindow(GW_OWNER);
	CEdit *pEdit1 = (CEdit *)pWnd->GetDlgItem(IDC_EDITSELECTIMG1);
	CEdit *pEdit2 = (CEdit *)pWnd->GetDlgItem(IDC_EDITSELECTIMG2);

	if (pEdit1)
		pEdit1->SetReadOnly(false);
	if (pEdit2)
		pEdit2->SetReadOnly(false);

	pWnd->SetDlgItemText(IDC_EDITKEYPOINTSNUM1, "");
	pWnd->SetDlgItemText(IDC_EDITKEYPOINTSNUM2, "");
	pWnd->SetDlgItemText(IDC_EDITMATCHEDNUM, "");
	
	m_sifted = false;
	m_matched = false;

	CDialog::OnDestroy();
}

BOOL CShowImgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//改变图标
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONSHOWIMG)), TRUE);
	SetIcon(LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICONSHOWIMG)), FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowImgDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	SCROLLINFO scrollinfo; 
	GetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
	switch (nSBCode) 
	{ 
	case SB_BOTTOM: 
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMax)*50); 
		scrollinfo.nPos = scrollinfo.nMax; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_TOP: 
		ScrollWindow(0,(scrollinfo.nPos-scrollinfo.nMin)*50); 
		scrollinfo.nPos = scrollinfo.nMin; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_LINEUP: 
		scrollinfo.nPos -= 1; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,50); 
		break; 
	case SB_LINEDOWN: 
		scrollinfo.nPos += 1; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,-50); 
		break; 
	case SB_PAGEUP: 
		scrollinfo.nPos -= 5; 
		if (scrollinfo.nPos<scrollinfo.nMin) 
		{ 
			scrollinfo.nPos = scrollinfo.nMin; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,50*5); 
		break; 
	case SB_PAGEDOWN: 
		scrollinfo.nPos += 5; 
		if (scrollinfo.nPos>scrollinfo.nMax) 
		{ 
			scrollinfo.nPos = scrollinfo.nMax; 
			break; 
		} 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		ScrollWindow(0,-50*5); 
		break; 
	case SB_ENDSCROLL: 
		// MessageBox("SB_ENDSCROLL"); 
		break; 
	case SB_THUMBPOSITION: 
		// ScrollWindow(0,(scrollinfo.nPos-nPos)*10); 
		// scrollinfo.nPos = nPos; 
		// SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	case SB_THUMBTRACK: 
		ScrollWindow(0,(scrollinfo.nPos-nPos)*50); 
		scrollinfo.nPos = nPos; 
		SetScrollInfo(SB_VERT,&scrollinfo,SIF_ALL); 
		break; 
	}
	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
