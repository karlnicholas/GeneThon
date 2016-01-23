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
CGeneSegment::InvalConsensus( DWORD *StartRange, DWORD *EndRange )
{

	DWORD tStartRange = *StartRange;
	DWORD tEndRange = *EndRange;
	if ( tStartRange >= m_TextSize ) {
		return 0;
	}
		
	if ( tEndRange >= m_TextSize ) {
		return 0;
	}

	// paranoia test
	if ( GetStyle() == LINESEQUENCE ) {
		return 0;
	}

	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	
	if ( pText == NULL ) {
		AfxMessageBox("InvalConsensus:GlobalLock:Fail:1");
		return 0;
	}

	GeneStor tFiller;

	tFiller.CharDisplay = '*';
	// tFiller.CharShade = 0;
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;
	tFiller.CharScore = 0;
	tFiller.GeneSeqNumber = 0L;


	GeneStor *spText = pText + tStartRange;
	DWORD tCount = tEndRange - tStartRange + 1;
	int Change = 0;

	// look for changes required.
	while (tCount-- ) {
		if ( spText->CharDisplay != '*' ) {
			Change = 1;
			break;
		}
		spText++;
	}

	if ( Change ) {

		spText = pText + tEndRange;
		tCount = tEndRange - tStartRange + 1;
		// look for changes required.
		while (tCount-- ) {
			if ( spText->CharDisplay == '*' ) {
				(*EndRange) = (*EndRange) - 1;
			} else {
				break;
			}
			spText--;
		}

		spText = pText + tStartRange;
		tCount = tEndRange - tStartRange + 1;

		// look for changes required.
		int Trim = 1;
		while (tCount-- ) {
			if ( Trim ) {
				if ( spText->CharDisplay == '*' ) {
					(*StartRange) = (*StartRange) + 1;
				} else {
					Trim = 0;
				}
			}
			*spText++ = tFiller;
		}
	}

	GlobalUnlock(m_Text);
	return Change;
}

int 
CGeneSegment::InvalScore( DWORD *StartRange, DWORD *EndRange )
{
	DWORD tStartRange = *StartRange;
	DWORD tEndRange = *EndRange;

	if ( tStartRange >= m_TextSize ) {
		return 0;
	}
		
	if ( tEndRange >= m_TextSize ) {
		return 0;
	}

	// paranoia test
	if ( GetStyle() == LINESEQUENCE ) {
		return 0;
	}

	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InvalScore:GlobalLock:Fail:1");
		return 0;
	}


	GeneStor *spText = pText + tStartRange;
	DWORD tCount = tEndRange - tStartRange + 1;
	int Change = 0;
	DWORD SegLength = m_TextSize;

	// look for changes required.
	while (tCount-- ) {
		if ( (spText->CharScore%2) != 0 ) {
			Change = 1;
			break;
		}
		spText++;
	}

	if ( Change ) {

		for ( tCount = tStartRange; tCount <= tEndRange; tCount++ ) {	 // Drawing loop
			if ( tCount == tStartRange ) {
				DWORD CheckCount = tCount;
				while ( 1 ) {
					if ( CheckCount == 0 ) {
						break;
					}
					CheckCount--;
					if ( (pText[CheckCount]).CharScore != 0
						&& (pText[CheckCount]).CharScore <= 4 
					) {
						if ( ((pText[CheckCount]).CharScore%2) != 0 ) {
							(pText[CheckCount]).CharScore += 1;
							*StartRange = CheckCount;
						}
					} else {
						break;
					}
				}
			} 
			// else 
			if ( tCount == tEndRange ) {
				// Right mode Position
				DWORD CheckCount = tEndRange;
				while ( (++CheckCount) < SegLength ) {
					if ( (pText[CheckCount]).CharScore != 0 
						&& (
							(pText[CheckCount]).CharScore <= 2 
							|| (pText[CheckCount]).CharScore >= 5
						)
					) {
						if ( ((pText[CheckCount]).CharScore%2) != 0 ) {
							(pText[CheckCount]).CharScore += 1;
							*EndRange = CheckCount;
						}
					} else {
						break;
					}
				}
			}

			if ( ((pText[tCount]).CharScore%2) != 0 ) {
				(pText[tCount]).CharScore += 1;
			}

		}

	}

	GlobalUnlock(m_Text);
	return Change;
	
}


//	void GetMovedRange( DWORD *StartRange, DWORD *EndRange ) const {
int 
CGeneSegment::DeleteDash ( DWORD Position )
{
	DWORD Count;
	GeneStor tFiller;
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {

		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	if ( Position >= m_TextSize ) {
		return 0;
	}
		
	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InvalConsensus:GlobalLock:Fail:1");
		return 0;
	}

	m_StartRange = Position;
	m_Expanded = 0;

	GeneStor *spText = pText + Position;
	
	GeneStor *spText2;
	
	char tChar = toupper ( spText->CharGene );
	if ( !(tChar >= 'A' && tChar <= 'Z') || (GetStyle() != LINESEQUENCE) ) {
		spText2 = spText + 1;
		Count = m_TextSize - Position - 1;
		
		m_EndRange = m_TextSize - 1;
	
		while ( Count-- ) {
			*spText++ = *spText2++;
		}
		
		*spText =  tFiller;
	
		GlobalUnlock(m_Text);
		return 1;
	}

	GlobalUnlock(m_Text);
	return 0;
}

int 
CGeneSegment::InsertDash ( DWORD Position )
{
	DWORD Count;
	GeneStor tFiller;
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	if ( Position >= m_TextSize ) {
		return 0;
	}
		
	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InsertDash:GlobalLock:Fail:1");
		return 0;
	}

	m_StartRange = Position;
	m_Expanded = 0;

	GeneStor *spText = pText + m_TextSize - 1;
	GeneStor *spText2;
	
	// if ( (spText->CharGene == '-') || (spText->CharGene == '.') || (spText->CharGene == ' ' )) {
	char tChar = toupper ( spText->CharGene );
	if ( !(tChar >= 'A' && tChar <= 'Z') ) {
		spText2 = spText - 1;
		Count = m_TextSize - Position - 1;
	} else {
		GlobalUnlock(m_Text);
		m_Text = GlobalReAlloc(m_Text, (m_TextSize + 1) * sizeof(GeneStor), GMEM_MOVEABLE);
		if ( m_Text == NULL ) {
			AfxMessageBox("InsertDash:GlobalReAlloc:Fail:1");
			return 0;
		}
		pText = (GeneStor *)GlobalLock(m_Text);
		if ( pText == NULL ) {
			AfxMessageBox("InsertDash:GlobalLock:Fail:2");
			return 0;
		}

		m_TextSize += 1;
		m_Expanded = 1;

		spText = pText + m_TextSize - 1;
		spText2 = spText - 1;
		Count = m_TextSize - Position - 1;
	}
	
	// Not really the answer is it ..	
	m_EndRange = m_TextSize - 1;

	while ( Count-- ) {
		*spText-- = *spText2--;
	}
	
	*spText =  tFiller;

	GlobalUnlock(m_Text);
	return 1;

}


int 
CGeneSegment::TestDeleteFillerRange( DWORD StartRange, DWORD EndRange )
{
	// Its always ok to delete a comment seq.
	if ( GetStyle() != LINESEQUENCE ) return 1;

	DWORD Count;
	DWORD i;
	if ( StartRange >= m_TextSize ) {
		return 0;
	}
	
	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("TestFillerRange:GlobalLock:Fail:1");
		return 0;
	}

	Count = EndRange - StartRange + 1;
	m_Expanded = 0;

	GeneStor *spText = pText + StartRange;
	

	// Find out how much re-alloc needs to be done
	for (i = 0; i < Count; ++i ) {
		if ( GetStyle() != LINESEQUENCE ) {
			if ( (spText->CharDisplay == ' ') ) {
				spText++;
				continue;
			} else {
				break;
			}
		} else {
			// if ( (spText->CharGene == '-') || (spText->CharGene == '.') ) {
			char tChar = toupper ( spText->CharGene );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				spText++;
				continue;
			} else {
				break;
			}
		}
	}
	
	GlobalUnlock(m_Text);
	return ( i == Count );		// True if good
}
	
void 
CGeneSegment::DeleteFillerRange( DWORD StartRange, DWORD EndRange, int ReNum )
{

	DWORD Count;
		
	if ( StartRange >= m_TextSize ) {
		return;
	}

	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("DeleteFillerRange:GlobalLock:Fail:1");
		return;
	}


	m_StartRange = StartRange;
	m_Expanded = 0;
	
	Count = m_TextSize - EndRange - 1;

	GeneStor *spText = pText + StartRange;
	
	GeneStor *spText2 = pText + EndRange + 1;
	
	while ( Count-- ) {
		*spText++ = *spText2++;
	}

	if ( ReNum ) {
		DWORD tGeneSeqNumber = m_TextStart;
		for ( DWORD i = 0L; i < m_TextSize; ++i ) {

			char tChar = toupper ( pText->CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				pText->GeneSeqNumber = tGeneSeqNumber++;
			} else {
				pText->GeneSeqNumber = 0L;
			}
			
			pText++;
		}

	}
	GlobalUnlock(m_Text);
	
	m_TextSize = m_TextSize - (EndRange - StartRange) - 1;

	m_Text = GlobalReAlloc(m_Text, (m_TextSize) * sizeof(GeneStor), GMEM_MOVEABLE);

	if ( m_Text == NULL ) { 
		AfxMessageBox("DeleteFillerRange:GlobalReAlloc:Fail:1");
	}

	return;

}

int 
CGeneSegment::InsertFillerRange ( DWORD StartRange, DWORD EndRange )
{
	DWORD Count;
	GeneStor tFiller;
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	if ( StartRange >= m_TextSize ) {
		return 0;
	}
	
	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InsertFillerRange:GlobalLock:Fail:1");
		return 0;
	}

	m_StartRange = StartRange;
	Count = EndRange - StartRange + 1;
	m_Expanded = 0;

	GeneStor *spText = pText + m_TextSize - 1;
	GeneStor *spText2;

	// Find out how much re-alloc needs to be done
	DWORD i;
	for ( i = 0; i < Count; ++i ) {
		char tChar = toupper ( spText->CharGene );
		if ( !(tChar >= 'A' && tChar <= 'Z') ) {
			spText--;
			continue;
		} else {
			break;
		}
	}
	
	if ( Count == i ) {	
		// No Re-alloc needed	
		// Point to Dest Data Position
		spText2 = spText;
		spText = pText + m_TextSize - 1;

		Count = m_TextSize - Count - StartRange;

	} else {

		DWORD tLoc = (spText - pText);
		
		GlobalUnlock(m_Text);
		
		m_Text = GlobalReAlloc(m_Text, (m_TextSize + Count - i) * sizeof(GeneStor), GMEM_MOVEABLE);
		if ( m_Text == NULL ) {
			AfxMessageBox("InsertFillerRange:GlobalReAlloc:Fail:1");
			return 0;
		}

		pText = (GeneStor *)GlobalLock(m_Text);
		if ( pText == NULL ) {
			AfxMessageBox("InsertFillerRange:GlobalLock:Fail:2");
			return 0;
		}

		m_TextSize += (Count - i);
		m_Expanded = (int)(Count - i);

		// Get offset of spText2
		spText2 = pText + tLoc;

		spText = pText + m_TextSize - 1;

		Count = m_TextSize - Count - StartRange;

	}

	// Not really the answer is it ..	
	m_EndRange = m_TextSize - 1;

	while ( Count-- ) {
		*spText-- = *spText2--;
	}
	
	Count = EndRange - StartRange + 1;
	while ( Count-- ) {
		*spText-- =  tFiller;
	}

	//
	
	GlobalUnlock(m_Text);
	return 1;

}

/*
		m_StartRange = Position;
		m_Expanded = 0;

		if ( Position >= m_TextSize ) {
			GlobalUnlock(m_Text);
			return 0;
		}
		
		GeneStor *spText = pText;
        
        MoveCount = Amount;		// Always the case for right movement

        do {


			Count = m_TextSize - Position;

			GeneStor *gpLE = spText + m_TextSize - 1;
			do {
				tChar = toupper ( gpLE->CharGene );
				if ( !(tChar >= 'A' && tChar <= 'Z') ) {
					Count--;
				}
				gpLE--;
			}
			while ( (!(tChar >= 'A' && tChar <= 'Z')) && Count );

			DWORD GrowBy = (m_TextSize - Position)


			pText = spText + Position;

			// Check we at a reasonable character to move.
			tChar = toupper ( pText->CharGene );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {

				GlobalUnlock(m_Text);
				return 0;
			}

			GeneStor tRep = tFiller;
			

			// Special case
			tNext = *pText;
	
			m_EndRange = Position;
//	        do { 
			while ( --Count ) {
//					break;
//				}
	
				tNext = *pText;
				*pText++ = tRep;
				tRep = tNext;
				tNext = *pText;

				m_EndRange++;
			}
//				tChar = toupper ( tNext.CharGene );
//			} while ( (tChar >= 'A' && tChar <= 'Z') );

			if ( !Count ) {
				GlobalUnlock(m_Text);
				m_Text = GlobalReAlloc(m_Text, (m_TextSize + Amount) * sizeof(GeneStor), GMEM_MOVEABLE);
				if ( m_Text == NULL ) {
					AfxMessageBox("MoveText:GlobalReAlloc:Fail:1");
					return 0;
				}
				pText = (GeneStor *)GlobalLock(m_Text);
				if ( pText == NULL ) {
					AfxMessageBox("MoveText:GlobalLock:Fail:1");
					return 0;
				}
				pText += (m_TextSize - 1);
				*pText++ = tRep;
				*pText = tNext;
				m_TextSize += Amount;
				m_Expanded = Amount;
				Amount--;
				if ( Amount ) {

					Count = m_TextSize - Position - Amount;
					GeneStor *pText2 = pText + Amount;

					while ( Count-- ) {
						*pText2-- = *pText--;
					}
					while ( Amount ) {
						*pText2-- =  tFiller;
						Amount--;
					}

				}
			} else {
				*pText = tRep;
				Position++;
				Amount--;
			}


		} while ( Amount );

*/

int 
CGeneSegment::SlideText ( DWORD Position, int Amount )
{
	int MoveCount = 0;
	DWORD Count;
	GeneStor tFiller;
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InsertFillerRange:GlobalLock:Fail:1");
		return 0;
	}

	if ( Amount > 0 ) {

		m_StartRange = Position;

		if ( Position >= m_TextSize ) {
			GlobalUnlock(m_Text);
			return 0;
		}
		
//		GeneStor *spText = pText;
        
        MoveCount = Amount;		// Always the case for right movement

		Count = Amount;
		m_Expanded = 0;

		GeneStor *spText = pText + m_TextSize - 1;
		GeneStor *spText2;

		// Find out how much re-alloc needs to be done
		DWORD i;
		for ( i = 0; i < Count; ++i ) {
			char tChar = toupper ( spText->CharGene );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				spText--;
				continue;
			} else {
				break;
			}
		}
		
		if ( Count == i ) {	
			// No Re-alloc needed	
			// Point to Dest Data Position
			spText2 = spText;
			spText = pText + m_TextSize - 1;

			Count = m_TextSize - Count - Position;

		} else {

			DWORD tLoc = (spText - pText);
			
			GlobalUnlock(m_Text);
			
			m_Text = GlobalReAlloc(m_Text, (m_TextSize + Count - i) * sizeof(GeneStor), GMEM_MOVEABLE);
			if ( m_Text == NULL ) {
				AfxMessageBox("SlideText:GlobalReAlloc:Fail:1");
				return 0;
			}

			pText = (GeneStor *)GlobalLock(m_Text);
			if ( pText == NULL ) {
				AfxMessageBox("SlideText:GlobalLock:Fail:2");
				return 0;
			}

			m_TextSize += (Count - i);
			m_Expanded = (int)(Count - i);

			// Get offset of spText2
			spText2 = pText + tLoc;

			spText = pText + m_TextSize - 1;

			Count = m_TextSize - Count - Position;

		}

		// Not really the answer is it ..	
		m_EndRange = m_TextSize - 1;

		while ( Count-- ) {
			*spText-- = *spText2--;
		}
		
		Count = Amount;
		while ( Count-- ) {
			*spText-- =  tFiller;
		}


	} else {
	
		Amount = -Amount;
		m_StartRange = m_EndRange = Position;
		m_Expanded = 0;

		if ( Position >= m_TextSize ) {
			GlobalUnlock(m_Text);
			return 0;
		}

		GeneStor* pEnd = pText + m_TextSize - 1;
		pText += Position;
		// Check we at a reasonable character to move.
		char tChar = toupper ( pText->CharGene );
		if ( !(tChar >= 'A' && tChar <= 'Z') ) {
			GlobalUnlock(m_Text);
			return 0;
		}

		// Amount Loop
		GeneStor* pText2 = pText - 1;
		GeneStor *pText3 = pText;
		Count = Position;
		m_StartRange = Position;
		m_EndRange = m_TextSize - 1;
		m_Expanded = 0;

		int tAmount = Amount;

		do {
			if ( !Count ) {
				break;
			}
			char tc = toupper( (*pText2--).CharGene );
			if ( tc >= 'A' && tc <= 'Z' ) {
				++pText2;
				break;
			}
			if ( !(tc >= 'A' && tc <= 'Z') ) {
				tAmount--;
				m_StartRange = Count - 1;
			}
			Count--;
		} while ( tAmount);

		// Put pointer back to where it belongs.
		++pText2;

		if ( tAmount != Amount ) {
			while ( pText3 <= pEnd ) { 
//				char tChar = toupper ( pText3->CharGene );
//				if ( !(tChar >= 'A' && tChar <= 'Z') ) {
//					pText3++;
//				} else {
					*pText2++ = *pText3++;
//				}
			}

			while ( pText2 <= pEnd ) {
				*pText2++ =  tFiller;
			}
		}

		MoveCount = -(Amount - tAmount);
	}

	GlobalUnlock(m_Text);
	return MoveCount;
}


int 
CGeneSegment::MoveText ( DWORD Position, int Amount )
{
	int MoveCount = 0;
	DWORD Count;
	GeneStor tNext;
	GeneStor tFiller;
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	GeneStor *pText = (GeneStor *)GlobalLock(m_Text);
	if ( pText == NULL ) {
		AfxMessageBox("InsertFillerRange:GlobalLock:Fail:1");
		return 0;
	}

	if ( Amount > 0 ) {

		m_StartRange = Position;
		m_Expanded = 0;

		if ( Position >= m_TextSize ) {
			GlobalUnlock(m_Text);
			return 0;
		}
		
		GeneStor *spText = pText;
        
        MoveCount = Amount;		// Always the case for right movement

        do {
			Count = m_TextSize - Position;
			pText = spText + Position;

			// Check we at a reasonable character to move.
			// if ( (pText->CharGene == '-') || (pText->CharGene == '.') || (pText->CharGene == ' ') ) {
			char tChar = toupper ( pText->CharGene );
			if ( !(tChar >= 'A' && tChar <= 'Z') ) {

				GlobalUnlock(m_Text);
				return 0;
			}

			GeneStor tRep = tFiller;
			// Special case
			tNext = *pText;
	
			m_EndRange = Position;
	        do { 
				if ( !(--Count) ) {
					break;
				}
	
				tNext = *pText;
				*pText++ = tRep;
				tRep = tNext;
				tNext = *pText;

				m_EndRange++;
				tChar = toupper ( tNext.CharGene );
			// } while ( (tNext.CharGene != '-') && (tNext.CharGene != '.') && (tNext.CharGene != ' ') );
			} while ( (tChar >= 'A' && tChar <= 'Z') );

			if ( !Count ) {
				GlobalUnlock(m_Text);
				m_Text = GlobalReAlloc(m_Text, (m_TextSize + Amount) * sizeof(GeneStor), GMEM_MOVEABLE);
				if ( m_Text == NULL ) {
					AfxMessageBox("MoveText:GlobalReAlloc:Fail:1");
					return 0;
				}
				pText = (GeneStor *)GlobalLock(m_Text);
				if ( pText == NULL ) {
					AfxMessageBox("MoveText:GlobalLock:Fail:1");
					return 0;
				}
				pText += (m_TextSize - 1);
				*pText++ = tRep;
				*pText = tNext;
				m_TextSize += Amount;
				m_Expanded = Amount;
				Amount--;
				if ( Amount ) {

					Count = m_TextSize - Position - Amount;
					GeneStor *pText2 = pText + Amount;

					while ( Count-- ) {
						*pText2-- = *pText--;
					}
					while ( Amount ) {
						*pText2-- =  tFiller;
						Amount--;
					}

				}
			} else {
				*pText = tRep;
				Position++;
				Amount--;
			}


		} while ( Amount );

	} else {
	
		Amount = -Amount;
		m_StartRange = m_EndRange = Position;
		m_Expanded = 0;

		if ( Position >= m_TextSize ) {
			GlobalUnlock(m_Text);
			return 0;
		}

		pText += Position;
		// Check we at a reasonable character to move.
		char tChar = toupper ( pText->CharGene );
		if ( !(tChar >= 'A' && tChar <= 'Z') ) {
		// if ( (pText->CharGene == '-') || (pText->CharGene == '.') || (pText->CharGene == ' ')) {
			GlobalUnlock(m_Text);
			return 0;
		}

		// Amount Loop
		GeneStor* pText2 = pText - 1;
		Count = Position;
		m_StartRange = m_EndRange = Position;
		m_Expanded = 0;

		int tAmount = Amount;

		do {
			if ( !Count ) {
				break;
			}
			char tc = toupper( (*pText2--).CharGene );
			// if ( (tc == '-') || (tc == '.') || ( tc == ' ') ) {
			if ( !(tc >= 'A' && tc <= 'Z') ) {
				tAmount--;
				m_StartRange = Count - 1;
			}
			Count--;
		} while ( tAmount);

		// Put pointer back to where it belongs.
		++pText2;

		if ( tAmount != Amount ) {
			GeneStor *pText3 = pText2;
			while ( pText3 <= pText ) { 
				char tChar = toupper ( pText3->CharGene );
				if ( !(tChar >= 'A' && tChar <= 'Z') ) {
				// if ( (pText3->CharGene == '-') || (pText3->CharGene == '.') || (pText3->CharGene == ' ')) {
					pText3++;
				} else {
					*pText2++ = *pText3++;
				}
			}

			while ( pText2 <= pText ) {
				*pText2++ =  tFiller;
			}
		}

		MoveCount = -(Amount - tAmount);
	}

	GlobalUnlock(m_Text);
	return MoveCount;
}


int 
CGeneSegment::Create ( 
	int nStyle, 
	const char *nTitle, 
	const char *nDescr, 
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

		tStor.CharScore = 0;
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
CGeneSegment::AppendFiller( DWORD Length )
{
	DWORD Size = m_TextSize;
	GeneStor tFiller;
	
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	m_Text = GlobalReAlloc( m_Text, (Size + Length) * sizeof(GeneStor), GMEM_MOVEABLE);
	if ( m_Text == NULL) {
		AfxMessageBox("AppendFiller:GlobalReAlloc:Fail:1");
		return 0;
	}
	GeneStor * pc = (GeneStor* )GlobalLock(m_Text);
	if ( pc == NULL ) {
		AfxMessageBox("AppendFiller:GlobalLock:Fail:2");
		return 0;
	}

	pc += Size;

	m_TextSize += Length;

	while ( Length-- ) {
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
	pc->CharScore = 0;
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

void 
CGeneSegment::AlignInsertDash(DWORD Index)
{


	GeneStor tFiller;
	
	if ( GetStyle() != LINESEQUENCE ) {
		tFiller.CharGene = ' ';
		tFiller.CharDisplay = ' ';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	} else {
		tFiller.CharGene = '.';
		tFiller.CharDisplay = '.';
		tFiller.CharScore = 0;
		tFiller.GeneSeqNumber = 0L;
	}
	tFiller.TextColor = *TextColor;
	tFiller.BackColor = *BackColor;

	if ( m_AlignExtra == 0 ) {
		GlobalUnlock(m_Text);
		LockAndLoad();
	}

	if ( Index == m_TextSize ) {
		m_TextSize++;
		*(m_pMyGeneStor + Index) = tFiller;
	} else if ( Index > m_TextSize ) {

		AfxMessageBox("Align: Index Greater than Sequence Size!");
		return;

	} else {

		GeneStor *spText = m_pMyGeneStor + m_TextSize;
		GeneStor *spText2 = m_pMyGeneStor + m_TextSize - 1;

//		DWORD Count = m_TextSize - 1 - Index;
		DWORD Count = m_TextSize - Index;

		while ( Count-- ) {
			*spText-- = *spText2--;
		}
		
		*spText = tFiller;

		m_TextSize++;

	}

	m_AlignExtra--;

}

char CGeneSegment::AlignGet(DWORD Index)
{
	return m_pMyGeneStor[Index].CharGene;
}

