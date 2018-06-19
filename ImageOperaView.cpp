// ImageOperaView.cpp : implementation of the CImageOperaView class
//

#include "stdafx.h"
#include "ImageOpera.h"
#include "ImageCYDlg.h"
#include "ImageOperaDoc.h"
#include "CntrItem.h"
#include "ImageOperaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView

IMPLEMENT_DYNCREATE(CImageOperaView, CView)

BEGIN_MESSAGE_MAP(CImageOperaView, CView)
	//{{AFX_MSG_MAP(CImageOperaView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_SHOW_TWO, OnShowTwo)
	ON_COMMAND(ID_SHOW_HD, OnShowHd)
	ON_COMMAND(ID_LH_2, OnLh2)
	ON_COMMAND(ID_LH_4, OnLh4)
	ON_COMMAND(ID_LH_8, OnLh8)
	ON_COMMAND(ID_LH_16, OnLh16)
	ON_COMMAND(ID_LH_32, OnLh32)
	ON_COMMAND(ID_LH_64, OnLh64)
	ON_COMMAND(ID_CY, OnCy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView construction/destruction

CImageOperaView::CImageOperaView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CImageOperaView::~CImageOperaView()
{
}

BOOL CImageOperaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView drawing

void CImageOperaView::OnDraw(CDC* pDC)
{
	CImageOperaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)  
        return;  
  
    // TODO: 在此处为本机数据添加绘制代码  
  
    if( EntName.Compare(_T("bmp")) == 0 )      //bmp格式  
    {  
		ReadBmp();
        ShowBitmap(pDC,BmpName);               //显示图片  
    }  
	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CImageOperaCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.
/*
	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CImageOperaCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));

  */
}

void CImageOperaView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView printing

BOOL CImageOperaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageOperaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageOperaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CImageOperaView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CImageOperaView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CImageOperaCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CImageOperaView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CImageOperaCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CImageOperaCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CImageOperaDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CImageOperaCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CImageOperaView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CImageOperaView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CImageOperaView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView diagnostics

#ifdef _DEBUG
void CImageOperaView::AssertValid() const
{
	CView::AssertValid();
}

void CImageOperaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageOperaDoc* CImageOperaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageOperaDoc)));
	return (CImageOperaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageOperaView message handlers
/*************************************************************/  
/* numPicture变量显示图片数量 
/* 0-提示错误或未打开图片 1-显示一张图片 2-显示两张图片和处理 
/*************************************************************/  
int numPicture = 0;  
  
/*************************************************************/  
/* level变量显示具体的处理操作，每个处理函数中赋值该变量 
/* 0-显示2张图片 1-显示灰度图片 3-显示图片采样 
/* 2 4 8 16 32 64-不同量化等级量化图片 
/*************************************************************/   
int level = 0;      
  
//****************显示BMP格式图片****************//  
void CImageOperaView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	//四种格式的文件：bmp gif jpg tiff  
    CString filter;  
    filter="所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);   
	
  
    //按下确定按钮 dlg.DoModal() 函数显示对话框  
    if( dlg.DoModal() == IDOK )  
    {  
        BmpName = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp  
		BmpNameLin = "picture.bmp";      //临时变量名  
        numPicture=1;                    //显示一张图片  
        EntName = dlg.GetFileExt();      //获取文件扩展名  
        EntName.MakeLower();             //将文件扩展名转换为一个小写字符  
        Invalidate();                    //调用该函数就会调用OnDraw重绘画图  
    }  
}

void CImageOperaView::ShowBitmap(CDC *pDC, CString BmpName)  
{  
    //定义bitmap指针 调用函数LoadImage装载位图  
    HBITMAP m_hBitmap;  
    m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
          
    /*************************************************************************/  
    /* 1.要装载OEM图像，则设此参数值为0  OBM_ OEM位图 OIC_OEM图标 OCR_OEM光标 
    /* 2.BmpName要装载图片的文件名                   
    /* 3.装载图像类型:  
    /*   IMAGE_BITMAP-装载位图 IMAGE_CURSOR-装载光标 IMAGE_ICON-装载图标     
    /* 4.指定图标或光标的像素宽度和长度 以像素为单位     
    /* 5.加载选项: 
    /*   IR_LOADFROMFILE-指明由lpszName指定文件中加载图像 
    /*   IR_DEFAULTSIZE-指明使用图像默认大小 
    /*   LR_CREATEDIBSECTION-当uType参数为IMAGE_BITMAP时,创建一个DIB项 
    /**************************************************************************/  
  
    if( m_bitmap.m_hObject )  
    {  
        m_bitmap.Detach();           //切断CWnd和窗口联系  
    }  
    m_bitmap.Attach(m_hBitmap);      //将句柄HBITMAP m_hBitmap与CBitmap m_bitmap关联  
      
    //边界  
    CRect rect;  
    GetClientRect(&rect);  
  
    //图片显示(x,y)起始坐标  
    int m_showX=0;  
    int m_showY=0;  
    int m_nWindowWidth = rect.right - rect.left;   //计算客户区宽度  
    int m_nWindowHeight = rect.bottom - rect.top;  //计算客户区高度  
          
    //定义并创建一个内存设备环境DC  
    CDC dcBmp;  
    if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC  
        return;  
      
    BITMAP m_bmp;                          //临时bmp图片变量  
    m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中  
      
    CBitmap *pbmpOld = NULL;        
    dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境  
      
    //图片显示调用函数stretchBlt  
    pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  
      
    /*******************************************************************************/  
    /* BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC,  
    /*                 int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop ); 
    /* 1.参数x、y位图目标矩形左上角x、y的坐标值       
    /* 2.nWidth、nHeigth位图目标矩形的逻辑宽度和高度       
    /* 3.pSrcDC表示源设备CDC指针                           
    /* 4.xSrc、ySrc表示位图源矩形的左上角的x、y逻辑坐标值  
    /* 5.dwRop表示显示位图的光栅操作方式 SRCCOPY用于直接将位图复制到目标环境中             
    /*******************************************************************************/  
      
    dcBmp.SelectObject(pbmpOld);           //恢复临时DC的位图  
    DeleteObject(&m_bitmap);               //删除内存中的位图  
    dcBmp.DeleteDC();                      //删除CreateCompatibleDC得到的图片DC  

	if(numPicture==2) {  
        //显示图片函数LoadImage  
        HBITMAP m_hBitmapChange;  
       if(level==0) //显示2张图 BmpNameLin原图  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else  
if(level==1) //灰度图片 BmpNameLin临时图片  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //量化2  
if(level==2)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
} 
  else if(level==3) //图片采样
 {
          m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
                 LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
  } 
else         //量化4  
if(level==4)    
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //量化8  
if(level==8)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //量化16  
if(level==16)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //量化32  
if(level==32)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //量化64  
if(level==64)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}    
        if( m_bitmap.m_hObject ) {  
            m_bitmap.Detach();            //m_bitmap为创建的位图对象  
        }  
        m_bitmap.Attach(m_hBitmapChange);  
        //定义并创建一个内存设备环境  
        CDC dcBmp;  
        if( !dcBmp.CreateCompatibleDC(pDC) )   //创建兼容性的DC  
            return;  
        BITMAP m_bmp;                          //临时bmp图片变量  
        m_bitmap.GetBitmap(&m_bmp);            //将图片载入位图中  
        CBitmap *pbmpOld = NULL;  
        dcBmp.SelectObject(&m_bitmap);         //将位图选入临时内存设备环境  
  
        //如果图片太大显示大小为固定640*640 否则显示原图大小  
        if(m_nDrawWidth<650 && m_nDrawHeight<650)  
            pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,  
                m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  
        else  
            pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,  
                m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);   


        //恢复临时DC的位图  
        dcBmp.SelectObject(pbmpOld);   
		

    }  

  
}  

bool CImageOperaView::ReadBmp()  
{  
    //图片读出存储其中的东西  
    FILE *fp = fopen(BmpName,"rb");  
    if(fp==0)  
    {         
        AfxMessageBox("无法打开文件!",MB_OK,0);  
        return 0;   
    }  
    //读取文件头 解决BMP格式倒置的方法  
    fread(&bfh.bfType,sizeof(WORD),1,fp);  
    fread(&bfh.bfSize,sizeof(DWORD),1,fp);  
    fread(&bfh.bfReserved1,sizeof(WORD),1,fp);  
    fread(&bfh.bfReserved2,sizeof(WORD),1,fp);  
    fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);  
    //图像文件的总字节数  
    m_nSize = bfh.bfSize;  
    //判断是否是bmp格式图片  
    if(bfh.bfType!=0x4d42)   //'BM'  
    {  
        AfxMessageBox("不是BMP格式图片!",MB_OK,0);  
        return 0;  
    }  
    //读取信息头  
    fread(&bih.biSize,sizeof(DWORD),1,fp);  
    fread(&bih.biWidth,sizeof(LONG),1,fp);  
    fread(&bih.biHeight,sizeof(LONG),1,fp);  
    fread(&bih.biPlanes,sizeof(WORD),1,fp);  
    fread(&bih.biBitCount,sizeof(WORD),1,fp);  
    fread(&bih.biCompression,sizeof(DWORD),1,fp);  
    fread(&bih.biSizeImage,sizeof(DWORD),1,fp);  
    fread(&bih.biXPelsPerMeter,sizeof(LONG),1,fp);  
    fread(&bih.biYPelsPerMeter,sizeof(LONG),1,fp);  
    fread(&bih.biClrUsed,sizeof(DWORD),1,fp);  
    fread(&bih.biClrImportant,sizeof(DWORD),1,fp);  
    if(bih.biSize!=sizeof(bih))  
    {  
        AfxMessageBox("本结构所占用字节数出现错误");  
        return 0;  
    }  
    //位图压缩类型，必须是 0（不压缩） 1（BI_RLE8压缩类型）或2（BI_RLE压缩类型）之一  
    if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)  
    {  
        AfxMessageBox("位图被压缩!");  
        return 0;  
    }  
    //获取图像高宽和每个像素所占位数  
    m_nHeight = bih.biHeight;  
    m_nWidth = bih.biWidth;  
    m_nDrawHeight = bih.biHeight;  
    m_nDrawWidth = bih.biWidth;  
    m_nBitCount = bih.biBitCount;   //每个像素所占位数  
    //计算图像每行像素所占的字节数（必须是32的倍数）  
    m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;  
    //图片大小 调用系统自带的文件头 BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih;   
    //否则用 BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;要 m_nImage = m_nLineByte * m_nHeight - 2;  
    m_nImage = m_nLineByte * m_nHeight;  
    //位图实际使用的颜色表中的颜色数 biClrUsed  
    m_nPalette = 0;                       //初始化  
    if(bih.biClrUsed)  
        m_nPalette = bih.biClrUsed;  
    //申请位图空间 大小为位图大小 m_nImage  
    //malloc只能申请4字节的空间 （未知）  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fp);  
    fclose(fp);  
    return true;  
}  
bool CImageOperaView::SaveBmp(LPCSTR lpFileName) //lpFileName为位图文件名  
{  
    //保存bmp格式图片 写图片过程 只处理24像素的图片 该图片无调色板  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(lpFileName,"wb");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //malloc只能申请4字节的空间 （未知）  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    return true;  
}  

void CImageOperaView::OnFileSave() 
{
	// TODO: Add your command handler code here
	CString filter;  
    filter="所有文件(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";  
    //重点: 1-文件打开 0-文件保存  
    CFileDialog dlg(0,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);     
    //按下确定按钮  
    if( dlg.DoModal() == IDOK ) {  
        CString str;  
        CString strName;  
        CString filename;  
        str = dlg.GetPathName();           //获取文件的路径  
        filename = dlg.GetFileTitle();     //获取文件名  
        int nFilterIndex=dlg.m_ofn.nFilterIndex;  
        if( nFilterIndex == 2 )            //当用户选择文件过滤器为".BMP"时  
        {  
            str = str + ".bmp";            //自动加扩展名.bmp  
            SaveBmp(str);                  //保存bmp图片 就是一个写出图片的过程   
            AfxMessageBox("图片保存成功",MB_OK,0);  
        }  
    }  
}

void CImageOperaView::OnShowTwo() 
{
//如果没有导入图片直接点击双显 提示错误  
    if(numPicture==0)  
    {  
        AfxMessageBox("载入图片后才能显示2张图片!");  
        return;  
    }  
    AfxMessageBox("显示两张图片!",MB_OK,0);  
    numPicture = 2;    //全局变量 显示两图  
    level =0;          //level=0双显  
    Invalidate();      //调用Invalidate 每秒调用一次OnDraw画图  	
}
/********************************************************************************************/                    
/* 其中24位的图片灰度时,采用如下算法:                                                        
/* 1.平均值算法 R=G=B=(R+G+B)/3                                                               
/* 2.快速算法 R=G=B=(R+G+B+128)/4>>2                                                           
/* 3.加权平均值算法 根据光的亮度特性,其实正确的灰度公式应当是R=G=B=R*0.299+G*0.587+B0.144    
/*   为了提高速度我们做一个完全可以接受的近似，公式变形如下 R=G=B=(R*3+G*6+B)/10             
/* 4.精确加权平均值算法 R=G=B=R*0.299+G*0.587+B0.144                                         
/********************************************************************************************/  
//**灰度图像就是 R=G=B且为三者的1/3 level=1时灰度图像**//  
void CImageOperaView::OnShowHd() 
{
	// TODO: Add your command handler code here
	if(numPicture==0)  
    {  
        AfxMessageBox("载入图片后才能灰度图片!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("灰度图像!",MB_OK,0);  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //读取文件  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //灰度图像  
    unsigned char color;  
    unsigned char red,green,blue;  
  
    /********************************************************************/  
    /* 注意：原来下面所有操作都是for( i=0; i<m_nWidth*m_nHeight; i++ )   
    /* 后发现如果图片最后一行没有完整的一行数据，会出现图像变多或变少    
    /* 但图像的总像素为m_nImage，如果是m_nImage/3就可以保证所有像素都有  
    /********************************************************************/  
  
    for(int i=0; i < m_nImage/3; i++ )  
    {  
        fread(&red,sizeof(char),1,fpo);  
        fread(&green,sizeof(char),1,fpo);  
        fread(&blue,sizeof(char),1,fpo);  
  
    //    color=(red+green+blue)/3;   //平均值算法
		color=(red*3+green*6+blue)/10  ;//加权平均值算法
		
        red=color;  
        green=color;    
        blue=color;  
  
        fwrite(&red,sizeof(char),1,fpw);  
        fwrite(&green,sizeof(char),1,fpw);  
        fwrite(&blue,sizeof(char),1,fpw);  
    }  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=1;  
    Invalidate();  
}

//****************量化 量化等级为2****************//
/*
*核心流程是打开两张图片原图(BmpName)和临时图片(BmpNameLin)，然后读取原图信息头赋值给临时处理图片，
在读取原图m_nImage整个像素矩阵，量化处理每个像素（即分等级量化），最后文件写量化后的像素矩阵给BmpNameLin，
在赋值全局变量level\numPicture和调用Invalidate()重绘图像即可。
*/
void CImageOperaView::OnLh2() 
{
	// TODO: Add your command handler code here
	 if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=2!",MB_OK,0);  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //读取文件  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //malloc只能申请4字节的空间  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //等级2量化  
    for(int i=0; i<m_nImage; i++ ) {  
        //24位的为调色板为真彩图 Red Green Blue 为3字节   
        //量化等级为2取中间值为 64 和 192  
        if(m_pImage[i]<128) {   
            m_pImage[i]=0;  
        }  
        else if(m_pImage[i]>=128) {  
            m_pImage[i]=128;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=2;  
    Invalidate();  
}

void CImageOperaView::OnLh4() 
{
	// TODO: Add your command handler code here
	 if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=4!",MB_OK,0);  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //等级4量化  
    for(int i=0; i<m_nImage; i++ ) {  
        if(m_pImage[i]<64) {  
            m_pImage[i]=0;  
        }  
        else if( (m_pImage[i]>=64) && (m_pImage[i]<128) ) {  
            m_pImage[i]=64;  
        }  
        else if( (m_pImage[i]>=128) && (m_pImage[i]<192) ) {  
            m_pImage[i]=128;  
        }  
        else if(m_pImage[i]>=192) {  
            m_pImage[i]=192;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=4;  
    Invalidate();  
}

void CImageOperaView::OnLh8() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=8!",MB_OK,0);  
    //打开临时的图片 读取文件  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //malloc只能申请4字节的空间 （未知）  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //等级8量化  
    for(int i=0; i<m_nImage; i++ ) {  
        if(m_pImage[i]<32) {  
            m_pImage[i]=0;  
        }  
        else if( (m_pImage[i]>=32) && (m_pImage[i]<64) ) {  
            m_pImage[i]=32;  
        }  
        else if( (m_pImage[i]>=64) && (m_pImage[i]<96) ) {  
            m_pImage[i]=64;  
        }  
        else if( (m_pImage[i]>=96) && (m_pImage[i]<128) ) {  
            m_pImage[i]=96;  
        }  
        else if( (m_pImage[i]>=128) && (m_pImage[i]<160) ) {  
            m_pImage[i]=128;  
        }  
        else if( (m_pImage[i]>=160) && (m_pImage[i]<192) ) {  
            m_pImage[i]=160;  
        }  
        else if( (m_pImage[i]>=192) && (m_pImage[i]<224) ) {  
            m_pImage[i]=192;  
        }  
        else if(m_pImage[i]>=224) {  
            m_pImage[i]=224;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=8;  
    Invalidate();  
}

void CImageOperaView::OnLh16() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=16!",MB_OK,0);  
    int i,j;  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    for( i=0; i<m_nImage; i++ ) {  
        j=16;  
        while(j<=256)  
        {  
            if(m_pImage[i]<j)   
            {  
                if(m_pImage[i]<16)   
                    m_pImage[i]=0;  
                else   
                    m_pImage[i]=j-16;  
                break;  
            }  
            else j+=16;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=16;  
    Invalidate();  
}

void CImageOperaView::OnLh32() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=32!",MB_OK,0);  
    int i,j;  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //读取文件  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //等级32化  
    for( i=0; i<m_nImage; i++ )  
    {  
        j=8;  
        while(j<=256)  
        {  
            if(m_pImage[i]<j)   
            {  
                if(m_pImage[i]<8)   
                    m_pImage[i]=0;  
                else   
                    m_pImage[i]=j-8;  
                break;  
            }  
            else j+=8;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=32;  
    Invalidate();  
}

void CImageOperaView::OnLh64() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {  
        AfxMessageBox("载入图片后才能量化!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("量化等级Level=64!",MB_OK,0);  
    int i,j;  
    //打开临时的图片  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //读取文件  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //等级64量化  
    for( i=0; i<m_nImage; i++ )  
    {  
        j=4;  
        while(j<=256)  
        {  
            if(m_pImage[i]<j)   
            {  
                if(m_pImage[i]<16)   
                    m_pImage[i]=0;  
                else   
                    m_pImage[i]=j-4;  
                break;  
            }  
            else j+=4;  
        }  
    }  
    fwrite(m_pImage,m_nImage,1,fpw);  
    fclose(fpo);  
    fclose(fpw);  
    numPicture = 2;  
    level=64;  
    Invalidate();  
}

void CImageOperaView::OnCy() 
{
	// TODO: Add your command handler code here
	if(numPicture==0) {  
        AfxMessageBox("载入图片后才能采样!",MB_OK,0);  
        return;  
    }  
    CImageCYDlg dlg;     //定义采样对话框  
    //显示对话框  
    if( dlg.DoModal()==IDOK ) {  
        //采样坐标最初为图片的自身像素  
        if( dlg.m_xPlace==0 || dlg.m_yPlace==0 ) {  
            AfxMessageBox("输入图片像素不能为0!",MB_OK,0);  
            return;  
        }  
        if( dlg.m_xPlace>m_nWidth || dlg.m_yPlace>m_nHeight ) {  
            AfxMessageBox("图片像素不能为超过原图长宽!",MB_OK,0);  
            return;  
        }  
        AfxMessageBox("图片采样!",MB_OK,0);  
        //打开临时的图片 读取文件  
        FILE *fpo = fopen(BmpName,"rb");  
        FILE *fpw = fopen(BmpNameLin,"wb+");  
        fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
        fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
        fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
        fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
        fread(m_pImage,m_nImage,1,fpo);  
      
        /*图片采样*/  
        int numWidth,numHeight;     //图片此区间取相同的像素点  
        int numSYWidth,numSYHeight; //剩余期间区域   
  
        /*********************************************************/  
        /* 表示numWidth*numHeight为一个区域 该区域颜色相同        
        /* 如 512/512=1 512/512=1 1*1为一个区域                   
        /* dlg.m_xPlace*dlg.m_yPlace 表示新的（x,y）坐标          
        /* numSYWidth表示剩余空间 该区域统一为一个颜色            
        /*********************************************************/  
  
        numWidth=m_nWidth/dlg.m_xPlace;          
        numHeight=m_nHeight/dlg.m_yPlace;        
        numSYWidth=m_nWidth%dlg.m_xPlace;       
        numSYHeight=m_nHeight%dlg.m_yPlace;     
        int Y,X;  
        int i,j,m,n;  
        unsigned char red,green,blue;  //存储三种颜色  
      
        /* 有((m_xPlace * m_yPlace)+ 剩余区域 )个小区域 */  
        for( i=0; i<dlg.m_yPlace; i++ )       //高度  
        {  
            Y=numHeight*i;                    //获取Y坐标  
            for( j=0; j<dlg.m_yPlace; j++ )   //宽度  
            {  
                X=numWidth*j;                 //获取X坐标  
                /*获取填充颜色*/  
                red=m_pImage[(X+Y*m_nWidth)*3];  
                green=m_pImage[(X+Y*m_nWidth)*3+1];  
                blue=m_pImage[(X+Y*m_nWidth)*3+2];  
                /*填出图像循环 小区域中的长宽循环*/  
                for( n=0; n<numHeight; n++ )  
                {  
                    for( m=0; m<numWidth*3; )  
                    {  
                        m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=red;  
                        m++;  
                        m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=green;  
                        m++;  
                        m_pImage[(X+Y*m_nWidth)*3+m+n*m_nWidth*3]=blue;  
                        m++;  
                    }  
                }  
            }  
        }  
        fwrite(m_pImage,m_nImage,1,fpw);  
        fclose(fpo);  
        fclose(fpw);  
        numPicture = 2;  
        level=3;  
        Invalidate();  
    }  
}
