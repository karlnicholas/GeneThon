
#include "stdafx.h"

void
CGenedocDoc::ReScoreAll(int ScoreAll)
{
	if ( pGSFiller == NULL ) {
		return;
	}

	CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetHead();
	HANDLE tSegHandle = tCGSeg->GetTextHandle();
	GeneStor *pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
	if ( pGeneStor == NULL ) {
		AfxMessageBox("ReScoreAll:GlobalLock:Fail:1");
		return;
	}

	DWORD SegLength = tCGSeg->GetTextLength(); 

	DWORD StartRange = 0; 
	DWORD EndRange = 0;

	while ( StartRange < SegLength ) {

		if ( (pGeneStor[StartRange].CharScore > 0) && 
			( 
				( (pGeneStor[StartRange].CharScore%2) == 0 ) 
				|| ( ScoreAll ) 
			)
		) {
			GlobalUnlock( tSegHandle );
			if ( FindScore( StartRange, &StartRange, &EndRange ) ) {
				Score( &StartRange, &EndRange );
			}
			pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
			if ( pGeneStor == NULL ) {
				AfxMessageBox("ReScoreAll:GlobalLock:Fail:2");
				return;
			}
		}
		EndRange = StartRange = EndRange + 1;
	}
	
	GlobalUnlock( tSegHandle );
}

