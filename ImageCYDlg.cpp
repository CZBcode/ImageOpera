// ImageCYDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageOpera.h"
#include "ImageCYDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageCYDlg dialog


CImageCYDlg::CImageCYDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImageCYDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageCYDlg)
	m_xPlace = 0;
	m_yPlace = 0;
	//}}AFX_DATA_INIT
}


void CImageCYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageCYDlg)
	DDX_Text(pDX, IDC_EDIT_CYX, m_xPlace);
	DDX_Text(pDX, IDC_EDIT_CYY, m_yPlace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageCYDlg, CDialog)
	//{{AFX_MSG_MAP(CImageCYDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageCYDlg message handlers
