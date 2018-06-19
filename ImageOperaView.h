// ImageOperaView.h : interface of the CImageOperaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEOPERAVIEW_H__C5C2C96B_70C1_4826_8DFB_0436BA987416__INCLUDED_)
#define AFX_IMAGEOPERAVIEW_H__C5C2C96B_70C1_4826_8DFB_0436BA987416__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageOperaCntrItem;

class CImageOperaView : public CView
{
protected: // create from serialization only
	CImageOperaView();
	DECLARE_DYNCREATE(CImageOperaView)

// Attributes
public:
	CImageOperaDoc* GetDocument();
	//��Ա����  
    CString BmpName;                               //����ͼ���ļ��ļ���  
    CString EntName;                               //����ͼ���ļ���չ��  
    CBitmap m_bitmap;                              //����λͼ����  
  
bool ReadBmp();                            //������ȡbmp���ֻ�ͼƬ  
    bool SaveBmp(LPCSTR lpFileName);           //��������bmp��ʽͼƬ  

    //��Ա����  
    void ShowBitmap(CDC* pDC,CString BmpName);    //������ʾָ��λͼbmp�ĺ��� 
	// m_pSelection holds the selection to the current CImageOperaCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CImageOperaCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
int m_nWidth;       //ͼ��ʵ�ʿ��  
    int m_nHeight;      //ͼ��ʵ�ʸ߶�  
    int m_nDrawWidth;   //ͼ����ʾ���  
    int m_nDrawHeight;  //ͼ����ʾ�߶�  
    DWORD m_nImage;     //ͼ�����ݵ��ֽ��� ֻ��λͼ  
    DWORD m_nSize;      //ͼ���ļ���С  
    int m_nLineByte;    //ͼ��һ����ռ�ֽ���  
    int m_nBitCount;    //ͼ��ÿ��������ռλ��  
    int m_nPalette;     //λͼʵ��ʹ�õ���ɫ���е���ɫ��  
      
    BYTE *m_pImage;         //����ͼƬ���ݺ��ָ��  
    BITMAPFILEHEADER bfh;   //ȫ�ֱ����ļ�ͷ  
    BITMAPINFOHEADER bih;   //ȫ�ֱ�����Ϣͷ  
    RGBQUAD m_pPal;         //��ɫ��ָ��  
	CImageOperaCntrItem* m_pSelection;

	CBitmap m_bitmaplin;   //������ʱλͼ������д���  
    CString BmpNameLin;    //����ͼ�񸱱��ļ�  

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageOperaView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageOperaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CImageOperaView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnShowTwo();
	afx_msg void OnShowHd();
	afx_msg void OnLh2();
	afx_msg void OnLh4();
	afx_msg void OnLh8();
	afx_msg void OnLh16();
	afx_msg void OnLh32();
	afx_msg void OnLh64();
	afx_msg void OnCy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ImageOperaView.cpp
inline CImageOperaDoc* CImageOperaView::GetDocument()
   { return (CImageOperaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEOPERAVIEW_H__C5C2C96B_70C1_4826_8DFB_0436BA987416__INCLUDED_)
