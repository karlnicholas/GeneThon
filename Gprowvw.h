/*
    GeneDoc: Multiple Sequence Alignment Editing Utility
    Copyright (C) 2000, Karl Nicholas

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


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
	void WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenethonDoc* pDoc );

	void SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint);
	DWORD ColPosFromCaret(UINT XPosition, DWORD YPosition );
	BOOL CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos );

};

