// GVEdit.cpp : implementation of the CGPEdit class
//

#include "stdafx.h"

#define EDIT_CLIP_LEFT 2
#define EDIT_CLIP_RIGHT 0

#define EDIT_CHECK_LEFT 2
#define EDIT_CHECK_RIGHT 3

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVEdit

IMPLEMENT_DYNCREATE(CGVEdit, CObject)


CGVEdit::CGVEdit(): CGeneViewBase()
{
	// TODO: add construction code here
	m_MoveString = NULL;
}


CGVEdit::~CGVEdit()
{

	while ( !ViewDataList.IsEmpty() ) {
		delete (CGeneString *) ViewDataList.RemoveHead();
	}

	while ( !ViewHeaderList.IsEmpty() ) {
		delete (CString *) ViewHeaderList.RemoveHead();
	}

}


/////////////////////////////////////////////////////////////////////////////
// CGVEdit serialization

void CGVEdit::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGVEdit diagnostics

#ifdef _DEBUG
void CGVEdit::AssertValid() const
{
	CObject::AssertValid();
}

void CGVEdit::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CGVEdit::AddHeader( CString* nString )
{
	ViewHeaderList.AddTail( nString );
}

void 
CGVEdit::AddData( CGeneString* nString )
{
	ViewDataList.AddTail(nString);
}

void 
CGVEdit::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int)
{
	// TODO: calculate the total size of this view

	m_YSize = ViewDataList.GetCount() * m_LineHeight;
	m_XSize = ((CGeneString *)ViewDataList.GetHead())->GetLength() * m_CharWidth;

	*YSize = m_YSize;
	*XSize = m_XSize;

	return;
}

int 
CGVEdit::GetGVEditRows()
{
	CGeneString * tGStr;
	switch ( m_GVEditRowCount++ ) {
	case 0:
		return 0;
	case 1:
		m_GVEditRowPos = ViewDataList.GetHeadPosition();
		if ( m_GVEditRowPos != NULL ) {
			tGStr = (CGeneString *)ViewDataList.GetNext(m_GVEditRowPos);
		} else {
			return 1;
		}
		m_GVRYPosition += m_YInc;
		return 0;
	default:
		if ( m_GVEditRowPos != NULL ) {
			tGStr = (CGeneString *)ViewDataList.GetNext(m_GVEditRowPos);
		} else {
			return 1;
		}
		m_GVRYPosition += m_YInc;
		return 0;
	}
	return 0;
}	


int 
CGVEdit::GetPartialPageSize(
	DWORD tPageTop, 
	DWORD tPageBottom, 
	DWORD *tPageAmount)
{

	// Init GetGVEditRows	
	int tRet;
	// int
	m_YInc = m_LineHeight;

	m_GVRYPosition = m_YPosition;
	// int
	m_GVEditRowCount = 0;

	// First we move past the top
	while ( 1 ) {
		if ( tRet = GetGVEditRows() ) {
			break;
		}
		if ( m_GVRYPosition >= tPageTop ) {
			break;
		}
	}

//	*tPageAmount += m_YInc;
	
	// Dont do this if already the end, but should never really happen?
	while ( tRet == 0 ) {
		if ( tRet = GetGVEditRows() ) {
			break;
		}
		if ( m_GVRYPosition > tPageBottom ) {
			break;
		}
		*tPageAmount += m_YInc;
	}

	return tRet;
}

void 
CGVEdit::OnDraw( DrawStruct *DrawStc )
{

	char tOut[2];
	CGenethonDoc *pDoc = ((CGenethonView *)DrawStc->pView)->GetDocument();
	
	CBrush	tBrush;

	POSITION tPos = ViewDataList.GetHeadPosition();
	DWORD CurrentDisplayLoc = m_YPosition;

	tOut[1] = 0;

	DWORD sScore;
	UINT RowNum = 0;
	UINT PrintTop = 1;
	// Is consensus top?


	// int RowCount = ViewDataList.GetCount();
	if ( DrawStc->pDC->IsPrinting() ) {
		DrawStc->pDC->SetBkMode ( TRANSPARENT );
		if ( pDoc->m_UserVars.m_ConsensusLine != 0 ) {
			// Then use score line
			PrintTop = 2;
		}
	}

	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		if ( (CurrentDisplayLoc + m_LineHeight) > DrawStc->ReDrawTop 
//			&& CurrentDisplayLoc <= DrawStc->ReDrawBottom // Changed because of printing lipid10
			&& CurrentDisplayLoc < DrawStc->ReDrawBottom 
		) {

			int i = 0;	
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			// Outter String Transverse Loop
			for ( UINT tCount = 0; tCount < tMax; tCount++ ) {

				UINT tXLoc1 = tCount*m_CharWidth + m_CharWidth + m_XPosition;
				UINT tXLoc2 = tCount*m_CharWidth + m_XPosition;

				if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {
		
					// i is set to chading level
					COLORREF TextColor, BkColor;
					TextColor = tStr[tCount].TextColor;
					BkColor = tStr[tCount].BackColor;
					CRect tcRect( 
						tXLoc2 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
						tXLoc1 - DrawStc->DisplayXPosition, 
						(int)(CurrentDisplayLoc + m_LineHeight - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset
					);

					if ( DrawStc->pDC->IsPrinting() ) {

						switch ( BkColor ) {
						case  1:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_BDIAGONAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  2:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_CROSS, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  3:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_DIAGCROSS, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  4:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_FDIAGONAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case  5:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_HORIZONTAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						case 6:
							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							tBrush.CreateHatchBrush( HS_VERTICAL, RGB(0,0,0) );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						default:
							tBrush.CreateSolidBrush( BkColor );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();
							break;
						}

					}

					DrawStc->pDC->SetBkColor( BkColor );

					DrawStc->pDC->SetTextColor( TextColor );
					tOut[0] = (tStr + tCount)->CharDisplay;

					if ( DrawStc->pDC->IsPrinting() ) {
						if ( !pDoc->m_UserVars.m_PrintShading || RowNum < PrintTop ) {
							DrawStc->pDC->TextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								tOut, 1 
							);
						}
					} else {

						// HS_BDIAGONAL   Downward hatch (left to right) at 45 degrees
						// HS_CROSS   Horizontal and vertical crosshatch
						// HS_DIAGCROSS   Crosshatch at 45 degrees
						// HS_FDIAGONAL   Upward hatch (left to right) at 45 degrees
						// HS_HORIZONTAL   Horizontal hatch
						// HS_VERTICAL   Vertical hatch

						switch ( BkColor ) {
						case  1:
							tBrush.CreateHatchBrush( HS_BDIAGONAL, RGB(0,0,0) );
							break;
						case  2:
							tBrush.CreateHatchBrush( HS_CROSS, RGB(0,0,0) );
							break;
						case  3:
							tBrush.CreateHatchBrush( HS_DIAGCROSS, RGB(0,0,0) );
							break;
						case  4:
							tBrush.CreateHatchBrush( HS_FDIAGONAL, RGB(0,0,0) );
							break;
						case  5:
							tBrush.CreateHatchBrush( HS_HORIZONTAL, RGB(0,0,0) );
							break;
						case 6:
							tBrush.CreateHatchBrush( HS_VERTICAL, RGB(0,0,0) );
							break;
						}

						if ( BkColor >= 1 && BkColor <= 6 ) {

							DrawStc->pDC->SetBkColor( pDoc->m_UserVars.m_BackColor );
							DrawStc->pDC->SetBkMode ( TRANSPARENT );
							DrawStc->pDC->FillRect ( tcRect, &tBrush );
							tBrush.DeleteObject();

							DrawStc->pDC->ExtTextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								NULL, 
								tcRect, 
								tOut, 1 , (int *)(&m_CharWidth) 
							);
						} else {
							DrawStc->pDC->ExtTextOut( 
								tXLoc2 - DrawStc->DisplayXPosition, 
								(int)(CurrentDisplayLoc - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
								ETO_OPAQUE, 
								tcRect, 
								tOut, 1 , (int *)(&m_CharWidth) 

							);
						}
					}
				}
			}
		}

		CurrentDisplayLoc += m_LineHeight;
		RowNum++;

	}
	
	if (
		DrawStc->MenuFunc == CGenethonView::DEF_GENESELECTCOL
		&& DrawStc->ColSelBegin
		&& (!DrawStc->pDC->IsPrinting())
	) {
		DWORD StartRange;
		DWORD EndRange;
		if (DrawStc->ColSelStart < DrawStc->ColSelEnd) {
			StartRange = DrawStc->ColSelStart;
			EndRange = DrawStc->ColSelEnd;
		}
		else {
			StartRange = DrawStc->ColSelEnd;
			EndRange = DrawStc->ColSelStart;
		}

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();

		// Test if range hits this string.    
		if (!
			(
				(
					(StartRange < tGStr->GetStartPos())
					&& (EndRange < tGStr->GetStartPos())
					) || (
						(StartRange >(tGStr->GetStartPos() + tGStr->GetLength()))
						&& (EndRange >(tGStr->GetStartPos() + tGStr->GetLength()))
						)
				)
			) {

			CRect tcRect(
				m_XPosition - DrawStc->DisplayXPosition,
				(int)(m_YPosition - DrawStc->DisplayYPosition),
				m_XPosition + m_XSize - DrawStc->DisplayXPosition,
				(int)(m_YPosition + m_YSize - DrawStc->DisplayYPosition)
				);

			if (EndRange < (tGStr->GetStartPos() + tGStr->GetLength())) {
				tcRect.BottomRight().x =
					tcRect.TopLeft().x + (int)((EndRange + 1 - tGStr->GetStartPos()) * m_CharWidth);
			}

			if (StartRange > tGStr->GetStartPos()) {
				tcRect.TopLeft().x += (int)((StartRange - tGStr->GetStartPos()) * m_CharWidth);
			}

			DrawStc->pDC->InvertRect(tcRect);
		}
	}
}

void 
CGVEdit::InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2)
{
	DWORD StartRange;
	DWORD EndRange;

	if ( Range1 < Range2 ) {
		StartRange = Range1;
		EndRange = Range2;
	} else {
		StartRange = Range2;
		EndRange = Range1;
	}
	
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	
	// Test if range hits this string.    
    if ( ! 
    	(
	    	(
	    		(StartRange < tGStr->GetStartPos() ) 
	    		&& (EndRange < tGStr->GetStartPos() )
	    	) || (
	    		(StartRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
	    		&& (EndRange > (tGStr->GetStartPos() + tGStr->GetLength() ))
			)
		)
    ) {


		// CRect tRect = GetViewRect();
		UINT tXPosition, tXSize;
		DWORD tYPosition, tYSize;
		GetPosition( &tXPosition, &tYPosition );
		GetSize( &tXSize, &tYSize );

		if ( ((CGenethonView*)pWnd)->IsVisible( tXPosition, tYPosition, tXSize, tYSize ) ) {

			if ( EndRange < (tGStr->GetStartPos() + tGStr->GetLength() ) ) {
				// tXSize = (UINT)((EndRange + 1 - tGStr->GetStartPos()) * m_CharWidth);
				tXSize = (UINT)((EndRange + 1 - StartRange) * m_CharWidth);
			}

			if ( StartRange > tGStr->GetStartPos() ) {
				tXPosition += (UINT)((StartRange - tGStr->GetStartPos()) * m_CharWidth);
			}
			((CGenethonView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

		}
	}
}

//
void 
CGVEdit::OnLButtonDown(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{
	int move;
//	int OnlyExp = 0;

	DeSelect();		// Clear return flag
	pViewRet->Clip = 0;
	
	if ( !m_pBase->IsKindOf(RUNTIME_CLASS(CGSFiller)) )
		return;

	if ( pViewRet->MenuFunc == 0 ) {
		return;
	}
	
	if (pViewRet->MenuFunc == CGenethonView::DEF_GENESELECTCOL) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();

		if (pViewRet->ColSelBegin == 0) {

			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;
			pViewRet->ColSelBegin = 1;

			UINT tXPosition, tXSize;
			DWORD tYPosition, tYSize;
			GetPosition(&tXPosition, &tYPosition);
			GetSize(&tXSize, &tYSize);

			tXPosition += (tCount * m_CharWidth);
			tXSize = m_CharWidth;

			((CGenethonView*)pWnd)->InvalidateRectLP(tXPosition, tYPosition, tXSize, tYSize);

			// All Done here
			return;

		}

		DWORD StartRange;
		DWORD EndRange;

		if (pViewRet->ColSelStart < pViewRet->ColSelEnd) {
			StartRange = pViewRet->ColSelStart;
			EndRange = pViewRet->ColSelEnd;
		}
		else {
			StartRange = pViewRet->ColSelEnd;
			EndRange = pViewRet->ColSelStart;
		}

		if ((gloc >= StartRange) && (gloc <= EndRange)) {

			((CGenethonView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelStart, pViewRet->ColSelEnd);
			pViewRet->ColSelStart = pViewRet->ColSelEnd = gloc;

		}
		else {
			((CGenethonView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
		return;
	}

	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;

	POSITION tPos = ViewDataList.GetHeadPosition();
	
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		
		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();

		if ( pViewRet->DDevice == CGenethonView::KEYBRD ) {
			tXSize += 1;
		}

		// Dont shade comment seg's
		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
			&& 
			( tGStr->GetGeneSegment()->GetStyle() == LINESEQUENCE )
		) {


			if ( pViewRet->MenuFunc == CGenethonView::DEF_SHADE ) { 
				// here we do Shading.
				// Fill out selection stuff
				
				
				CGenethonView *pView = ((CGenethonView*)pWnd);
				COLORREF ShadeTextColor, ShadeBackColor;
				ShadeTextColor = pView->m_ShadeTextColor;
				ShadeBackColor = pView->m_ShadeBackColor;

				CGenethonDoc *pDoc = pView->GetDocument();
				pViewRet->Expanded = 0;

				UINT tCount = (PointXPosition - sXLoc) / m_CharWidth;
				COLORREF TextColor, BackColor;
				tGStr->GetShade( tCount, &TextColor, &BackColor );
				if ( TextColor == ShadeTextColor && BackColor == ShadeBackColor ) { 
					pDoc->GetColors(&m_SaveShadeText, &m_SaveShadeBack );
					AddRemShade = 0;
				} else {
					m_SaveShadeText = ShadeTextColor;
					m_SaveShadeBack = ShadeBackColor;
					AddRemShade = 1;
				}
				tGStr->SetShade( tCount, m_SaveShadeText, m_SaveShadeBack );
				tGStr->GetGeneSegment()->SetShade ( 
					(DWORD)(tGStr->GetStartPos() + tCount), 
					m_SaveShadeText, m_SaveShadeBack, AddRemShade 
				);

				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tCount * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenethonView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );
				
				break;

			} 
				
		}

//		sLoc.y += m_LineHeight;
		sYLoc += m_LineHeight;
	}		
}

void 
CGVEdit::OnMouseMove(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{
	if (pViewRet->MenuFunc == CGenethonView::DEF_GENESELECTCOL) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();

		if (gloc != pViewRet->ColSelEnd) {
			((CGenethonView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	} else if ( pViewRet->MenuFunc == CGenethonView::DEF_SHADE ) {
		CheckShade( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	}
}

void
CGVEdit::CheckShade( UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet)
{
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	
	POSITION tPos = ViewDataList.GetHeadPosition();
		
	while ( tPos != NULL ) {
	
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
	
		DWORD tYSize = m_LineHeight;
		int tXSize = m_CharWidth * tGStr->GetLength();

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {
			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {
				break;
			}

			UINT tLoc = (PointXPosition - m_XPosition) / m_CharWidth;

			COLORREF TextColor, BackColor;
			tGStr->GetShade(tLoc, &TextColor, &BackColor);

			if ( TextColor != m_SaveShadeText || BackColor != m_SaveShadeBack ) {
				tGStr->SetShade( tLoc, m_SaveShadeText, m_SaveShadeBack );
				tGStr->GetGeneSegment()->SetShade ( 
					(DWORD)(tGStr->GetStartPos() + tLoc), 
					m_SaveShadeText, m_SaveShadeBack, AddRemShade 
				);
					
				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tLoc * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenethonView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

			}
				
			break;
		}
		sYLoc += m_LineHeight;
	}
}

void 
CGVEdit::OnLButtonUp(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd, VIEWRETSTRUCT * pViewRet) 
{
	if (pViewRet->MenuFunc == CGenethonView::DEF_GENESELECTCOL) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
		UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
		DWORD gloc = tCount + tGStr->GetStartPos();

		if (gloc != pViewRet->ColSelEnd) {
			((CGenethonView*)pWnd)->InvalNewEndPoint(pViewRet->ColSelEnd, gloc);
			pViewRet->ColSelEnd = gloc;
		}

		// All done here
	} else if ( pViewRet->MenuFunc == CGenethonView::DEF_SHADE ) {
		CheckShade( nFlags, PointXPosition, PointYPosition, pWnd, pViewRet );
	}
	m_MoveString = NULL;
}


void 
CGVEdit::OnLButtonDblClk(UINT nFlags, UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{
}

int 
CGVEdit::OnComment(char nChar, UINT PointXPosition, DWORD PointYPosition, CView* pWnd) 
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;
	

	ASSERT ( pWnd->IsKindOf(RUNTIME_CLASS(CGenethonView)));
	CGenethonView* pView = (CGenethonView* )pWnd;
	
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();
		// CRect tRect ( sLoc, tSize );

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {

			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {

				// Fill out selection stuff
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;

				tGStr->SetComment( tCount, nChar );
				tGStr->GetGeneSegment()->SetComment ( 
					(DWORD)(tGStr->GetStartPos() + tCount), 
					nChar
				);

				UINT tXPosition, tXSize;
				DWORD tYPosition, tYSize;
				GetPosition( &tXPosition, &tYPosition );
				GetSize( &tXSize, &tYSize );

				tXPosition += (tCount * m_CharWidth);
				tXSize = m_CharWidth;
		
				((CGenethonView*)pWnd)->InvalidateRectLP( tXPosition, tYPosition, tXSize, tYSize );

				return 1;

			}

			return 0;
		}
		sYLoc += m_LineHeight;
	}
	
	return 0;
}


void 
CGVEdit::CopyText(char * tString, DWORD *dwCount, UINT RowNumber )
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				tString[*dwCount] = tStr->CharDisplay;
				(*dwCount)++;
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}
 

void 
CGVEdit::CountCopyText( DWORD *dwCount )
{
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	*dwCount = tGStr->GetLength();
}


void 
CGVEdit::WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc *pDoc )
{
	UINT sRowNum = RowNumber;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				COLORREF TextC, BkC;
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetColors( &TextC, &BkC );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					TextC = tStr->TextColor;
					BkC = tStr->BackColor;
				}

				pPictFile->CharOut( tStr->CharDisplay, TextC, BkC );

				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}
  
void 
CGVEdit::WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenethonDoc *pDoc )
{
	UINT sRowNum = RowNumber;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {
		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);
		if ( RowNumber == 0 ) {
			UINT tMax = tGStr->GetLength();
			const GeneStor *tStr = (const GeneStor *)*tGStr;
			for ( UINT i=0; i < tMax; ++i ) {
				// If this is a score row, just black and white.
				COLORREF TextC, BkC;
				if ( (sRowNum == 0)) {
					// Get BackGround Color
					pDoc->GetColors( &TextC, &BkC );
				} else {
					// Get Level Shade Color, checks Mode and LastShadeLevel
					TextC = tStr->TextColor;
					BkC = tStr->BackColor;
				}

				pRTFFile->CharOut( tStr->CharDisplay, TextC, BkC );

				// Lets do something for scoring.
				tStr++;
			}
			return;
		}
		RowNumber--;
	}
}

void  
CGVEdit::SetStatusBar(UINT nFlags, UINT PointXPosition, DWORD PointYPosition ) 
{
	// CPoint	sLoc = m_DataStartPoint;
	UINT sXLoc = m_XPosition;
	DWORD sYLoc = m_YPosition;

	POSITION tPos = ViewDataList.GetHeadPosition();
	while ( tPos != NULL ) {

		CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

		// SIZE tSize;
		DWORD tYSize = m_LineHeight;
		UINT tXSize = m_CharWidth * tGStr->GetLength();
		// CRect tRect ( sLoc, tSize );

		if ( (PointXPosition >= sXLoc && PointXPosition < (sXLoc + tXSize)) 
			&&
			(PointYPosition >= sYLoc && PointYPosition < (sYLoc + tYSize))
		) {

			if ( tGStr->GetGeneSegment()->GetStyle() != LINESEQUENCE ) {

				// Fill out selection stuff
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;

                ((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = (DWORD)(tGStr->GetStartPos() + tCount + 1);
				strncpy( 
					((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName, 
					"Column", 
					10 );
				((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[10] = 0;

			} else  {
				// Find Which residue ...
				UINT tCount = (PointXPosition - m_XPosition) / m_CharWidth;
				const GeneStor * pg = *tGStr;
				pg += tCount;
                
                ((CMainFrame *)AfxGetApp()->m_pMainWnd)->dwPosLoc = (DWORD)(pg->GeneSeqNumber);
				strncpy( 
					((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName, 
					(const char *)tGStr->GetGeneSegment()->GetTitle(), 
					10 );
				((CMainFrame *)AfxGetApp()->m_pMainWnd)->strPosSeqName[10] = 0;

			}

			return;
		}
		sYLoc += m_LineHeight;
	}
}

DWORD 
CGVEdit::ColPosFromCaret(UINT XPosition, DWORD YPosition ) 
{
	// CPoint	sLoc = m_DataStartPoint;
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();
	if ( XPosition < m_XPosition ) {
		return tGStr->GetStartPos();
	} else if ( XPosition > (m_XPosition + (m_CharWidth * tGStr->GetLength())) ) {
		return tGStr->GetStartPos() + tGStr->GetLength();
	}

	UINT tCount = (XPosition - m_XPosition) / m_CharWidth;
    return (DWORD)(tGStr->GetStartPos() + tCount);
}

BOOL 
CGVEdit::CaretPosFromColSeq( DWORD tCount, CGeneSegment* pCGSeg, UINT *XPos, DWORD *YPos )
{
	CGeneString * tGStr = (CGeneString *)ViewDataList.GetHead();

	UINT sXLoc = m_XPosition + ( tGStr->GetStartPos() * m_CharWidth);

	UINT tXSize = m_CharWidth * tGStr->GetLength();
	// CRect tRect ( sLoc, tSize );
	tCount = (tCount * m_CharWidth) + m_XPosition;

	if ( tCount >= sXLoc && tCount < (sXLoc + tXSize) ) {
		*XPos = tCount - sXLoc + m_XPosition;

		UINT sXLoc = m_XPosition;
		DWORD sYLoc = m_YPosition;

		POSITION tPos = ViewDataList.GetHeadPosition();
		while ( tPos != NULL ) {

			CGeneString * tGStr = (CGeneString *)ViewDataList.GetNext(tPos);

			// SIZE tSize;
			DWORD tYSize = m_LineHeight;
			UINT tXSize = m_CharWidth * tGStr->GetLength();
			// CRect tRect ( sLoc, tSize );

			if ( tGStr->GetGeneSegment() == pCGSeg ) {
				*YPos = sYLoc;
				return 1;
			}
			sYLoc += m_LineHeight;
		}
		return 1;
	}
	return 0;
}

