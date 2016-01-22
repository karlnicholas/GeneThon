// GVEditFill.cpp : implementation of the CGVEditFill class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGVEditFill

IMPLEMENT_DYNCREATE(CGVEditFill, CObject)


CGVEditFill::CGVEditFill(): CGeneViewBase()
{
	// TODO: add construction code here
}


CGVEditFill::~CGVEditFill()
{
}


/////////////////////////////////////////////////////////////////////////////
// CGVEditFill serialization

void CGVEditFill::Serialize(CArchive& ar)
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
// CGVEditFill diagnostics

#ifdef _DEBUG
void CGVEditFill::AssertValid() const
{
	CObject::AssertValid();
}

void CGVEditFill::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CGVEditFill::CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int)
{
	// m_DataStartPoint = ViewRect.TopLeft();
	*XSize = m_XSize;
	*YSize = m_YSize;
}

void 
CGVEditFill::OnDraw( DrawStruct *DrawStc )
{
	CGenethonDoc *pDoc = ((CGenethonView *)DrawStc->pView)->GetDocument();

	CBrush tBrush;

//	if ( (m_YPosition + m_YSize) > DrawStc->ReDrawTop && m_YPosition <= DrawStc->ReDrawBottom ) {
	if ( (m_YPosition + m_YSize) > DrawStc->ReDrawTop && m_YPosition < DrawStc->ReDrawBottom ) {

		UINT tXLoc1 = m_XPosition + m_XSize;
		UINT tXLoc2 = m_XPosition;

		if ( tXLoc1 > DrawStc->ReDrawLeft && tXLoc2 <= DrawStc->ReDrawRight ) {


			COLORREF TextColor, BkColor;

			pDoc->GetColors( &TextColor, &BkColor );
/*
			UINT x1 = tXLoc2 - DrawStc->DisplayXPosition;
			UINT x2 = tXLoc1 - DrawStc->DisplayXPosition;
			UINT y1 = (UINT)(m_YPosition - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset;
			UINT y2 = (UINT)(m_YPosition + m_YSize - DrawStc->DisplayYPosition) + DrawStc->PrintYOffset;
*/
			UINT x1 = tXLoc2;
			UINT x2 = tXLoc1;
			UINT y1 = (UINT)(m_YPosition);
			UINT y2 = (UINT)(m_YPosition + m_YSize);

			if ( DrawStc->ReDrawLeft > x1 ) x1 = DrawStc->ReDrawLeft;
			if ( DrawStc->ReDrawRight < x2 ) x2 = DrawStc->ReDrawRight;
			if ( DrawStc->ReDrawTop > y1 ) y1 = (UINT)DrawStc->ReDrawTop;
			if ( DrawStc->ReDrawBottom < y2 ) y2 = (UINT)DrawStc->ReDrawBottom;

			CRect tcRect( 
				x1 - DrawStc->DisplayXPosition, 
				(y1 - (UINT)DrawStc->DisplayYPosition) + DrawStc->PrintYOffset, 
				x2 - DrawStc->DisplayXPosition, 
				(y2 - (UINT)DrawStc->DisplayYPosition) + DrawStc->PrintYOffset
			);

			tBrush.CreateSolidBrush( BkColor );
			DrawStc->pDC->FillRect ( tcRect, &tBrush );
			tBrush.DeleteObject();
		}
	}
}


void 
CGVEditFill::CopyText(char * tString, DWORD *dwCount, UINT RowNumber )
{

}

void 
CGVEditFill::CountCopyText(DWORD *dwCount )
{
	*dwCount = 0;
}

void 
CGVEditFill::WritePict(CPictFile* pPictFile, UINT RowNumber, CGenethonDoc *pDoc )
{

}

void 
CGVEditFill::WriteHTML(CHTMLFile* pHTMLFile, UINT RowNumber, CGenethonDoc *pDoc )
{

}
