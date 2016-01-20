// gsfiller.cpp : implementation of the CGPFiller class
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGSFiller

IMPLEMENT_DYNCREATE(CGSFiller, CObject)


CGSFiller::CGSFiller(): CGeneSegBase()
{
	// TODO: add construction code here
}


CGSFiller::~CGSFiller()
{

	while ( !SegDataList.IsEmpty() ) {
		delete (CGeneSegment *) SegDataList.RemoveHead();
	}

	while ( !SegHeaderList.IsEmpty() ) {
		delete (CString *) SegHeaderList.RemoveHead();
	}

}


/////////////////////////////////////////////////////////////////////////////
// CGSFiller serialization

void CGSFiller::Serialize(CArchive& ar)
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
// CGSFiller diagnostics

#ifdef _DEBUG
void CGSFiller::AssertValid() const
{
	CObject::AssertValid();
}

void CGSFiller::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CGSFiller::AddHeader( CString* nString )
{
	SegHeaderList.AddTail( nString );
}

void 
CGSFiller::AddData(CGeneSegment* nSeg )
{
	SegDataList.AddTail(nSeg);
}

