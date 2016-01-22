
#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


void CGenethonDoc::OnGeneview()
{
	// TODO: Add your command handler code here
	if ( m_pGeneView == NULL ) {
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenGeneView();
	} else {
		m_pGeneView->GetParentFrame()->ActivateFrame();
		m_pGeneView->Invalidate();
	}
	
}

void CGenethonDoc::OnSummaryview()
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pSummaryView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenSummaryView();
		} else {
			m_pSummaryView->GetParentFrame()->ActivateFrame();
			m_pSummaryView->Invalidate();
		}
	}
}

void CGenethonDoc::OnUpdateSummaryview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}

void CGenethonDoc::OnFileimport() 
{
	// TODO: Add your command handler code here
	SequenceImport();

}

void CGenethonDoc::OnFileexport() 
{
	// TODO: Add your command handler code here
	SequenceExport();
}


void CGenethonDoc::OnGeneloadini()
{

	int sType = m_UserVars.m_ProjectType;

	GetIniDefaults();
	
	m_UserVars.m_ProjectType = sType;
	
	SetModifiedFlag();
}


BOOL CGenethonDoc::CheckMatch( char cF, char cS)
{
	BOOL match = FALSE;

	if ( m_UserVars.m_ProjectType > 1 ) {
		switch( cF ) {
		case 'A': match = (cS == 'A'); break;
		case 'G': match = (cS == 'G'); break;
		case 'C': match = (cS == 'C'); break;
		case 'T': match = (cS == 'T'); break;
		case 'U': match = (cS == 'U'); break;
		case 'Y': match = (cS == 'C' || cS == 'T' || cS == 'U' ); break;
		case 'R': match = (cS == 'A' || cS == 'G' ); break;
		case 'W': match = (cS == 'A' || cS == 'T' || cS == 'U' ); break;
		case 'S': match = (cS == 'C' || cS == 'G' ); break;
		case 'K': match = (cS == 'T' || cS == 'U' || cS == 'G' ); break;
		case 'M': match = (cS == 'C' || cS == 'A' ); break;
		case 'B': match = (cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'D': match = (cS == 'A' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'H': match = (cS == 'A' || cS == 'C' || cS == 'T' || cS == 'U' ); break;
		case 'V': match = (cS == 'A' || cS == 'C' || cS == 'G' ); break;
		case 'N': match = (cS == 'A' || cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		case 'X': match = (cS == 'A' || cS == 'C' || cS == 'G' || cS == 'T' || cS == 'U' ); break;
		}
	} else {
		if ( cF == 'X' && ( cS >= 'A' && cS <= 'Z') ) match = TRUE;
		else if ( cF == cS ) match = TRUE;
	}
	return match;
}


void CGenethonDoc::OnCopycons() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;

	// CWnd
	if ( !OpenClipboard(AfxGetMainWnd()->m_hWnd) ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	BeginWaitCursor(); // Let em know
	

	int ConsensusCount = -1;
	int tRC = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment row. here
	CGeneSegment *pConsSeg = NULL;

	if ( m_UserVars.m_ConsensusLine == 0 ) {
		// Use Top Consensus Row
		ConsensusCount = 1;
	} else if ( m_UserVars.m_ConsensusLine == 1 ) {
		// Use Bottom Consensus Row
		ConsensusCount = tRC - 1;
	}

	if ( ConsensusCount == -1 ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "No Consensus Line!" );
		return;
	}

	int i = 0;
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( i == ConsensusCount ) {
			pConsSeg = tCGSeg;
			break;
		}
		i++;
	}

	if ( pConsSeg == NULL ) {
		EndWaitCursor(); // Let em know
		return;
	}

	DWORD Size = pConsSeg->GetTextLength();

	CString BuildString;

	GeneStor *pc = (GeneStor *)GlobalLock(pConsSeg->GetTextHandle());
	if ( pc == NULL ) {
		AfxMessageBox("GetConsensus:GlobalLock:Fail:2");
		return;
	}

	BuildString = ">" + GetTitle().SpanExcluding(".") + "\r\n";

	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = pConsSeg->GetTextLength();

	while ( (CurPos + 60L) < Len ) {

		// Build data blocks
		GeneStor *tgs = pc + CurPos;
		for ( int j = 0; j < 60; ++j ) {
			char tChar = toupper( tgs->CharDisplay );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				DataBlock[j] = tgs->CharDisplay;
			} else {
				DataBlock[j] = '-';
			}

			tgs++;
		}
		DataBlock[60] = 0;

		BuildString += CString(DataBlock) + "\r\n";

		CurPos += 60L;

	};
	
	// Do Last set of lines 

	Len = pConsSeg->GetTextLength() - CurPos;
	

	// Build data blocks
	GeneStor *tgs = pc + CurPos;
	for ( unsigned int j = 0; j < Len; ++j ) {
		char tChar = toupper( tgs->CharDisplay );
		if ( tChar >= 'A' && tChar <= 'Z' ) {
			DataBlock[j] = tgs->CharDisplay;
		} else {
			DataBlock[j] = '-';
		}
		tgs++;
	}
	DataBlock[Len] = 0;

	BuildString += CString(DataBlock) + "\r\n";
	

	GlobalUnlock(pConsSeg->GetTextHandle());
		
	HANDLE hnSeg = GlobalAlloc(GMEM_DDESHARE, BuildString.GetLength() + 1 );
	if ( hnSeg == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalAlloc:Fail:1");
		return;
	}

	char *pn = (char *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalLock:Fail:1");
		return;
	}

	memcpy ( pn, (const char *)BuildString, BuildString.GetLength() );
	pn[BuildString.GetLength()] = 0;

	GlobalUnlock(hnSeg);
	
	if ( SetClipboardData ( CF_TEXT, hnSeg ) == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "SetClipboardData Fails" );
	}
	
	if ( !CloseClipboard() ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}
	
	EndWaitCursor(); // Let em know
	
}

void CGenethonDoc::OnUpdateCopycons(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
	
}


void CGenethonDoc::OnConsprosite() 
{
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;

	// CWnd
	if ( !OpenClipboard(AfxGetMainWnd()->m_hWnd) ) {
		AfxMessageBox("Cannot Open Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	
	
	if ( !EmptyClipboard() ) {
		AfxMessageBox("Cannot Empty Clipboard", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	BeginWaitCursor(); // Let em know
	

	CString PathName;

	if ( pGSFiller == NULL ) {
		return;
	}
	

	unsigned long Score = 0;


//	DWORD SegLength = ((CGeneSegment*)pGSFiller->SegDataList.GetHead())->GetTextLength();

	DWORD StartRange = 0L;
	DWORD EndRange = ((CGeneSegment*)pGSFiller->SegDataList.GetHead())->GetTextLength() - 1;
	
	DWORD iSeqCount = 0;
	ShadeSegStc *pSSArr = new ShadeSegStc[pGSFiller->SegDataList.GetCount()];
	
	CGeneSegment *tCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			pSSArr[iSeqCount].pCGSeg = tCGSeg;
			pSSArr[iSeqCount].pGeneStor = (GeneStor *) GlobalLock( tCGSeg->GetTextHandle() );
			if ( pSSArr[iSeqCount].pGeneStor == NULL) AfxThrowMemoryException();
			iSeqCount++;
		}
	}
	


	CString BuildString;
//	BuildString = ">" + GetTitle().SpanExcluding(".") + "\r\n";

	
	DWORD CurPos = 0;
	int first = 1;
	int dArr[26];
	int found = 0;
		
	for ( DWORD dwl = StartRange; dwl <= EndRange; ++dwl ) {

		memset ( dArr, 0, sizeof(dArr) );

		if ( !first && found) BuildString += "-";
		first = 0;

		found = 0;

		for ( DWORD di=0; di < iSeqCount; ++di ) {
			char tChar = toupper ( pSSArr[di].pGeneStor[dwl].CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				dArr[tChar - 'A'] = 1;
			}
		}
		for ( int i=0; i < 26; ++i ) {
			switch (i + 'A') {
			case 'A':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'K':
			case 'L':
			case 'M':
			case 'N':
			case 'P':
			case 'Q':
			case 'R':
			case 'S':
			case 'T':
			case 'V':
			case 'W':
			case 'Y':
				if ( dArr[i] ) found++;
				break;
			}
		}
		if ( found == 1 ) {
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] ) BuildString += "" + i + 'A';
					break;
				}
			}
		} else if ( found == 20 ) {
			BuildString += "X";
		} else if ( found > 10 ) {
			BuildString += "{";
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] == 0 ) BuildString += "" + i + 'A';
					break;
				}
			}
			BuildString += "}";
		} else if ( found <= 10 && found > 0 ) {
			BuildString += "[";
			for ( int i=0; i < 26; ++i ) {
				switch (i + 'A') {
				case 'A':
				case 'C':
				case 'D':
				case 'E':
				case 'F':
				case 'G':
				case 'H':
				case 'I':
				case 'K':
				case 'L':
				case 'M':
				case 'N':
				case 'P':
				case 'Q':
				case 'R':
				case 'S':
				case 'T':
				case 'V':
				case 'W':
				case 'Y':
					if ( dArr[i] ) BuildString += "" +  i + 'A';
					break;
				}
			}
			BuildString += "]";
		}
	}
	BuildString += ".";

	delete pSSArr;

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			GlobalUnlock( tCGSeg->GetTextHandle() );
		}
	}
	
	HANDLE hnSeg = GlobalAlloc(GMEM_DDESHARE, BuildString.GetLength() + 1 );
	if ( hnSeg == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalAlloc:Fail:1");
		return;
	}

	char *pn = (char *)GlobalLock(hnSeg);
	if ( pn == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox("GetConsensus:GlobalLock:Fail:1");
		return;
	}

	memcpy ( pn, (const char *)BuildString, BuildString.GetLength() );
	pn[BuildString.GetLength()] = 0;

	GlobalUnlock(hnSeg);
	
	if ( SetClipboardData ( CF_TEXT, hnSeg ) == NULL ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "SetClipboardData Fails" );
	}
	
	if ( !CloseClipboard() ) {
		EndWaitCursor(); // Let em know
		AfxMessageBox( "CloseClipboard Failed", MB_OK | MB_ICONEXCLAMATION );
	}
	
	EndWaitCursor(); // Let em know
	
}


void CGenethonDoc::OnUpdateConsprosite(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );

}

void CGenethonDoc::OnShowmanshade()
{
	m_UserVars.m_ShowManShade = !m_UserVars.m_ShowManShade;
}

void CGenethonDoc::OnUpdateShowman(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowManShade );

}

void CGenethonDoc::OnShowcomments()
{
	m_UserVars.m_ShowComments = !m_UserVars.m_ShowComments;
}

void CGenethonDoc::OnUpdateShowcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowComments );

}

void CGenethonDoc::OnClearcomments() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			tCGSeg->ClearComments();
		}
	}

	SetModifiedFlag();
}

void CGenethonDoc::OnClearmanshade() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			tCGSeg->ClearShades();
		}
	}

	SetModifiedFlag();
}


void CGenethonDoc::OnSelectarrseq() 
{
	// TODO: Add your command handler code here
	CSelArrSeq tDlg;
	tDlg.pDoc = this;
	tDlg.DoModal();
	UpdateAllViews(NULL);
}


void CGenethonDoc::OnComplimentsel() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			if ( tCGSeg->GetArrangeFlag() ) {
				tCGSeg->SetArrangeFlag(0);
			} else {
				tCGSeg->SetArrangeFlag(1);
			}
		}
	}

	UpdateAllViews(NULL);
	
}

void CGenethonDoc::OnGenereportview() 
{
	
	if ( m_pTextView == NULL ) {
	
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
	} else {

		m_pTextView->GetParentFrame()->ActivateFrame();
		m_pTextView->Invalidate();
	}
	
}


void CGenethonDoc::ReplaceFromProj(DWORD StartPos, DWORD EndPos) 
{
	// TODO: Add your command handler code here

	int count = 0;
	CGenethonDoc *poDoc;
	CMultiDocTemplate* pMDTmpl = ((CGenethonApp *)AfxGetApp())->m_pGenethonTemplate;

	POSITION dPos = pMDTmpl->GetFirstDocPosition( );
	while ( dPos != NULL ) {
		poDoc = (CGenethonDoc*)pMDTmpl->GetNextDoc(dPos);
		if ( poDoc == this ) continue;
		count++;
		break;
	}

	if ( !count ) {
		AfxMessageBox("No Other Project To Select From!");
		return;
	}
	
	CSelProject pDlg;
	pDlg.pDoc = this;
	if ( pDlg.DoModal() != IDOK ) return;

	poDoc = pDlg.poDoc;

	if ( poDoc == NULL ) {
		AfxMessageBox("No Other Project Selected!");
		return;
	}

	CGSFiller *poFiller = poDoc->pGSFiller;
	if ( poFiller == NULL ) return;

	if ( pGSFiller == NULL ) return;

	CGeneSegment *pCGSeg;
	CGeneSegment *poCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		POSITION pPos = poFiller->SegDataList.GetHeadPosition();
		while (pPos != NULL ) {
			poCGSeg = (CGeneSegment *)poFiller->SegDataList.GetNext(pPos);
			if ( poCGSeg->GetStyle() != LINESEQUENCE ) continue;
			if ( pCGSeg->GetTitle() == poCGSeg->GetTitle() ) {
				pCGSeg->ReplaceWith( StartPos, EndPos, poCGSeg->GetTextHandle(), poCGSeg->GetTextLength() );
				break;
			}
		}
	}

	ReSizeRows();

	SetModifiedFlag();
}
