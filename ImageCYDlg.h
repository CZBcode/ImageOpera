#if !defined(AFX_IMAGECYDLG_H__9FE9A5A0_86E7_41A7_94CE_9F9495F95E08__INCLUDED_)
#define AFX_IMAGECYDLG_H__9FE9A5A0_86E7_41A7_94CE_9F9495F95E08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageCYDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageCYDlg dialog

class CImageCYDlg : public CDialog
{
// Construction
public:
	CImageCYDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImageCYDlg)
	enum { IDD = IDD_DIALOG_CY };
	int		m_xPlace;
	int		m_yPlace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageCYDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageCYDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGECYDLG_H__9FE9A5A0_86E7_41A7_94CE_9F9495F95E08__INCLUDED_)
