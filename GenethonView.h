// genedvw.h : interface of the CGenethonView class
//
/////////////////////////////////////////////////////////////////////////////

class CGDocViewCaret: public CBaseCaret
{
public:
	CGDocViewCaret() {}
	void Select( UINT XPosition, DWORD YPosition, CView *pView );
	void LeftDown( UINT XPosition, DWORD YPosition, CView *pView );
	void LeftUp( UINT XPosition, DWORD YPosition, CView *pView );
	void InsKey( UINT XPosition, DWORD YPosition, CView* pView );
	void DelKey( UINT XPosition, DWORD YPosition, CView* pView );

	void RightDown( UINT XPosition, DWORD YPosition, CView *pView );
//	void RightUp( UINT XPosition, DWORD YPosition, CView *pView );
};

class CGenethonView : public CView
{
protected: // create from serialization only
	CGenethonView();
	DECLARE_DYNCREATE(CGenethonView)
	
	friend CGDocViewCaret;
	CGDocViewCaret m_MyCaret;

	UINT m_Descent;		// For Pict Files.

	int m_iReadShift;
	int m_TransColumns;
	int m_TransFixed;
	int m_TransFltStart;

	void ResetGPAdd( CGeneSegBase *pGSBase );
	void BuildRowViews( CGeneSegBase *pGSBase, DWORD StartPos );

	void AddHeadTail( CGVEdit* tGEt, CGVEdit* tGEh, CGPRowView* tRowView );
	void AddHead( CGVEdit* tGEh, CGPRowView* tRowView );
        
//	int m_MaxX;
//	int m_CharWidth;
//	int m_CharHeight;
//	CSize m_Size;


// scrolling vars.

	DWORD m_LineHeight;
	UINT m_CharWidth;

	DWORD m_PageScrollHeight;
	UINT m_PageScrollWidth;

	DWORD m_TotalHeight;
	UINT m_TotalWidth;
	
	UINT m_DisplayXPosition;
	DWORD m_DisplayYPosition;
	
	UINT m_SaveDisplayXPosition;
	DWORD m_SaveDisplayYPosition;

	DWORD m_DisplayHeight;
	UINT m_DisplayWidth;
	
	UINT m_ScrollBarRange;

	void SetScrollVariables();
	
	void SetScrollBars();

	void DoDraw(CDC* pDC, int InvFlag1, int InvFlag2 );
// scrolling vars.

	CDC *m_pDC;

	UINT m_EnumCount;
	UINT m_RowVEnum;
	UINT m_LeaderSaveEnum;
	int m_ExpandedResize;
	int m_FileOpenFlag;

	// Global vars

	POSITION m_EndPos;
	UINT m_StartSelect;
	UINT m_EndSelect;

	UINT m_LeftView;
	UINT m_TopView;

	DWORD m_PageHeight;
	UINT m_PageWidth;
	DWORD m_TopPage;
	DWORD m_BottomPage;

	int m_PartialPrintFlag;
	int m_PrintOnly;

	CRect m_rectMargins;
	void CalculateMargins(CDC* pDC);
	int m_PrintYOffSet;

	enum { NONE, KEYBRD, MOUSE };
	int m_SelectDevice;
	
	int m_CopyFlag;

	int m_InitialUpdateDone;
	
	int m_GeneShade;
	int m_GeneSelectCol;
	int m_GeneSelect;

	COLORREF m_ShadeTextColor;
	COLORREF m_ShadeBackColor;
	
	enum { 
		DEF_NULL,
	//
		DEF_SHADE,
	//
		DEF_GENESELECT,
		DEF_GENESELECTCOL,
	};

	void ClearMenu();
	unsigned int GetMenuFunction();
	void LeftDownFunc( UINT nFlags, CPoint point, int DDevice );
	void MoveFunc(UINT nFlags, CPoint point, int DDevice);
	void LeftUpFunc(UINT nFlags, CPoint point, int DDevice);
	void RightDownFunc( UINT nFlags, CPoint point, int DDevice );

	void AdjustEndToPoint( CGPRowView *tGP, UINT PointXPosition, DWORD PointYPosition, CView *pWnd );
	void DeSelectAll();
	void ClipFunction( int InvFlag, int ResFlag, int BitFlag );
	
	DWORD m_ColSelStart;
	DWORD m_ColSelEnd;
	int   m_ColSelBegin;
	
	void RebuildShowCaret();

	int m_NamesLength;
	

// Attributes
public:
	CGenethonDoc* GetDocument();

	CObList m_RowViewList;
	void CleanRowViewList();

	int m_GVETailLength;
	int m_GVELeadLength;
	int m_IndLength;

	void ResetGPSize( CDC* pDC, UINT MaxX );

	void ExpandedSegments( VIEWRETSTRUCT *pViewRet );
	void InvalNewEndPoint( DWORD Range1, DWORD Range2);

	void InvalidateRectLP(UINT tXPosition, DWORD tYPosition, UINT tXSize, DWORD tYSize );
	void InvalidateGVBLP( CGeneViewBase *pGVB );
	BOOL IsVisible( UINT XPosition, DWORD YPosition, UINT XSize, DWORD YSize );

	void ScrollToPosition ( UINT ScrollXPosition, DWORD ScrollYPosition );
	void GetScrollPosition( UINT *ScrollXPosition, DWORD *ScrollYPosition);

	void CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg );
	DWORD ColPosFromCaret(UINT XPosition, DWORD YPosition );

// Operations
public:

// Implementation
public:
	virtual ~CGenethonView();
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate ( CView* pSender, LPARAM lHint, CObject *pHint );
	// Printing support
	virtual void OnPrepareDC( CDC* pDC, CPrintInfo* pInfo = NULL);
	virtual void OnPrint( CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView );
	virtual void OnEndPrintPreview( CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView );
// My Message Handlers

// Generated message map functions
protected:
	//{{AFX_MSG(CGenethonView)
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSelect();
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	afx_msg void OnSelectcol();
	afx_msg void OnUpdateSelectcol(CCmdUI* pCmdUI);
	afx_msg void OnGenecreatewin();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy0();
	afx_msg void OnUpdateEditCopy0(CCmdUI* pCmdUI);
	afx_msg void OnEditCopy8();
	afx_msg void OnUpdateEditCopy8(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinv0();
	afx_msg void OnUpdateEditCopyinv0(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinv8();
	afx_msg void OnUpdateEditCopyinv8(CCmdUI* pCmdUI);
	afx_msg void OnEditCopyinvbit();
	afx_msg void OnUpdateEditCopyinvbit(CCmdUI* pCmdUI);
	afx_msg void OnEditCopybit();
	afx_msg void OnUpdateEditCopybit(CCmdUI* pCmdUI);
	afx_msg void OnCopytext();
	afx_msg void OnGenecopypict();
	afx_msg void OnUpdateGenecopypict(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnCopymetaclip();
	afx_msg void OnCopymetafile();
	afx_msg void OnUpdateCopymetaclip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCopymetafile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenecreatewin(CCmdUI* pCmdUI);
	afx_msg void OnGenecopyrtf();
	afx_msg void OnUpdateGenecopyrtf(CCmdUI* pCmdUI);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // debug version in genedvw.cpp
inline CGenethonDoc* CGenethonView::GetDocument()
   { return (CGenethonDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
