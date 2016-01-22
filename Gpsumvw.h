
class CGPSumView: public CGeneViewBase 
{
private:

public:
	CGPSumView();
	DECLARE_DYNCREATE(CGPSumView)

	UINT m_IntXPos;
	DWORD m_IntYPos;

	void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	void AssertValid() const;
	void Dump(CDumpContext& dc) const;
#endif

	void OnDraw( DrawStruct *m_DrawStc );
	void CalcDrawSize(CDC* pDC, UINT* XSize, DWORD *YSize, int ) {return; }

//
    void OnLButtonDown(UINT nFlags, UINT XPoint, DWORD YPoint, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnMouseMove(UINT nFlags, UINT XPoint, DWORD YPoint, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnLButtonUp(UINT nFlags, UINT XPoint, DWORD YPoint, CView * pWnd, VIEWRETSTRUCT *pViewRet);
	void OnLButtonDblClk(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd);
	
	int GetPartialPageSize(DWORD tPageTop, DWORD tPageBottom, DWORD *tPageAmount);
	void InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2);
//
	void AddTail( CGeneViewBase * pGP );
	void AddHead( CGeneViewBase * pGP );
	
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc );

	void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint);

};

