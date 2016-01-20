
#include "stdafx.h"


int 
CGenethonDoc::PairWiseScore( DWORD *nStartRange, DWORD *nEndRange, 
unsigned long *Score, int RowCount, ShadeSegStc *pSegArr )
{

	DWORD StartRange = *nStartRange;
	DWORD EndRange = *nEndRange;
	DWORD tCount;
	char tGapChar;
	int rScore;
	GeneStor tGStor;

	if ( m_UserVars.m_GapInd == 0 ) {
		tGapChar = '-';
	} else {
		tGapChar = '.';
	}
	
	*Score = 0;

//	long NewGap = -1;
//	long GapLen = -1;
// Now held in genedoc.h

	int OpenGp = 0, TopGap = 0;

	for ( int n = 2; n < RowCount - 1; ++n ) {		// Loop A
	
		for ( int m = n + 1; m < RowCount; ++m ) {	// Loop B
		
			tCount = StartRange; 
			while ( tCount <= EndRange ) {

				tGStor = (pSegArr[m].pGeneStor)[tCount];	// Indexed from Loop B
				char Nuc1 = toupper(tGStor.CharGene);
				tGStor = (pSegArr[n].pGeneStor)[tCount];	// Indexed from Loop A
				char Nuc2 = toupper(tGStor.CharGene);

				int gc1 = !(Nuc1 >= 'A' && Nuc1 <= 'Z');
				int gc2 = !(Nuc2 >= 'A' && Nuc2 <= 'Z');

				if ( !gc1 && !gc2 ) {
					rScore = ScoreCurrentArray(Nuc1, Nuc2 );
					if ( rScore == INT_MIN ) {
						AfxMessageBox ( "Invalid Char in Score Range" );
						return 0;
					}
					*Score += rScore;
					OpenGp = 0;
				} else if ( gc1 && !gc2 ) {
					*Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						*Score += NewGap;
						TopGap = 1;
					} else {
						if ( !TopGap ) {
							*Score += NewGap;
							TopGap = 1;
						}
					}
				} else if ( !gc1 && gc2 ) {
					*Score += GapLen;
					if ( !OpenGp ) {
						OpenGp = 1;
						*Score += NewGap;
						TopGap = 0;
					} else {
						if ( TopGap ) {
							*Score += NewGap;
							TopGap = 0;
						}
					}
				}
				tCount = tCount + 1L;
			}
		}
	}

	return 1;
}
