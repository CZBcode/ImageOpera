// CntrItem.h : interface of the CImageOperaCntrItem class
//

#if !defined(AFX_CNTRITEM_H__C35861BB_A965_41F3_92D3_58634A29FF4F__INCLUDED_)
#define AFX_CNTRITEM_H__C35861BB_A965_41F3_92D3_58634A29FF4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CImageOperaDoc;
class CImageOperaView;

class CImageOperaCntrItem : public COleClientItem
{
	DECLARE_SERIAL(CImageOperaCntrItem)

// Constructors
public:
	CImageOperaCntrItem(CImageOperaDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE.
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer.

// Attributes
public:
	CImageOperaDoc* GetDocument()
		{ return (CImageOperaDoc*)COleClientItem::GetDocument(); }
	CImageOperaView* GetActiveView()
		{ return (CImageOperaView*)COleClientItem::GetActiveView(); }

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageOperaCntrItem)
	public:
	virtual void OnChange(OLE_NOTIFICATION wNotification, DWORD dwParam);
	virtual void OnActivate();
	protected:
	virtual void OnGetItemPosition(CRect& rPosition);
	virtual void OnDeactivateUI(BOOL bUndoable);
	virtual BOOL OnChangeItemPosition(const CRect& rectPos);
	//}}AFX_VIRTUAL

// Implementation
public:
	~CImageOperaCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void Serialize(CArchive& ar);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CNTRITEM_H__C35861BB_A965_41F3_92D3_58634A29FF4F__INCLUDED_)
