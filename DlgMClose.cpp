// DlgMClose.cpp : implementation file
//

#include "stdafx.h"
#include "IMAGEMATCHOnSIFT.h"
#include "DlgMClose.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMClose dialog


CDlgMClose::CDlgMClose(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMClose::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMClose)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMClose::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMClose)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMClose, CDialog)
	//{{AFX_MSG_MAP(CDlgMClose)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMClose message handlers
