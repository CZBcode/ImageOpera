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
  
    // TODO: �ڴ˴�Ϊ����������ӻ��ƴ���  
  
    if( EntName.Compare(_T("bmp")) == 0 )      //bmp��ʽ  
    {  
		ReadBmp();
        ShowBitmap(pDC,BmpName);               //��ʾͼƬ  
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
/* numPicture������ʾͼƬ���� 
/* 0-��ʾ�����δ��ͼƬ 1-��ʾһ��ͼƬ 2-��ʾ����ͼƬ�ʹ��� 
/*************************************************************/  
int numPicture = 0;  
  
/*************************************************************/  
/* level������ʾ����Ĵ��������ÿ���������и�ֵ�ñ��� 
/* 0-��ʾ2��ͼƬ 1-��ʾ�Ҷ�ͼƬ 3-��ʾͼƬ���� 
/* 2 4 8 16 32 64-��ͬ�����ȼ�����ͼƬ 
/*************************************************************/   
int level = 0;      
  
//****************��ʾBMP��ʽͼƬ****************//  
void CImageOperaView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	//���ָ�ʽ���ļ���bmp gif jpg tiff  
    CString filter;  
    filter="�����ļ�(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";  
    CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);   
	
  
    //����ȷ����ť dlg.DoModal() ������ʾ�Ի���  
    if( dlg.DoModal() == IDOK )  
    {  
        BmpName = dlg.GetPathName();     //��ȡ�ļ�·����   ��D:\pic\abc.bmp  
		BmpNameLin = "picture.bmp";      //��ʱ������  
        numPicture=1;                    //��ʾһ��ͼƬ  
        EntName = dlg.GetFileExt();      //��ȡ�ļ���չ��  
        EntName.MakeLower();             //���ļ���չ��ת��Ϊһ��Сд�ַ�  
        Invalidate();                    //���øú����ͻ����OnDraw�ػ滭ͼ  
    }  
}

void CImageOperaView::ShowBitmap(CDC *pDC, CString BmpName)  
{  
    //����bitmapָ�� ���ú���LoadImageװ��λͼ  
    HBITMAP m_hBitmap;  
    m_hBitmap = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
          
    /*************************************************************************/  
    /* 1.Ҫװ��OEMͼ������˲���ֵΪ0  OBM_ OEMλͼ OIC_OEMͼ�� OCR_OEM��� 
    /* 2.BmpNameҪװ��ͼƬ���ļ���                   
    /* 3.װ��ͼ������:  
    /*   IMAGE_BITMAP-װ��λͼ IMAGE_CURSOR-װ�ع�� IMAGE_ICON-װ��ͼ��     
    /* 4.ָ��ͼ���������ؿ�Ⱥͳ��� ������Ϊ��λ     
    /* 5.����ѡ��: 
    /*   IR_LOADFROMFILE-ָ����lpszNameָ���ļ��м���ͼ�� 
    /*   IR_DEFAULTSIZE-ָ��ʹ��ͼ��Ĭ�ϴ�С 
    /*   LR_CREATEDIBSECTION-��uType����ΪIMAGE_BITMAPʱ,����һ��DIB�� 
    /**************************************************************************/  
  
    if( m_bitmap.m_hObject )  
    {  
        m_bitmap.Detach();           //�ж�CWnd�ʹ�����ϵ  
    }  
    m_bitmap.Attach(m_hBitmap);      //�����HBITMAP m_hBitmap��CBitmap m_bitmap����  
      
    //�߽�  
    CRect rect;  
    GetClientRect(&rect);  
  
    //ͼƬ��ʾ(x,y)��ʼ����  
    int m_showX=0;  
    int m_showY=0;  
    int m_nWindowWidth = rect.right - rect.left;   //����ͻ������  
    int m_nWindowHeight = rect.bottom - rect.top;  //����ͻ����߶�  
          
    //���岢����һ���ڴ��豸����DC  
    CDC dcBmp;  
    if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC  
        return;  
      
    BITMAP m_bmp;                          //��ʱbmpͼƬ����  
    m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��  
      
    CBitmap *pbmpOld = NULL;        
    dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����  
      
    //ͼƬ��ʾ���ú���stretchBlt  
    pDC->StretchBlt(0,0,m_bmp.bmWidth,m_bmp.bmHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  
      
    /*******************************************************************************/  
    /* BOOL StretchBlt(int x,int y,int nWidth,int nHeight,CDC* pSrcDC,  
    /*                 int xSrc,int ySrc,int nSrcWidth,int nSrcHeight,DWORD dwRop ); 
    /* 1.����x��yλͼĿ��������Ͻ�x��y������ֵ       
    /* 2.nWidth��nHeigthλͼĿ����ε��߼���Ⱥ͸߶�       
    /* 3.pSrcDC��ʾԴ�豸CDCָ��                           
    /* 4.xSrc��ySrc��ʾλͼԴ���ε����Ͻǵ�x��y�߼�����ֵ  
    /* 5.dwRop��ʾ��ʾλͼ�Ĺ�դ������ʽ SRCCOPY����ֱ�ӽ�λͼ���Ƶ�Ŀ�껷����             
    /*******************************************************************************/  
      
    dcBmp.SelectObject(pbmpOld);           //�ָ���ʱDC��λͼ  
    DeleteObject(&m_bitmap);               //ɾ���ڴ��е�λͼ  
    dcBmp.DeleteDC();                      //ɾ��CreateCompatibleDC�õ���ͼƬDC  

	if(numPicture==2) {  
        //��ʾͼƬ����LoadImage  
        HBITMAP m_hBitmapChange;  
       if(level==0) //��ʾ2��ͼ BmpNameLinԭͼ  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpName,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else  
if(level==1) //�Ҷ�ͼƬ BmpNameLin��ʱͼƬ  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //����2  
if(level==2)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
} 
  else if(level==3) //ͼƬ����
 {
          m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,
                 LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);
  } 
else         //����4  
if(level==4)    
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //����8  
if(level==8)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //����16  
if(level==16)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //����32  
if(level==32)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}  
else         //����64  
if(level==64)  
{  
    m_hBitmapChange = (HBITMAP) LoadImage(NULL,BmpNameLin,IMAGE_BITMAP,0,0,  
        LR_LOADFROMFILE|LR_DEFAULTSIZE|LR_CREATEDIBSECTION);  
}    
        if( m_bitmap.m_hObject ) {  
            m_bitmap.Detach();            //m_bitmapΪ������λͼ����  
        }  
        m_bitmap.Attach(m_hBitmapChange);  
        //���岢����һ���ڴ��豸����  
        CDC dcBmp;  
        if( !dcBmp.CreateCompatibleDC(pDC) )   //���������Ե�DC  
            return;  
        BITMAP m_bmp;                          //��ʱbmpͼƬ����  
        m_bitmap.GetBitmap(&m_bmp);            //��ͼƬ����λͼ��  
        CBitmap *pbmpOld = NULL;  
        dcBmp.SelectObject(&m_bitmap);         //��λͼѡ����ʱ�ڴ��豸����  
  
        //���ͼƬ̫����ʾ��СΪ�̶�640*640 ������ʾԭͼ��С  
        if(m_nDrawWidth<650 && m_nDrawHeight<650)  
            pDC->StretchBlt(m_nWindowWidth-m_nDrawWidth,0,  
                m_nDrawWidth,m_nDrawHeight,&dcBmp,0,0,m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);  
        else  
            pDC->StretchBlt(m_nWindowWidth-640,0,640,640,&dcBmp,0,0,  
                m_bmp.bmWidth,m_bmp.bmHeight,SRCCOPY);   


        //�ָ���ʱDC��λͼ  
        dcBmp.SelectObject(pbmpOld);   
		

    }  

  
}  

bool CImageOperaView::ReadBmp()  
{  
    //ͼƬ�����洢���еĶ���  
    FILE *fp = fopen(BmpName,"rb");  
    if(fp==0)  
    {         
        AfxMessageBox("�޷����ļ�!",MB_OK,0);  
        return 0;   
    }  
    //��ȡ�ļ�ͷ ���BMP��ʽ���õķ���  
    fread(&bfh.bfType,sizeof(WORD),1,fp);  
    fread(&bfh.bfSize,sizeof(DWORD),1,fp);  
    fread(&bfh.bfReserved1,sizeof(WORD),1,fp);  
    fread(&bfh.bfReserved2,sizeof(WORD),1,fp);  
    fread(&bfh.bfOffBits,sizeof(DWORD),1,fp);  
    //ͼ���ļ������ֽ���  
    m_nSize = bfh.bfSize;  
    //�ж��Ƿ���bmp��ʽͼƬ  
    if(bfh.bfType!=0x4d42)   //'BM'  
    {  
        AfxMessageBox("����BMP��ʽͼƬ!",MB_OK,0);  
        return 0;  
    }  
    //��ȡ��Ϣͷ  
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
        AfxMessageBox("���ṹ��ռ���ֽ������ִ���");  
        return 0;  
    }  
    //λͼѹ�����ͣ������� 0����ѹ���� 1��BI_RLE8ѹ�����ͣ���2��BI_RLEѹ�����ͣ�֮һ  
    if(bih.biCompression == BI_RLE8 || bih.biCompression == BI_RLE4)  
    {  
        AfxMessageBox("λͼ��ѹ��!");  
        return 0;  
    }  
    //��ȡͼ��߿��ÿ��������ռλ��  
    m_nHeight = bih.biHeight;  
    m_nWidth = bih.biWidth;  
    m_nDrawHeight = bih.biHeight;  
    m_nDrawWidth = bih.biWidth;  
    m_nBitCount = bih.biBitCount;   //ÿ��������ռλ��  
    //����ͼ��ÿ��������ռ���ֽ�����������32�ı�����  
    m_nLineByte = (m_nWidth*m_nBitCount+31)/32*4;  
    //ͼƬ��С ����ϵͳ�Դ����ļ�ͷ BITMAPFILEHEADER bfh; BITMAPINFOHEADER bih;   
    //������ BITMAPFILEHEADER_ bfh; BITMAPINFOHEADER_ bih;Ҫ m_nImage = m_nLineByte * m_nHeight - 2;  
    m_nImage = m_nLineByte * m_nHeight;  
    //λͼʵ��ʹ�õ���ɫ���е���ɫ�� biClrUsed  
    m_nPalette = 0;                       //��ʼ��  
    if(bih.biClrUsed)  
        m_nPalette = bih.biClrUsed;  
    //����λͼ�ռ� ��СΪλͼ��С m_nImage  
    //mallocֻ������4�ֽڵĿռ� ��δ֪��  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fp);  
    fclose(fp);  
    return true;  
}  
bool CImageOperaView::SaveBmp(LPCSTR lpFileName) //lpFileNameΪλͼ�ļ���  
{  
    //����bmp��ʽͼƬ дͼƬ���� ֻ����24���ص�ͼƬ ��ͼƬ�޵�ɫ��  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(lpFileName,"wb");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //mallocֻ������4�ֽڵĿռ� ��δ֪��  
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
    filter="�����ļ�(*.bmp,*.jpg)|*.bmp;*.jpg| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg||";  
    //�ص�: 1-�ļ��� 0-�ļ�����  
    CFileDialog dlg(0,NULL,NULL,OFN_HIDEREADONLY,filter,NULL);     
    //����ȷ����ť  
    if( dlg.DoModal() == IDOK ) {  
        CString str;  
        CString strName;  
        CString filename;  
        str = dlg.GetPathName();           //��ȡ�ļ���·��  
        filename = dlg.GetFileTitle();     //��ȡ�ļ���  
        int nFilterIndex=dlg.m_ofn.nFilterIndex;  
        if( nFilterIndex == 2 )            //���û�ѡ���ļ�������Ϊ".BMP"ʱ  
        {  
            str = str + ".bmp";            //�Զ�����չ��.bmp  
            SaveBmp(str);                  //����bmpͼƬ ����һ��д��ͼƬ�Ĺ���   
            AfxMessageBox("ͼƬ����ɹ�",MB_OK,0);  
        }  
    }  
}

void CImageOperaView::OnShowTwo() 
{
//���û�е���ͼƬֱ�ӵ��˫�� ��ʾ����  
    if(numPicture==0)  
    {  
        AfxMessageBox("����ͼƬ�������ʾ2��ͼƬ!");  
        return;  
    }  
    AfxMessageBox("��ʾ����ͼƬ!",MB_OK,0);  
    numPicture = 2;    //ȫ�ֱ��� ��ʾ��ͼ  
    level =0;          //level=0˫��  
    Invalidate();      //����Invalidate ÿ�����һ��OnDraw��ͼ  	
}
/********************************************************************************************/                    
/* ����24λ��ͼƬ�Ҷ�ʱ,���������㷨:                                                        
/* 1.ƽ��ֵ�㷨 R=G=B=(R+G+B)/3                                                               
/* 2.�����㷨 R=G=B=(R+G+B+128)/4>>2                                                           
/* 3.��Ȩƽ��ֵ�㷨 ���ݹ����������,��ʵ��ȷ�ĻҶȹ�ʽӦ����R=G=B=R*0.299+G*0.587+B0.144    
/*   Ϊ������ٶ�������һ����ȫ���Խ��ܵĽ��ƣ���ʽ�������� R=G=B=(R*3+G*6+B)/10             
/* 4.��ȷ��Ȩƽ��ֵ�㷨 R=G=B=R*0.299+G*0.587+B0.144                                         
/********************************************************************************************/  
//**�Ҷ�ͼ����� R=G=B��Ϊ���ߵ�1/3 level=1ʱ�Ҷ�ͼ��**//  
void CImageOperaView::OnShowHd() 
{
	// TODO: Add your command handler code here
	if(numPicture==0)  
    {  
        AfxMessageBox("����ͼƬ����ܻҶ�ͼƬ!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�Ҷ�ͼ��!",MB_OK,0);  
    //����ʱ��ͼƬ  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //��ȡ�ļ�  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //�Ҷ�ͼ��  
    unsigned char color;  
    unsigned char red,green,blue;  
  
    /********************************************************************/  
    /* ע�⣺ԭ���������в�������for( i=0; i<m_nWidth*m_nHeight; i++ )   
    /* �������ͼƬ���һ��û��������һ�����ݣ������ͼ��������    
    /* ��ͼ���������Ϊm_nImage�������m_nImage/3�Ϳ��Ա�֤�������ض���  
    /********************************************************************/  
  
    for(int i=0; i < m_nImage/3; i++ )  
    {  
        fread(&red,sizeof(char),1,fpo);  
        fread(&green,sizeof(char),1,fpo);  
        fread(&blue,sizeof(char),1,fpo);  
  
    //    color=(red+green+blue)/3;   //ƽ��ֵ�㷨
		color=(red*3+green*6+blue)/10  ;//��Ȩƽ��ֵ�㷨
		
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

//****************���� �����ȼ�Ϊ2****************//
/*
*���������Ǵ�����ͼƬԭͼ(BmpName)����ʱͼƬ(BmpNameLin)��Ȼ���ȡԭͼ��Ϣͷ��ֵ����ʱ����ͼƬ��
�ڶ�ȡԭͼm_nImage�������ؾ�����������ÿ�����أ����ֵȼ�������������ļ�д����������ؾ����BmpNameLin��
�ڸ�ֵȫ�ֱ���level\numPicture�͵���Invalidate()�ػ�ͼ�񼴿ɡ�
*/
void CImageOperaView::OnLh2() 
{
	// TODO: Add your command handler code here
	 if(numPicture==0) {  
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=2!",MB_OK,0);  
    //����ʱ��ͼƬ  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //��ȡ�ļ�  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //mallocֻ������4�ֽڵĿռ�  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //�ȼ�2����  
    for(int i=0; i<m_nImage; i++ ) {  
        //24λ��Ϊ��ɫ��Ϊ���ͼ Red Green Blue Ϊ3�ֽ�   
        //�����ȼ�Ϊ2ȡ�м�ֵΪ 64 �� 192  
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
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=4!",MB_OK,0);  
    //����ʱ��ͼƬ  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //�ȼ�4����  
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
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=8!",MB_OK,0);  
    //����ʱ��ͼƬ ��ȡ�ļ�  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    //mallocֻ������4�ֽڵĿռ� ��δ֪��  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //�ȼ�8����  
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
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=16!",MB_OK,0);  
    int i,j;  
    //����ʱ��ͼƬ  
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
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=32!",MB_OK,0);  
    int i,j;  
    //����ʱ��ͼƬ  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //��ȡ�ļ�  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //�ȼ�32��  
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
        AfxMessageBox("����ͼƬ���������!",MB_OK,0);  
        return;  
    }  
    AfxMessageBox("�����ȼ�Level=64!",MB_OK,0);  
    int i,j;  
    //����ʱ��ͼƬ  
    FILE *fpo = fopen(BmpName,"rb");  
    FILE *fpw = fopen(BmpNameLin,"wb+");  
    //��ȡ�ļ�  
    fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
    fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
    fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
    fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
    m_pImage=(BYTE*)malloc(m_nImage);  
    fread(m_pImage,m_nImage,1,fpo);  
    //�ȼ�64����  
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
        AfxMessageBox("����ͼƬ����ܲ���!",MB_OK,0);  
        return;  
    }  
    CImageCYDlg dlg;     //��������Ի���  
    //��ʾ�Ի���  
    if( dlg.DoModal()==IDOK ) {  
        //�����������ΪͼƬ����������  
        if( dlg.m_xPlace==0 || dlg.m_yPlace==0 ) {  
            AfxMessageBox("����ͼƬ���ز���Ϊ0!",MB_OK,0);  
            return;  
        }  
        if( dlg.m_xPlace>m_nWidth || dlg.m_yPlace>m_nHeight ) {  
            AfxMessageBox("ͼƬ���ز���Ϊ����ԭͼ����!",MB_OK,0);  
            return;  
        }  
        AfxMessageBox("ͼƬ����!",MB_OK,0);  
        //����ʱ��ͼƬ ��ȡ�ļ�  
        FILE *fpo = fopen(BmpName,"rb");  
        FILE *fpw = fopen(BmpNameLin,"wb+");  
        fread(&bfh,sizeof(BITMAPFILEHEADER),1,fpo);  
        fread(&bih,sizeof(BITMAPINFOHEADER),1,fpo);  
        fwrite(&bfh,sizeof(BITMAPFILEHEADER),1,fpw);  
        fwrite(&bih,sizeof(BITMAPINFOHEADER),1,fpw);  
        fread(m_pImage,m_nImage,1,fpo);  
      
        /*ͼƬ����*/  
        int numWidth,numHeight;     //ͼƬ������ȡ��ͬ�����ص�  
        int numSYWidth,numSYHeight; //ʣ���ڼ�����   
  
        /*********************************************************/  
        /* ��ʾnumWidth*numHeightΪһ������ ��������ɫ��ͬ        
        /* �� 512/512=1 512/512=1 1*1Ϊһ������                   
        /* dlg.m_xPlace*dlg.m_yPlace ��ʾ�µģ�x,y������          
        /* numSYWidth��ʾʣ��ռ� ������ͳһΪһ����ɫ            
        /*********************************************************/  
  
        numWidth=m_nWidth/dlg.m_xPlace;          
        numHeight=m_nHeight/dlg.m_yPlace;        
        numSYWidth=m_nWidth%dlg.m_xPlace;       
        numSYHeight=m_nHeight%dlg.m_yPlace;     
        int Y,X;  
        int i,j,m,n;  
        unsigned char red,green,blue;  //�洢������ɫ  
      
        /* ��((m_xPlace * m_yPlace)+ ʣ������ )��С���� */  
        for( i=0; i<dlg.m_yPlace; i++ )       //�߶�  
        {  
            Y=numHeight*i;                    //��ȡY����  
            for( j=0; j<dlg.m_yPlace; j++ )   //���  
            {  
                X=numWidth*j;                 //��ȡX����  
                /*��ȡ�����ɫ*/  
                red=m_pImage[(X+Y*m_nWidth)*3];  
                green=m_pImage[(X+Y*m_nWidth)*3+1];  
                blue=m_pImage[(X+Y*m_nWidth)*3+2];  
                /*���ͼ��ѭ�� С�����еĳ���ѭ��*/  
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
