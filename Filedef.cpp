
#include "stdafx.h"


UserVars sUserVars;
DisplayVars sDisplayVars;
UserVars iUserVars;

BOOL UseGSFiller;

CGenethonDoc *gpDoc;

void 
CGenethonDoc::GetNewUserDefaults( )
{

	CString strDef;
	CString *tStr;

	// Need this to get init vars ..
	CopyUserVars( &sUserVars, &m_UserVars );
	// But clear the lists out 
	ClearUserVars( &sUserVars );
	
	// Restore Old Storage..
	sUserVars.m_Vars.CopyDisplayVars( &sDisplayVars, &sUserVars.m_Vars, this );
	// Remove Old Storage ..
	ClearUserVars( &m_UserVars );
	CopyUserVars( &m_UserVars, &sUserVars);

	ClearUserVars( &sUserVars );

//	AutoShade(-1);
}

/*
//CStdioFile wFile;
//#define WBUG(ostr) wFile.Open( "debug.txt", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeText );\
//wFile.SeekToEnd(); \
//wFile.WriteString( ostr );\
//wFile.Close();
*/
#define WBUG(ostr)

void 
CGenethonDoc::SetUserDefaults( )
{

	gpDoc = this;

	CopyUserVars( &sUserVars, &m_UserVars );

	// Some silly stuff to get access to private variables ...
	m_UserVars.m_Vars.CopyDisplayVars ( &sDisplayVars, &m_UserVars.m_Vars, this );

	POSITION tPos = m_UserVars.m_DisplayVars.GetHeadPosition();
	
	while ( tPos != NULL ) {

		CDisplayVars *DisplayVars = (CDisplayVars *)m_UserVars.m_DisplayVars.GetNext(tPos);
		DisplayVars->CopyDisplayVars ( &sDisplayVars, DisplayVars, this );
	
	}


	// Remove Storage ..
	ClearUserVars( &sUserVars );


}


