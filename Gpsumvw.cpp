// gpsumvw.cpp : implementation of the CGPSumView class
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGPSumView

IMPLEMENT_DYNCREATE(CGPSumView, CObject)

void 
CGPSumView::AddHead( CGeneViewBase * pGP )
{

	UINT XSize;
	DWORD YSize;
	pGP->GetSize(&XSize, &YSize);

	m_XSize += XSize;
	m_YSize = YSize;

	ViewDataList.AddHead( pGP );
}



void 
CGPSumView::AddTail( CGeneViewBase * pGP )
{

	UINT XSize;
	DWORD YSize;
	pGP->GetSize(&XSize, &YSize);

	m_XSize += XSize;
	m_YSize = YSize;

	ViewDataList.AddTail( pGP );
}


CGPSumView::CGPSumView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CGPSumView serialization

void CGPSumView::Serialize(CArchive& ar)
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
// CGPSumView diagnostics

#ifdef _DEBUG
void CGPSumView::AssertValid() const
{
	CObject::AssertValid();
}

void CGPSumView::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


int 
CGPSumView::GetPartialPageSize(
	DWORD tPageTop, 
	DWORD tPageBottom, 
	DWORD *tPageAmount
) {
	
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVSummary) ) ) {
			return tGVB->GetPartialPageSize( tPageTop, tPageBottom, tPageAmount );
		}
	}
	return 0;
}

void 
CGPSumView::OnDraw( DrawStruct *m_DrawStc )
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	int FirstDraw = 0;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

		tGVB->OnDraw( m_DrawStc );

	}
}

//
void 
CGPSumView::OnLButtonDown(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet )
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenethonView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVSummary))
		) {
			tGVB->OnLButtonDown(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {

			tGVB->OnLButtonDown(nFlags, XPoint, YPoint, pWnd, pViewRet );

			break;
		}
	}
}

void 
CGPSumView::OnMouseMove(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenethonView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVSummary))
		) {
			tGVB->OnMouseMove(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
//		} else if ( tRect.PtInRect(point) ) {
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->OnMouseMove(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
		}
	}
}

void 
CGPSumView::OnLButtonUp(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd, VIEWRETSTRUCT *pViewRet)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
//		CRect tRect = tGVB->GetViewRect();
//		tRect.NormalizeRect();
		if ( 
			pViewRet->DDevice == CGenethonView::KEYBRD 
			&& tGVB->IsKindOf(RUNTIME_CLASS(CGVSummary))
		) {
			tGVB->OnLButtonUp(nFlags, XPoint, YPoint, pWnd, pViewRet );
			break;
//		} else if ( tRect.PtInRect(point) ) {
		} else if ( tGVB->IsPointWithin(XPoint, YPoint) ) {

			tGVB->OnLButtonUp(nFlags, XPoint, YPoint, pWnd, pViewRet );

			break;
		}
	}
}

void 
CGPSumView::OnLButtonDblClk(UINT nFlags, UINT XPoint, DWORD YPoint, CView *pWnd)
{

	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;
	
	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->OnLButtonDblClk(nFlags, XPoint, YPoint, pWnd );
			break;
		}
	}

}

void 
CGPSumView::InvalNewEndPoint( CView *pWnd, DWORD Range1, DWORD Range2)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsKindOf(RUNTIME_CLASS(CGVSummary) ) ) {
			((CGVSummary*)tGVB)->InvalNewEndPoint( pWnd, Range1, Range2 );
		}
	}
}

// RowNumber Not Used Here
void 
CGPSumView::WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc )
{
	CGeneViewBase *tGVB;

	tGVB = (CGeneViewBase *)ViewDataList.GetHead();
	
	UINT Count = tGVB->ViewDataList.GetCount();

	for ( UINT i=0; i < Count; ++i ) {

		POSITION tPos = ViewDataList.GetHeadPosition();
	
		while ( tPos != NULL ) {
			tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);

			tGVB->WritePict( pPictFile, i, pDoc );
		}
		
		// Add the CR/LF
		pPictFile->NewLine();
	}
}


void 
CGPSumView::SetStatusBar(UINT nFlags, UINT XPoint, DWORD YPoint)
{
	POSITION tPos = ViewDataList.GetHeadPosition();
	CGeneViewBase *tGVB;

	while ( tPos != NULL ) {
		tGVB = (CGeneViewBase *)ViewDataList.GetNext(tPos);
		if ( tGVB->IsPointWithin(XPoint, YPoint) ) {
			tGVB->SetStatusBar(nFlags, XPoint, YPoint );
			break;
		}
	}
}
