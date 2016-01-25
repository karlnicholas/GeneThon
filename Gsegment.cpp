//
// GSegment.cpp : implementation of the CGeneSegment class
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneSegment

IMPLEMENT_DYNCREATE(CGeneSegment, CObject)

/////////////////////////////////////////////////////////////////////////////
// CGeneSegment serialization

void CGeneSegment::Serialize(CArchive& ar)
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
// CGeneSegment diagnostics

#ifdef _DEBUG
void CGeneSegment::AssertValid() const
{
	CObject::AssertValid();
}

void CGeneSegment::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG


int 
CGeneSegment::Create ( 
	int nStyle, 
	const char *nTitle, 
	const char *nDescr, 
	double nWeight,
	HANDLE nText,
	DWORD nTextSize, 
	DWORD nTextStart, 
	COLORREF *nTextColor,
	COLORREF *nBackColor
) { 
	GeneStor tStor = {0,0,0,0};
	m_Style = nStyle;
	m_Title = nTitle;
	m_Descr = nDescr;
	m_Weight = nWeight;
	m_TextSize = nTextSize;
	m_TextStart = nTextStart;
	m_Expanded = 0;

	TextColor = nTextColor;
	BackColor = nBackColor;

	m_Text = GlobalAlloc ( GMEM_FLAG, m_TextSize * sizeof(GeneStor) );
	if ( m_Text == NULL ) {
		AfxMessageBox("Create:GlobalAlloc:Fail:1");
		return 0;
	}
	GeneStor *pDWD = (GeneStor *)GlobalLock( m_Text );
	if ( pDWD == NULL ) {
		AfxMessageBox("Create:GlobalLock:Fail:1");
		return 0;
	}
	char *pcS = (char *)GlobalLock( nText );
	if ( pcS == NULL ) {
		AfxMessageBox("Create:GlobalLock:Fail:2");
		return 0;
	}

	DWORD tGeneSeqNumber = m_TextStart;
	for ( DWORD i = 0L; i < nTextSize; ++i ) {
		tStor.CharGene = *pcS++;
		tStor.CharDisplay = tStor.CharGene;

		tStor.TextColor = *TextColor;
		tStor.BackColor = *BackColor;

		// if ( (tStor.CharGene != '-') && (tStor.CharGene != '.') && (tStor.CharGene != ' ') ) {
		char tChar = toupper ( tStor.CharGene );
		if ( tChar >= 'A' && tChar <= 'Z' ) {
			tStor.GeneSeqNumber = tGeneSeqNumber++;
		} else {
			tStor.GeneSeqNumber = 0L;
		}
		
		*pDWD++ = tStor;
	}

	m_LastResidue = tGeneSeqNumber;

	GlobalUnlock(m_Text);
	GlobalUnlock(nText);

	return 1;
}

void 
CGeneSegment::CreateCopy ( CGeneSegment *poCGSeg, DWORD nStart, DWORD nLen )
{
//	int nStyle, 
//	const char *nTitle, 
//	const char *nDescr, 
//	double nWeight,
//	HANDLE nText,
//	DWORD nTextSize, 
//	DWORD nTextStart, 
//	char	nGapChar,
//	COLORREF *nTextColor, 
//	COLORREF *nBackColor, 
//	int	nDisplayGroup
//) { 
//			tCGSeg->GetStyle(), 
//			tCGSeg->GetTitle(),
//			tCGSeg->GetDescr(), 
//			tCGSeg->GetWeight(), 
//			tCGSeg->MidText(tStart, tLen), 
//			tLen, 
//			tCGSeg->GetTextStart() + tStart, 
//			tCGSeg->GetGapChar(), 
//			, 
//			tCGSeg->BackColor, 
//			
//		);
	m_Expanded = 0;
	
	m_Style = poCGSeg->GetStyle();
	m_Title = poCGSeg->GetTitle();
	m_Descr = poCGSeg->GetDescr();
	m_Weight = poCGSeg->GetWeight();
	m_TextSize = nLen;
	
	TextColor = poCGSeg->TextColor;
	BackColor = poCGSeg->BackColor;
	m_Text = poCGSeg->MidText(nStart, nLen);

	SetTextStart( poCGSeg->GetTextStart() + nStart );

	CPAIR tPair;
	DWORD dwPos;
	const CMapDWORDToCPAIR& oMap = poCGSeg->GetMapCPAIR();
	POSITION tPos = oMap.GetStartPosition();
	while ( tPos != NULL ) {
		oMap.GetNextAssoc(tPos, dwPos, tPair);
		if ( dwPos > nStart && dwPos < (nStart + nLen) ) {
			m_mapCPAIR[dwPos - nStart] = tPair;
		}
	}

	char tChar;
	const CMapDWORDToChar& ocMap = poCGSeg->GetMapChar();
	tPos = ocMap.GetStartPosition();
	while ( tPos != NULL ) {
		ocMap.GetNextAssoc(tPos, dwPos, tChar);
		if ( dwPos > nStart && dwPos < (nStart + nLen) ) {
			m_mapChar[dwPos - nStart] = tChar;
		}
	}
}



HANDLE 
CGeneSegment::MidText( DWORD first, DWORD count ) const 
{
	DWORD Size = m_TextSize;
	if ( Size < first ) return NULL;
	Size = Size - first;
	Size = (Size < count) ? Size : count;

	HANDLE hnSeg = GlobalAlloc(GMEM_FLAG, Size * sizeof(GeneStor));
	if ( hnSeg == NULL ) {
		AfxMessageBox("MidText:GlobalAlloc:Fail:1");
		return NULL;
	}

	GeneStor *pn = (GeneStor *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		AfxMessageBox("MidText:GlobalLock:Fail:1");
		return NULL;
	}

	GeneStor *pc = (GeneStor *)GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("MidText:GlobalLock:Fail:2");
		return NULL;
	}
	pc += first;
	
	while ( Size-- ) {
		*pn++ = *pc++;
	}
	
	GlobalUnlock(m_Text);
	GlobalUnlock(hnSeg);
	return hnSeg;
}

HANDLE 
CGeneSegment::MidText( DWORD first ) const  
{
	DWORD Size = m_TextSize;
	if ( Size < first ) return NULL;
	Size = Size - first;

	HANDLE hnSeg = GlobalAlloc(GMEM_FLAG, Size * sizeof(GeneStor) );
	if ( hnSeg == NULL ) {
		AfxMessageBox("MidText:GlobalAlloc:Fail:1");
		return NULL;
	}

	GeneStor *pn = (GeneStor *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		AfxMessageBox("MidText:GlobalLock:Fail:1");
		return NULL;
	}

	GeneStor *pc = (GeneStor *)GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("MidText:GlobalLock:Fail:2");
		return NULL;
	}
	pc += first;
	
	while ( Size-- ) {
		*pn++ = *pc++;
	}
	
	GlobalUnlock(m_Text);
	GlobalUnlock(hnSeg);
	return hnSeg;
}

// Zero Terminated Text of Residues for the clipboard
HANDLE 
CGeneSegment::GetResidues() const  
{
	DWORD Size = m_TextSize;

	HANDLE hnSeg = GlobalAlloc(GMEM_DDESHARE, (Size + 1) );
	if ( hnSeg == NULL ) {
		AfxMessageBox("GetResidues:GlobalAlloc:Fail:1");
		return NULL;
	}

	char *pn = (char *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		AfxMessageBox("GetResidues:GlobalLock:Fail:1");
		return NULL;
	}

	GeneStor *pc = (GeneStor *)GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("GetResidues:GlobalLock:Fail:2");
		return NULL;
	}
	
	while ( Size-- ) {
		*pn++ = pc->CharGene;
		pc++;
	}
	
	*pn = 0;
	
	GlobalUnlock(m_Text);
	GlobalUnlock(hnSeg);
	return hnSeg;
}


HANDLE 
CGeneSegment::LeftText( DWORD count ) const 
{
	DWORD Size = m_TextSize;
	Size = (Size < count) ? Size : count;

	HANDLE hnSeg = GlobalAlloc( GMEM_FLAG, Size * sizeof(GeneStor) );
	if ( hnSeg == NULL ) {
		AfxMessageBox("LeftText:GlobalAlloc:Fail:1");
		return NULL;
	}

	GeneStor *pn = (GeneStor *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		AfxMessageBox("LeftText:GlobalLock:Fail:1");
		return NULL;
	}

	GeneStor *pc = (GeneStor *)GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("LeftText:GlobalLock:Fail:2");
		return NULL;
	}
	
	while ( Size-- ) {
		*pn++ = *pc++;
	}
	
	GlobalUnlock(m_Text);
	GlobalUnlock(hnSeg);
	return hnSeg;
}

HANDLE 
CGeneSegment::RightText( DWORD count ) const 
{
	DWORD Size = m_TextSize;
	DWORD first;
	count = (Size < count) ? Size : count;
	first = Size - count;

	HANDLE hnSeg = GlobalAlloc( GMEM_FLAG,  count * sizeof(GeneStor) );
	if ( hnSeg == NULL ) {
		AfxMessageBox("RightText:GlobalAlloc:Fail:1");
		return NULL;
	}

	GeneStor *pn = (GeneStor *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		AfxMessageBox("RightText:GlobalLock:Fail:1");
		return NULL;
	}

	GeneStor *pc = (GeneStor *)GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("RightText:GlobalLock:Fail:2");
		return NULL;
	}
	pc += first;
	
	while ( count-- ) {
		*pn++ = *pc++;
	}
	
	GlobalUnlock(m_Text);
	GlobalUnlock(hnSeg);
	return hnSeg;
}

int
CGeneSegment::AppendFiller(DWORD Length)
{
	DWORD Size = m_TextSize;
	GeneStor tFiller;

	if (GetStyle() != LINESEQUENCE) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.GeneSeqNumber = 0L;
	}
	else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	m_Text = GlobalReAlloc(m_Text, (Size + Length) * sizeof(GeneStor), GMEM_MOVEABLE);
	if (m_Text == NULL) {
		AfxMessageBox("AppendFiller:GlobalReAlloc:Fail:1");
		return 0;
	}
	GeneStor * pc = (GeneStor*)GlobalLock(m_Text);
	if (pc == NULL) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return 0;
	}

	pc += Size;

	m_TextSize += Length;

	while (Length--) {
		*pc++ = tFiller;
	}

	// NULL terminate

	GlobalUnlock(m_Text);

	return 1;
}


void
CGeneSegment::SetShade ( DWORD Position, COLORREF nTextColor, COLORREF nBackColor, BOOL AddRemShade )
{

	if ( Position >= m_TextSize ) {
		return;
	}

	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	pc += Position;

	pc->TextColor = nTextColor;
	pc->BackColor = nBackColor;

	GlobalUnlock(m_Text);

	CPAIR tPair;

	if ( AddRemShade ) {
		tPair.rgbText = nTextColor;
		tPair.rgbBack = nBackColor;
		m_mapCPAIR[Position] = tPair;
//		TRACE("SetShade(%ld)\n", Position);
	} else {
		if ( m_mapCPAIR.Lookup(Position, tPair ) ) {
			m_mapCPAIR.RemoveKey(Position);
		}
//		TRACE("RemoveShade(%ld)\n", Position);
	}

}

void 
CGeneSegment::ResetShades()
{
	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	CPAIR tPair;
	DWORD dwPos;
	POSITION tPos = m_mapCPAIR.GetStartPosition();
	while ( tPos != NULL ) {
		m_mapCPAIR.GetNextAssoc(tPos, dwPos, tPair);
		pc[dwPos].TextColor = tPair.rgbText;
		pc[dwPos].BackColor = tPair.rgbBack;
	}

	GlobalUnlock(m_Text);
}

void
CGeneSegment::SetComment ( DWORD Position, char nChar )
{

	if ( Position >= m_TextSize ) {
		return;
	}
	
	if ( GetStyle() == LINESEQUENCE ) {
		return;
	}

	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	pc += Position;

	pc->CharDisplay = nChar;

	GlobalUnlock(m_Text);

	char tChar;
	if ( nChar != ' ' ) {
		m_mapChar[Position] = nChar;
	} else {
		if ( m_mapChar.Lookup(Position, tChar ) ) {
			m_mapChar.RemoveKey(Position);
		}
	}

}

void 
CGeneSegment::ResetComments()
{
	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	char tChar;
	DWORD dwPos;
	POSITION tPos = m_mapChar.GetStartPosition();
	while ( tPos != NULL ) {
		m_mapChar.GetNextAssoc(tPos, dwPos, tChar);
		pc[dwPos].CharDisplay = tChar;
	}

	GlobalUnlock(m_Text);
}

void
CGeneSegment::SetResidue ( DWORD Position, char nChar )
{

	if ( Position >= m_TextSize ) {
		return;
	}
	
	GeneStor * pc;
	GeneStor * spc;
	pc = spc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	pc += Position;

	pc->CharDisplay = nChar;
	pc->CharGene = nChar;
	//
	pc->TextColor = *TextColor;
	pc->BackColor = *BackColor;
	//
//	char tChar = toupper ( nChar );
//	if ( pc->GeneSeqNumber == 0 && (tChar >= 'A' && tChar <= 'Z') ) {

		DWORD tGeneSeqNumber = m_TextStart;

		for ( DWORD i = 0L; i < m_TextSize; ++i ) {

			char tChar = toupper ( spc->CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				spc->GeneSeqNumber = tGeneSeqNumber++;
			} else {
				spc->GeneSeqNumber = 0L;
			}
			
			spc++;
		}

		m_LastResidue = tGeneSeqNumber;
//	}


	GlobalUnlock(m_Text);

}

void
CGeneSegment::SetResidueText( HANDLE hText, DWORD StartPos, DWORD EndPos )
{

	if ( StartPos >= m_TextSize || EndPos >= m_TextSize ) return;
	
	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return;
	}

	GeneStor *pn = (GeneStor *)GlobalLock(hText);
	if ( pn == NULL ) {
		AfxMessageBox("MidText:GlobalLock:Fail:1");
		return;
	}

	DWORD m_StartPos = StartPos;
	DWORD Count = EndPos - StartPos + 1;

	pc += m_StartPos;

	while ( Count-- ) {
		pc->CharGene = pn->CharGene;
		pc++;
		pn++;
	}

	GlobalUnlock(hText);
	GlobalUnlock(m_Text);

}

void 
CGeneSegment::LockAndLoad()
{
	m_Text = GlobalReAlloc(m_Text, (m_TextSize + 1000) * sizeof(GeneStor), GMEM_MOVEABLE);
	if ( m_Text == NULL ) {
		AfxMessageBox("LockAndLoad:GlobalReAlloc:Fail:1");
		return;
	}

	m_pMyGeneStor = (GeneStor *)GlobalLock(m_Text);
	if ( m_pMyGeneStor == NULL ) {
		AfxMessageBox("LockAndLoad:GlobalLock:Fail:2");
		return;
	}

	m_AlignExtra = 1000;
}

void 
CGeneSegment::AlignDone()
{

	GlobalUnlock(m_Text);
			
	m_Text = GlobalReAlloc(m_Text, (m_TextSize) * sizeof(GeneStor), GMEM_MOVEABLE);
	if ( m_Text == NULL ) {
		AfxMessageBox("AlignDone:GlobalReAlloc:Fail:1");
		return;
	}
}


char CGeneSegment::AlignGet(DWORD Index)
{
	return m_pMyGeneStor[Index].CharGene;
}

