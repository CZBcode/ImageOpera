// ImageOpera.h : main header file for the IMAGEOPERA application
//

#if !defined(AFX_IMAGEOPERA_H__DA9A4A1C_BEED_4680_84D2_C714274C92BD__INCLUDED_)
#define AFX_IMAGEOPERA_H__DA9A4A1C_BEED_4680_84D2_C714274C92BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CImageOperaApp:
// See ImageOpera.cpp for the implementation of this class
//

class CImageOperaApp : public CWinApp
{
public:
	CImageOperaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageOperaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CImageOperaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEOPERA_H__DA9A4A1C_BEED_4680_84D2_C714274C92BD__INCLUDED_)
