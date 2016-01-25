
#include "stdafx.h"

void
CGenethonDoc::GetIniDisplayVars(CDisplayVars *DisplayVars)
{
	// Start Of Display Vars....
	CString strBuffer;
	char DecodeBuff[256];
	int i;

	DisplayVars->SetTitleColors(RGB(0, 0, 0), RGB(255, 255, 255));

	int PropLevelCount = 0;
	int TopCount = 1;
	// CPtrArray

}


void
CGenethonDoc::GetIniDefaults()
{

	// Start User Vars default init
	CString strBuffer;
	int i;

	m_UserVars.m_FontWeight = FW_NORMAL;

	m_UserVars.m_FontSize = 12;

	m_UserVars.m_ForeColor = RGB(0, 0, 0);

	m_UserVars.m_BackColor = RGB ( 255,255,255 );
	
	m_UserVars.m_TopBorder = 1.0;

	m_UserVars.m_BottomBorder = 1.0;
	
	m_UserVars.m_RightBorder = 1.25;

	m_UserVars.m_LeftBorder = 1.25;
	
	m_UserVars.m_PrintString = "";

	m_UserVars.m_PrintShading = 0;

	m_UserVars.m_PrintStringFlag = 0;

	m_UserVars.m_PrintPageNumber = 3;

	m_UserVars.m_PrintPageOffset = 0;

	m_UserVars.m_PrintFontWeight = FW_NORMAL;

	m_UserVars.m_PrintFontSize = 12;

	m_UserVars.m_PrintGeneBlock = 0;

	m_UserVars.m_PrintFontName = "Times New Roman";

	m_UserVars.m_WidthMode = 0;

	m_UserVars.m_FixedXSize = 50;
	
	m_UserVars.m_ConsensusLine = 1;

	m_UserVars.m_ShowTail = 1;

	m_UserVars.m_Orientation = 0;

	m_UserVars.m_PictWidth = 0;

	m_UserVars.m_PictHeight = 0;

	m_UserVars.m_PictAscent = 0;

	// Set default no project type.
	m_UserVars.m_ProjectType = 0;

	m_UserVars.m_strLead = " : ";

	m_UserVars.m_strTail = " : ";

	m_UserVars.m_MaxNameLength = 10;

	m_UserVars.m_SumColInch = 24;

	m_UserVars.m_Sum2Wid = 0;

	m_UserVars.m_SumDefDis = 0;

	m_UserVars.m_SumTextBlack = 0;

	m_UserVars.m_PrintFileName = 0;

	m_UserVars.m_PrintDate = 0;

	// Search .
	m_UserVars.m_MakeBackups = 1;
	m_UserVars.m_LocAfterName = 0;
	m_UserVars.m_LocAfterSeq = 1;


	// Group Conserved Level
	// Init these empty.
//	m_UserVars.m_TitleProgram[0] = 0;
//	m_UserVars.m_TitleScoreMatrix[0] = 0;
//	m_UserVars.m_TitleOpenGap[0] = 0;
//	m_UserVars.m_TitleExtendGap[0] = 0;


	// Init Base DisplayVars	
	GetIniDisplayVars( &m_UserVars.m_Vars );

}

