
class CGVEdit: public CGeneViewBase 
{
private:

    // int m_SaveSetShade;
	COLORREF m_SaveShadeText, m_SaveShadeBack;
//
	void CheckMove( UINT nFlags, UINT XPosition, DWORD YPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet);
	void CheckShade( UINT nFlags, UINT XPosition, DWORD YPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet);
	int GetGVEditRows();
//
	DWORD m_YInc;
	DWORD m_GVRYPosition;
	UINT m_GVEditRowCount;
	POSITION m_GVEditRowPos;
	BOOL AddRemShade;
//

public:
    CGeneSegBase *m_pBase;
    DWORD m_StartPos;
	DWORD m_StartSelect;

    CGeneString* m_MoveString;
    DWORD m_MovePoint;
    // CPoint m_DataStartPoint;                // Set by OnDraw Function
    // CRect m_ClipRect;
	UINT m_ClipXPosition;
	DWORD m_ClipYPosition;
	UINT m_ClipXSize;
	DWORD m_ClipYSize;

    CGVEdit();
    DECLARE_DYNCREATE(CGVEdit)
    ~CGVEdit();

    void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    void AssertValid() const;
    void Dump(CDumpContext& dc) const;
#endif
//
    void OnDraw( DrawStruct *DrawStc );
    void CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int);
    
    void OnLButtonDown(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnMouseMove(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnLButtonUp(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd, VIEWRETSTRUCT *pViewRet);
    void OnLButtonDblClk(UINT nFlags, UINT XPosition, DWORD YPosition, CView * pWnd);
//
    int OnComment(char nChar, UINT XPosition, DWORD YPosition, CView * pWnd);
	int ReScoreFunction( UINT XPosition, DWORD YPosition, CView *pWnd );
	int GetPartialPageSize(DWORD tPageTop, DWORD tPageBottom, DWORD *tPageAmount);

//
    void AddHeader( CString* nString );
    void AddData( CGeneString* nString );

    void SetDataParams( CGeneSegBase *npBase, unsigned long StartPos ) {
            m_pBase = npBase;
            m_StartPos = StartPos;
    }
	int CheckMoveRanges( 
		CView *pWnd, 
		CGeneSegment * pCGSeg, 
		UINT Row, 
		int InvalScore, 
		DWORD ScoreStart, 
		DWORD ScoreEnd 
	);
	void InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2);

	void CountCopyText(DWORD *dwCount );
	void CopyText(char *tString, DWORD *dwCount, UINT RowNumber );
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenethonDoc* pDoc );
	void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint );
	DWORD ColPosFromCaret(UINT XPosition, DWORD YPosition );
	BOOL CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos );

//
};

