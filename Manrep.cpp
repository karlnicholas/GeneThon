
#include "stdafx.h"


int
CGenethonDoc::WriteManRepFile( 
	const char *FileName
) {

	int rc = 1;
TRY {
	char LeadBuff[512];

	
	POSITION tPos;
	
	CStdioFile wFile ( FileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );


	char tGapChar = m_UserVars.m_GapInd ? '.' : '-';
	
	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		CString GroupName = "";
		// tCGSeg;
		if ( tCGSeg->m_DisplayGroup != 0 ) {
			CDisplayVars *DisplayVars = NULL;
			int GrpNum = 0;
			POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
			while ( tPos != NULL ) {
				DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
				GrpNum++;
				if ( GrpNum == tCGSeg->m_DisplayGroup ) break;
			}
			if ( DisplayVars != NULL ) {
				GroupName = DisplayVars->GetGroupName();
			}
		}

		sprintf( LeadBuff, "%s %s\n", tCGSeg->GetTitle(), GroupName );
		wFile.WriteString( LeadBuff );

		const CMapDWORDToCPAIR& mapCPAIR = tCGSeg->GetMapCPAIR();
		CPAIR tPair;
		DWORD dwPos;
		POSITION tPos = mapCPAIR.GetStartPosition();
		while ( tPos != NULL ) {
			mapCPAIR.GetNextAssoc(tPos, dwPos, tPair);
			sprintf( LeadBuff, "    %ld %06x %06x\n", dwPos, tPair.rgbText, tPair.rgbBack );
			wFile.WriteString( LeadBuff );
		}
		wFile.WriteString( "\n" );
	}
	
	// only sequences now ..
	
	

	wFile.Close();

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

