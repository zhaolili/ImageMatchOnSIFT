// DlgClose.cpp : implementation file
//

#include "stdafx.h"
#include "IMAGEMATCHOnSIFT.h"
#include "DlgClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClose dialog


CDlgClose::CDlgClose(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClose)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClose)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClose, CDialog)
	//{{AFX_MSG_MAP(CDlgClose)
	ON_BN_CLICKED(IDC_BUTTONNO, OnButtonno)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClose message handlers

void CDlgClose::OnButtonno() 
{	
	// TODO: Add your control notification handler code here
	EndDialog(0);		//关闭当前模态对话框
}

void CDlgClose::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnClose();
}
