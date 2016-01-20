// phylseq.cpp : implementation of the CPhyloSeq class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhyloSeq

IMPLEMENT_DYNCREATE(CPhyloSeq, CObject)


CPhyloSeq::CPhyloSeq(): CPhyloGenBase()
{
	// TODO: add construction code here
}


CPhyloSeq::~CPhyloSeq()
{

}


/////////////////////////////////////////////////////////////////////////////
// CPhyloSeq serialization

void CPhyloSeq::Serialize(CArchive& ar)
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
// CPhyloSeq diagnostics

#ifdef _DEBUG
void CPhyloSeq::AssertValid() const
{
	CObject::AssertValid();
}

void CPhyloSeq::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

void 
CPhyloSeq::SetDepth( int Depth )
{
	m_Depth = Depth;
}	

void 
CPhyloSeq::WriteString( CString& ParseString )
{
	int AddComma = 0;
	
	if ( ((CPhyloNode*)m_pPGParent)->m_PhyloList.GetTail() != this )  {
		AddComma = 1;
	}

	ParseString += GetName();

	if ( !m_Weight.IsEmpty() ) {
		ParseString += ":" + m_Weight;
	}

	if ( AddComma ) {
		ParseString += ",\r\n";
	}

}

int
CPhyloSeq::CheckCounts(int ErrMsg)
{
	return 1;
}

int 
CPhyloSeq::DetermineDraw (CPhyloGenBase * pPSBLast)
{

	m_DrawType = DLABEL;
	return DLABEL;
	
}

void
CPhyloSeq::CallFromSeq( CView* pView )
{
	ASSERT( pView->IsKindOf( RUNTIME_CLASS(CPhylogenView)));
	CPhylogenView* pPGView = (CPhylogenView*)pView;
	pPGView->CallBackFromSeq(this);
}

void
CPhyloSeq::CallDocFromSeq( CDocument* pDoc )
{
	ASSERT( pDoc->IsKindOf( RUNTIME_CLASS(CGenethonDoc)));
	CGenethonDoc* pGDoc = (CGenethonDoc*)pDoc;
	pGDoc->CallDocFromSeq(this);
}

void
CPhyloSeq::CallDocFromDepth( CDocument* pDoc, int Depth )
{
}

void 
CPhyloSeq::CallSDFromNamedSeq( CDialog *pDlg, const CString& Name )
{
	if ( m_pSequence->GetTitle() == Name ) {
		CSeqDialog* pPSDlg = (CSeqDialog*)pDlg;
		pPSDlg->CallSDFromNamedSeq(this);
	}
}
