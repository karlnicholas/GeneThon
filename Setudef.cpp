
#include "stdafx.h"

static char szUDSection[] = "User Defaults";

static char szFONTWEIGHT[] = "Font Weight";
static char szFONTSIZE[] = "Font Size";

static char szFOREBASE[] = "Fore Base";
static char szBACKBASE[] = "Back Base";

static char szLEFTBORD[] = "Left Bord";
static char szRIGHTBORD[] = "Right Bord";
static char szTOPBORD[] = "Top Bord";
static char szBOTTOMBORD[] = "Bottom Bord";

static char szPRINTSTRING[] = "PString";
static char szPRINTSTRINGFLAG[] = "PStringF";
static char szPRINTPAGENUMBER[] = "PPageNum";
static char szPRINTPAGEOFFSET[] = "PPageOff";
static char szPRINTFONTWEIGHT[] = "PFontW";
static char szPRINTFONTSIZE[] = "PFontS";
static char szPRINTGENEBLOCK[] = "PGeneB";
static char szPRINTFONTNAME[] = "PFontN";


static char szWIDTHMODE[] = "Width Mode";
static char szFIXEDX[] = "Fixed X";
static char szSHOWTAIL[] = "Seq Indicator";
static char szORIENTATION[] = "Orient";
static char szGAPIND[] = "Gap Ind";

static char szCONSENSUS[] = "Consensus";
static char szPICTWIDTH[] = "Pict Width";
static char szPICTHEIGHT[] = "Pict Height";
static char szPICTASCENT[] = "Pict Ascent";

static char szMarkerSymb[] = "MarkerSymb";		// *  symbol, 
static char szMarkerSpacing[] = "MarkerSpacing";	// 10  spacing between symbols, 
static char szMarkerReplace[] = "MarkerReplace";	// 2  how often to replace a symbol with a number, 
static char szMarkerStart[] = "MarkerStart";		// -13  the number to be assigned to the first column of the alignment,
static char szMarkerEnable[] = "MarkerEnable";		// is it enabled?

static char szConservedGap[] = "ConservedGap";		// *  symbol, 

static char szResidueUpper[] = "ResidueUpper";		// 

static char szStrLead[] = "String Lead";		// 
static char szStrTail[] = "String Tail";		// 
static char szMaxNameLength[] = "Max Name Length";		// 

static char szPRINTSHADE[] = "Print Shade";
static char szSUMCOLINCH[] = "Sum Col Inch";
static char szSUM2WID[] = "Sum2Wid";
static char szSUMDEFDIS[] = "SumDefDis";
static char szSUMTEXTBLACK[] = "SumTextBlack";

static char szPRINTFILENAME[] = "PrintFileName";
static char szPRINTDATE[] = "PrintDate";
static char szTRANSTILDE[] = "TransTilde";
static char szSHOWMANSHADE[] = "ShowManShade";
static char szSHOWCOMMENTS[] = "ShowComments";

static char szMakeBackups[] = "MakeBackups";
static char szLocAfterName[] = "LocAfterName";
static char szLocAfterSeq[] = "LocAfterSeq";

void
CGenethonDoc::GetIniDisplayVars(CDisplayVars *DisplayVars)
{
	// Start Of Display Vars....
	CString strBuffer;
	char DecodeBuff[256];
	int i;

	DisplayVars->SetTitleColors ( RGB ( 0,0,0), RGB ( 255,255,255) );

}


void
DecodeColor( const char *tStr, COLORREF *tRef )
{
	char DecodeBuff[20];
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Red = atoi( DecodeBuff );
	tStr += 3;
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Green = atoi( DecodeBuff );
	tStr += 3;
	memcpy ( DecodeBuff, tStr, 3 );
	DecodeBuff[3] = 0;
	int Blue = atoi( DecodeBuff );
	*tRef = RGB ( Red, Green, Blue );
}

void
CGenethonDoc::GetIniDefaults()
{

	// Start User Vars default init
	CString strBuffer;
	char DecodeBuff[256];
	int i;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFONTWEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FontWeight = FW_NORMAL;
	else 
		m_UserVars.m_FontWeight = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFONTSIZE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FontSize = 12;
	else 
		m_UserVars.m_FontSize = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBACKBASE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BackColor = RGB ( 255,255,255 );
	else {
		DecodeColor( strBuffer, &m_UserVars.m_BackColor );
	}
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szTOPBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_TopBorder = 1.0;
	else
		m_UserVars.m_TopBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szBOTTOMBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_BottomBorder = 1.0;
	else
		m_UserVars.m_BottomBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szRIGHTBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_RightBorder = 1.25;
	else
		m_UserVars.m_RightBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szLEFTBORD);
	if (strBuffer.IsEmpty())
		m_UserVars.m_LeftBorder = 1.25;
	else
		m_UserVars.m_LeftBorder = atof(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSTRING);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintString = "";
	else 
		m_UserVars.m_PrintString = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSHADE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintShading = 0;
	else 
		m_UserVars.m_PrintShading = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTSTRINGFLAG);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintStringFlag = 0;
	else 
		m_UserVars.m_PrintStringFlag = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTPAGENUMBER);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintPageNumber = 3;
	else 
		m_UserVars.m_PrintPageNumber = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTPAGEOFFSET);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintPageOffset = 0;
	else 
		m_UserVars.m_PrintPageOffset = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTWEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontWeight = FW_NORMAL;
	else 
		m_UserVars.m_PrintFontWeight = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTSIZE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontSize = 12;
	else 
		m_UserVars.m_PrintFontSize = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTGENEBLOCK);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintGeneBlock = 0;
	else 
		m_UserVars.m_PrintGeneBlock = atoi( strBuffer );

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFONTNAME);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFontName = "Times New Roman";
	else 
		m_UserVars.m_PrintFontName = strBuffer;


	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szWIDTHMODE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_WidthMode = 0;
	else
		m_UserVars.m_WidthMode = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szFIXEDX);
	if (strBuffer.IsEmpty())
		m_UserVars.m_FixedXSize = 50;
	else
		m_UserVars.m_FixedXSize = atoi(strBuffer);
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szCONSENSUS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ConsensusLine = 1;
	else
		m_UserVars.m_ConsensusLine = atoi(strBuffer);
	
	// Default to show tail.
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWTAIL);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowTail = 1;
	else
		m_UserVars.m_ShowTail = atoi(strBuffer);

	// Default to portrait
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szORIENTATION);
	if (strBuffer.IsEmpty())
		m_UserVars.m_Orientation = 0;
	else
		m_UserVars.m_Orientation = atoi(strBuffer);

	// Default to '-'
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szGAPIND);
	if (strBuffer.IsEmpty())
		m_UserVars.m_GapInd = 0;
	else
		m_UserVars.m_GapInd = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTWIDTH);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictWidth = 0;
	else
		m_UserVars.m_PictWidth = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTHEIGHT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictHeight = 0;
	else
		m_UserVars.m_PictHeight = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPICTASCENT);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PictAscent = 0;
	else
		m_UserVars.m_PictAscent = atoi(strBuffer);

	// Set default no project type.
	m_UserVars.m_ProjectType = 0;
	
	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerSymb);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerSymb = '*';		// *  symbol, 
	else 
		m_UserVars.m_MarkerSymb = strBuffer[0];

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerSpacing);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerSpacing = 10;	// 10  spacing between symbols, 
	else 
		m_UserVars.m_MarkerSpacing = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerReplace);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerReplace = 2;	// 2  how often to replace a symbol with a number, 
	else 
		m_UserVars.m_MarkerReplace = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerStart);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerStart = 1;		// -13  the number to be assigned to the first column of the alignment,
	else 
		m_UserVars.m_MarkerStart = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMarkerEnable);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MarkerEnable = 1;		// is it enabled?
	else 
		m_UserVars.m_MarkerEnable = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szConservedGap);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ConservedGap = ' ';
	else 
		m_UserVars.m_ConservedGap = strBuffer[0];

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szResidueUpper);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ResidueUpper = 0;
	else 
		m_UserVars.m_ResidueUpper = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szStrLead);
	if (strBuffer.IsEmpty())
		m_UserVars.m_strLead = " : ";
	else
		m_UserVars.m_strLead = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szStrTail);
	if (strBuffer.IsEmpty())
		m_UserVars.m_strTail = " : ";
	else
		m_UserVars.m_strTail = strBuffer;

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szMaxNameLength);
	if (strBuffer.IsEmpty())
		m_UserVars.m_MaxNameLength = 10;
	else 
		m_UserVars.m_MaxNameLength = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMCOLINCH);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumColInch = 24;
	else
		m_UserVars.m_SumColInch = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUM2WID);
	if (strBuffer.IsEmpty())
		m_UserVars.m_Sum2Wid = 0;
	else
		m_UserVars.m_Sum2Wid = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMDEFDIS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumDefDis = 0;
	else
		m_UserVars.m_SumDefDis = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSUMTEXTBLACK);
	if (strBuffer.IsEmpty())
		m_UserVars.m_SumTextBlack = 0;
	else
		m_UserVars.m_SumTextBlack = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTFILENAME);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintFileName = 0;
	else
		m_UserVars.m_PrintFileName = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szPRINTDATE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_PrintDate = 0;
	else
		m_UserVars.m_PrintDate = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szTRANSTILDE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_TransTilde = 0;
	else
		m_UserVars.m_TransTilde = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWMANSHADE);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowManShade = 1;
	else
		m_UserVars.m_ShowManShade = atoi(strBuffer);

	strBuffer = AfxGetApp()->GetProfileString(szUDSection, szSHOWCOMMENTS);
	if (strBuffer.IsEmpty())
		m_UserVars.m_ShowComments = 1;
	else
		m_UserVars.m_ShowComments = atoi(strBuffer);

	// Search .
	m_UserVars.m_MakeBackups = AfxGetApp()->GetProfileInt(szUDSection, szMakeBackups, (int)TRUE );
	m_UserVars.m_LocAfterName = AfxGetApp()->GetProfileInt(szUDSection, szLocAfterName, (int)FALSE );
	m_UserVars.m_LocAfterSeq = AfxGetApp()->GetProfileInt(szUDSection, szLocAfterSeq, (int)TRUE );


	// Group Conserved Level
	// Init these empty.
//	m_UserVars.m_TitleProgram[0] = 0;
//	m_UserVars.m_TitleScoreMatrix[0] = 0;
//	m_UserVars.m_TitleOpenGap[0] = 0;
//	m_UserVars.m_TitleExtendGap[0] = 0;


	// Init Base DisplayVars	
	GetIniDisplayVars( &m_UserVars.m_Vars );

}

void
CGenethonDoc::SetIniDefaults()
{

	TCHAR szBuffer[256];
	int i;

	sprintf( szBuffer, "%d", m_UserVars.m_FontWeight );
	AfxGetApp()->WriteProfileString(szUDSection, szFONTWEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_FontSize );
	AfxGetApp()->WriteProfileString(szUDSection, szFONTSIZE, szBuffer);

	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_BackColor), 
		GetGValue(m_UserVars.m_BackColor), 
		GetBValue(m_UserVars.m_BackColor) 
	);
	AfxGetApp()->WriteProfileString(szUDSection, szBACKBASE, szBuffer);


	sprintf( szBuffer, "%03d%03d%03d", 
		GetRValue(m_UserVars.m_ForeColor),
		GetGValue(m_UserVars.m_ForeColor),
		GetBValue(m_UserVars.m_ForeColor)
	);
	AfxGetApp()->WriteProfileString(szUDSection, szFOREBASE, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_TopBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szTOPBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_BottomBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szBOTTOMBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_RightBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szRIGHTBORD, szBuffer);

	sprintf( szBuffer, "%f", m_UserVars.m_LeftBorder );
	AfxGetApp()->WriteProfileString(szUDSection, szLEFTBORD, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintString );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSTRING, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintShading );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSHADE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintStringFlag );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTSTRINGFLAG, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintPageNumber );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTPAGENUMBER, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintPageOffset );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTPAGEOFFSET, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFontWeight );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTWEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFontSize );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTSIZE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintGeneBlock );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTGENEBLOCK, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_PrintFontName );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFONTNAME, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_WidthMode );
	AfxGetApp()->WriteProfileString(szUDSection, szWIDTHMODE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_FixedXSize );
	AfxGetApp()->WriteProfileString(szUDSection, szFIXEDX, szBuffer);
	
	sprintf( szBuffer, "%d", m_UserVars.m_ConsensusLine);
	AfxGetApp()->WriteProfileString(szUDSection, szCONSENSUS, szBuffer);
	
	sprintf( szBuffer, "%d", m_UserVars.m_ShowTail);
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWTAIL, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_Orientation);
	AfxGetApp()->WriteProfileString(szUDSection, szORIENTATION, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_GapInd);
	AfxGetApp()->WriteProfileString(szUDSection, szGAPIND, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictWidth );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTWIDTH, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictHeight );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTHEIGHT, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PictAscent );
	AfxGetApp()->WriteProfileString(szUDSection, szPICTASCENT, szBuffer);

	sprintf( szBuffer, "%c", m_UserVars.m_MarkerSymb );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerSymb, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerSpacing );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerSpacing, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerReplace );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerReplace, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerStart );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerStart, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MarkerEnable );
	AfxGetApp()->WriteProfileString(szUDSection, szMarkerEnable, szBuffer);

	sprintf( szBuffer, "%c", m_UserVars.m_ConservedGap );
	AfxGetApp()->WriteProfileString(szUDSection, szConservedGap, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ResidueUpper );
	AfxGetApp()->WriteProfileString(szUDSection, szResidueUpper, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_MaxNameLength );
	AfxGetApp()->WriteProfileString(szUDSection, szMaxNameLength, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_strLead );
	AfxGetApp()->WriteProfileString(szUDSection, szStrLead, szBuffer);

	sprintf( szBuffer, "%s", m_UserVars.m_strTail );
	AfxGetApp()->WriteProfileString(szUDSection, szStrTail, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintFileName );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTFILENAME, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_PrintDate );
	AfxGetApp()->WriteProfileString(szUDSection, szPRINTDATE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_TransTilde );
	AfxGetApp()->WriteProfileString(szUDSection, szTRANSTILDE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ShowManShade );
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWMANSHADE, szBuffer);

	sprintf( szBuffer, "%d", m_UserVars.m_ShowComments );
	AfxGetApp()->WriteProfileString(szUDSection, szSHOWCOMMENTS, szBuffer);

	szBuffer[0] = '\0';


//	
	
	// End User Vars default init
}

