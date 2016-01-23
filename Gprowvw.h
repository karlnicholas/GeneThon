
class CGPRowView: public CGeneViewBase 
{
private:

public:
	CGPRowView();
	DECLARE_DYNCREATE(CGPRowView)

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
	void OnLButtonDown(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet);
	void OnMouseMove(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet);
	void OnLButtonUp(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet);
	void OnLButtonDblClk(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd);
	
	int OnComment(char nChar, UINT XPoint, DWORD YPoint, CView *pWnd);
	int ReScoreFunction( UINT XPoint, DWORD YPoint, CView *pWnd );
	int GetPartialPageSize(DWORD tPageTop, DWORD tPageBottom, DWORD *tPageAmount);
//
	void AddTail( CGeneViewBase * pGP );
	void AddHead( CGeneViewBase * pGP );
	
	void CheckMoveRanges( CView *pWnd, CGeneSegment *pCGSeg, UINT Row, 
		int InvScore, DWORD ScoreStart, DWORD ScoreEnd );
	void InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2);

	void CountCopyText(DWORD *dwCount );

	void CopyText(char *tString, DWORD *dwCount, UINT RowNumber );
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenethonDoc* pDoc );

	void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint);
	DWORD ColPosFromCaret(UINT XPosition, DWORD YPosition );
	BOOL CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos );

};

