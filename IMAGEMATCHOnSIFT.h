// IMAGEMATCHOnSIFT.h : main header file for the IMAGEMATCHONSIFT application
//

#if !defined(AFX_IMAGEMATCHONSIFT_H__872B4C06_BD29_44B4_9822_95D9DC4B6EB8__INCLUDED_)
#define AFX_IMAGEMATCHONSIFT_H__872B4C06_BD29_44B4_9822_95D9DC4B6EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIMAGEMATCHOnSIFTApp:
// See IMAGEMATCHOnSIFT.cpp for the implementation of this class
//

class CIMAGEMATCHOnSIFTApp : public CWinApp
{
public:
	CIMAGEMATCHOnSIFTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIMAGEMATCHOnSIFTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIMAGEMATCHOnSIFTApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEMATCHONSIFT_H__872B4C06_BD29_44B4_9822_95D9DC4B6EB8__INCLUDED_)
