
#include "stdafx.h"

#define GENEDOCIDSTR	"GENEDOC:" 

#define GDFONTWEIGHT	"Font Weight:"
#define GDFONTSIZE		"Font Size:"

#define GDFOREBASE		"Fore Base:"
#define GDBACKBASE		"Back Base:"

#define GDLEFTBORD		"Left Bord:"
#define GDRIGHTBORD		"Right Bord:"
#define GDTOPBORD		"Top Bord:"
#define GDBOTTOMBORD	"Bottom Bord:"

#define GDPRINTSTRING "PString:"
#define GDPRINTSTRINGFLAG "PStringF:"
#define GDPRINTPAGENUMBER "PPageNum:"
#define GDPRINTPAGEOFFSET "PPageOff:"
#define GDPRINTFONTWEIGHT "PFontW:"
#define GDPRINTFONTSIZE "PFontS:"
#define GDPRINTFONTNAME "PFontN:"
#define GDPRINTGENEBLOCK "PGeneB:"

#define GDWIDTHMODE		"Width Mode:"
#define GDFIXEDX		"Fixed X:"

#define GDSHOWTAIL		"Seq Indicator:"
#define GDORIENTATION	"Orient:"

#define GDCONSENSUS		"Consensus:"		// m_ConsensusLine;

#define GDPICTWIDTH		"Pct Wdth:"
#define GDPICTHEIGHT	"Pct Hght:"
#define GDPICTASCENT	"Pct Asct:"


const char *
CGenethonDoc::GDUFindString(const CString& FindString)
{
	int FindLoc;
	const char * rStr;

	POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while (tPos != NULL) {
		CString *tStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
		if (tStr->Find(GENEDOCIDSTR) == -1) continue;
		if ((FindLoc = tStr->Find(FindString)) != -1) {
			rStr = (const char *)*tStr;
			rStr += FindLoc + FindString.GetLength();
			return rStr;
		}
	}

	return NULL;
}


void
CGenethonDoc::GetUserDefaults( )
{

	const char * tStr;
	char DecodeBuff[256];

	int NewHeader = 0;
	POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while ( tPos != NULL ) {
		CString *tStr = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
		if ( tStr->Find ( GENEDOCIDSTR ) != -1 ) break;
		if ( tStr->Find ( "GDC " ) != -1 ) {
			NewHeader = 1;
			break;
		}
	}

	if ( NewHeader ) {
		GetNewUserDefaults();
		return;
	}

	SetModifiedFlag();

	tStr = GDUFindString ( GDFONTWEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FontWeight = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDFONTSIZE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FontSize = atoi( DecodeBuff );
	}


	tStr = GDUFindString ( GDFOREBASE );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_ForeColor = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDBACKBASE );
	if ( tStr != NULL ) {
		int Red, Green, Blue;
		tStr++;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Red = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Green = atoi( DecodeBuff );
		tStr += 3;
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		Blue = atoi( DecodeBuff );
		m_UserVars.m_BackColor = RGB ( Red, Green, Blue );
	}

	tStr = GDUFindString ( GDLEFTBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_LeftBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDRIGHTBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_RightBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDTOPBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_TopBorder = atof( DecodeBuff );
	}

	tStr = GDUFindString ( GDBOTTOMBORD );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 10 );
		DecodeBuff[10] = 0;
		m_UserVars.m_BottomBorder = atof( DecodeBuff );
	}


	tStr = GDUFindString ( GDPRINTSTRING );
	if ( tStr != NULL ) {
		tStr++;
		m_UserVars.m_PrintString = tStr;
	}

	tStr = GDUFindString ( GDPRINTSTRINGFLAG );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintStringFlag = atoi( DecodeBuff );
		if ( m_UserVars.m_PrintStringFlag > 2 ) m_UserVars.m_PrintStringFlag = 0;
	}

	tStr = GDUFindString ( GDPRINTPAGENUMBER );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintPageNumber = atoi( DecodeBuff );
		if ( m_UserVars.m_PrintPageNumber > 4 ) m_UserVars.m_PrintPageNumber = 0;
	}

	tStr = GDUFindString ( GDPRINTPAGEOFFSET );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 5 );
		DecodeBuff[5] = 0;
		m_UserVars.m_PrintPageOffset = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTWEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_PrintFontWeight = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTSIZE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_PrintFontSize = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTGENEBLOCK );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_PrintGeneBlock = atoi( DecodeBuff );
	}

	tStr = GDUFindString ( GDPRINTFONTNAME );
	if ( tStr != NULL ) {
		tStr++;
		m_UserVars.m_PrintFontName = tStr;
	}


	tStr = GDUFindString ( GDWIDTHMODE );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_WidthMode = atoi( DecodeBuff );
		if ( m_UserVars.m_WidthMode != 0 ) m_UserVars.m_WidthMode = 1;
	}

	tStr = GDUFindString ( GDFIXEDX );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 6 );
		DecodeBuff[6] = 0;
		m_UserVars.m_FixedXSize = atoi( DecodeBuff );
		if ( m_UserVars.m_FixedXSize > 999 ) m_UserVars.m_FixedXSize = 999;
	}

	tStr = GDUFindString ( GDCONSENSUS );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ConsensusLine = atoi( DecodeBuff );
		if ( m_UserVars.m_ConsensusLine > 2 ) m_UserVars.m_ConsensusLine = 2;
	}

	tStr = GDUFindString ( GDSHOWTAIL );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_ShowTail = atoi( DecodeBuff );
		if ( m_UserVars.m_ShowTail != 0 ) m_UserVars.m_ShowTail = 1;
	}

	tStr = GDUFindString ( GDORIENTATION );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 2 );
		DecodeBuff[2] = 0;
		m_UserVars.m_Orientation = atoi( DecodeBuff );
		if ( m_UserVars.m_Orientation != 0 ) m_UserVars.m_Orientation = 1;
	}

	tStr = GDUFindString ( GDPICTWIDTH );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictWidth = atoi( DecodeBuff );
		if ( m_UserVars.m_PictWidth < -9 || m_UserVars.m_PictWidth > 9 ) m_UserVars.m_PictWidth = 0;
	}

	tStr = GDUFindString ( GDPICTHEIGHT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictHeight = atoi( DecodeBuff );
		if ( m_UserVars.m_PictHeight < -9 || m_UserVars.m_PictHeight > 9 ) m_UserVars.m_PictHeight = 0;
	}

	tStr = GDUFindString ( GDPICTASCENT );
	if ( tStr != NULL ) {
		memcpy ( DecodeBuff, tStr, 3 );
		DecodeBuff[3] = 0;
		m_UserVars.m_PictAscent = atoi( DecodeBuff );
		if ( m_UserVars.m_PictAscent < -9 || m_UserVars.m_PictAscent > 9 ) m_UserVars.m_PictAscent = 0;
	}



}

