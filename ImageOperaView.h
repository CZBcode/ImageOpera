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
	//成员变量  
    CString BmpName;                               //保存图像文件文件名  
    CString EntName;                               //保存图像文件扩展名  
    CBitmap m_bitmap;                              //创建位图对象  
  
bool ReadBmp();                            //用来读取bmp个手机图片  
    bool SaveBmp(LPCSTR lpFileName);           //用来保存bmp格式图片  

    //成员函数  
    void ShowBitmap(CDC* pDC,CString BmpName);    //用来显示指定位图bmp的函数 
	// m_pSelection holds the selection to the current CImageOperaCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CImageOperaCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
int m_nWidth;       //图像实际宽度  
    int m_nHeight;      //图像实际高度  
    int m_nDrawWidth;   //图像显示宽度  
    int m_nDrawHeight;  //图像显示高度  
    DWORD m_nImage;     //图像数据的字节数 只含位图  
    DWORD m_nSize;      //图像文件大小  
    int m_nLineByte;    //图像一行所占字节数  
    int m_nBitCount;    //图像每个像素所占位数  
    int m_nPalette;     //位图实际使用的颜色表中的颜色数  
      
    BYTE *m_pImage;         //读入图片数据后的指针  
    BITMAPFILEHEADER bfh;   //全局变量文件头  
    BITMAPINFOHEADER bih;   //全局变量信息头  
    RGBQUAD m_pPal;         //颜色表指针  
	CImageOperaCntrItem* m_pSelection;

	CBitmap m_bitmaplin;   //创建临时位图对象进行处理  
    CString BmpNameLin;    //保存图像副本文件  

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
