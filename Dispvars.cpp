//
// DisplayVars.cpp : implementation of the CDisplayVars class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayVars

IMPLEMENT_DYNCREATE(CDisplayVars, CObject)

/////////////////////////////////////////////////////////////////////////////
// CDisplayVars serialization

void CDisplayVars::Serialize(CArchive& ar)
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
// CDisplayVars diagnostics

#ifdef _DEBUG
void CDisplayVars::AssertValid() const
{
	CObject::AssertValid();
}

void CDisplayVars::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


CDisplayVars::CDisplayVars()
{
}

CDisplayVars::~CDisplayVars()
{
}

void 
CDisplayVars::ClearVars( DisplayVars *nDisplayVars )
{
}

void
CDisplayVars::CopyVars( CDisplayVars *nDisplayVars, CDocument *pDC )
{

	CopyDisplayVars ( &m_DisplayVars, nDisplayVars, pDC );
}

void
CDisplayVars::CopyDisplayVars( DisplayVars *pDV, CDisplayVars *nDisplayVars, CDocument *pDC )
{

	nDisplayVars->GetTitleColors ( &pDV->m_TitleTextColor, &pDV->m_TitleBkColor);

}

void
CDisplayVars::SetDisplayVars( DisplayVars *pDV, CDocument *pDC )
{

	SetTitleColors ( pDV->m_TitleTextColor, pDV->m_TitleBkColor);

}
