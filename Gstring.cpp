// GVEdit.cpp : implementation of the CGPEdit class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneString

IMPLEMENT_DYNCREATE(CGeneString, CObject)


CGeneString::CGeneString()
{
	// TODO: add construction code here
	m_Selected = 0;
	m_enum = 0;

	m_GString = NULL;
}


CGeneString::~CGeneString()
{
	if ( m_GString != NULL ) {
		delete m_GString;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGeneString serialization

void CGeneString::Serialize(CArchive& ar)
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
// CGeneString diagnostics

#ifdef _DEBUG
void CGeneString::AssertValid() const
{
	CObject::AssertValid();
}

void CGeneString::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////

int 
CGeneString::SetString( 
	GeneStor  *pnString, 
	int nSize, 
	DWORD nStartPos, 
	CGeneSegment *pParent, 
	unsigned int eval

) {

	if ( m_GString != NULL ) {
		delete m_GString;
	}
	m_GString = new GeneStor[nSize];
	if ( m_GString == 0 ) {
		AfxMessageBox("SetNewString:new fail 1" );
		return 0;
	}
	m_TextColor = pParent->TextColor;
	m_BackColor = pParent->BackColor;

	m_SegSize = nSize;
	m_SegStartPos = nStartPos;
	pGeneSegment = pParent;
	m_enum = eval;
	memcpy ( m_GString, pnString, nSize * sizeof(GeneStor) );
	return 1;
}

int 
CGeneString::SetNewString( 
	GeneStor  *pnString, 
	int nSize 
) {
	if ( m_GString != NULL ) {
		delete m_GString;
	}
	m_GString = new GeneStor[nSize];
	
	if ( m_GString == 0 ) {
		AfxMessageBox("SetNewString:new fail 1" );
		return 0;
	}
	
	m_SegSize = nSize;
	memcpy ( m_GString, pnString, nSize * sizeof(GeneStor) );
	
	return 1;
}


void 
CGeneString::SetShade( int Position, COLORREF TextColor, COLORREF BackColor )
{
	if ( Position >= m_SegSize ) {
		return;
	}
	m_GString[Position].TextColor = TextColor;
	m_GString[Position].BackColor = BackColor;
}


void 
CGeneString::SetComment( int Position, char nChar )
{
	if ( Position >= m_SegSize || Position < 0) {
		return;
	}
	m_GString[Position].CharDisplay = nChar;

	m_GString[Position].TextColor = *m_TextColor;
	m_GString[Position].BackColor = *m_BackColor;
	m_GString[Position].CharScore = 0;
}

void 
CGeneString::SetResidue( int Position, char nChar )
{
	if ( Position >= m_SegSize || Position < 0) {
		return;
	}
	m_GString[Position].CharDisplay = nChar;

	m_GString[Position].TextColor = *m_TextColor;
	m_GString[Position].BackColor = *m_BackColor;
	m_GString[Position].CharScore = 0;
}

void
CGeneString::GetShade( int Position, COLORREF *TextColor, COLORREF *BackColor )
{
	if ( Position >= m_SegSize ) {
		return;
	}
	*TextColor = m_GString[Position].TextColor;
	*BackColor = m_GString[Position].BackColor;
	// return 
}


void
CGeneString::Select()
{
	m_Selected = 1;
}

void
CGeneString::DeSelect()
{
	m_Selected = 0;
}

int 
CGeneString::IsSelected()
{
	return m_Selected;
}
