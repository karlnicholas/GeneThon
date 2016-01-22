// CRTFFile
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRTFFile

IMPLEMENT_DYNCREATE(CRTFFile, CObject)


CRTFFile::CRTFFile()
{
	// TODO: add construction code here
}


/////////////////////////////////////////////////////////////////////////////
// CRTFFile serialization

void CRTFFile::Serialize(CArchive& ar)
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
// CRTFFile diagnostics

#ifdef _DEBUG
void CRTFFile::AssertValid() const
{
	CObject::AssertValid();
}

void CRTFFile::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// where these?
//{\rtf1\ansi\deff0
//{\fonttbl{\f0\fmodern Courier;}}
//{\colortbl
//\red0\green0\blue0;\red255\green255\blue255;\red255\green0\blue0;\red0\green255\blue0;\red0\green0\blue255;\red0\green255\blue255;\red255\green0\blue255;\red255\green255\blue0;\red128\green128\blue128;}
//\paperw11880\paperh16820\margl1000\margr500
//\margt910\margb910\sectd\cols1\pard\plain
//\fs20


//
int 
CRTFFile::RTFInit ( 
	int pictwidth, 
	int pictheight, 
	int fontpoints, 
	int fontxsize, 
	int fontysize, 
	int fontdescent, 
	int fontbold, 
	const char *outname, 
	COLORREF bgcolor, 
	COLORREF fcolor, 
	int modeflag, 
	CPtrList *pColorList
) {

TRY {
	m_fontxsize = fontxsize;
	m_fontysize = fontysize;
	m_bold = fontbold;
//	m_bgcolor = bgcolor;
//	m_fcolor = fcolor;
	m_size = 3;
	m_modeflag = modeflag;
	m_pColorList = pColorList;
	char color[256];

	m_OutFile = new CStdioFile( outname, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	m_OutFile->WriteString( "{\\rtf1\\ansi\\deff0\n" );
	m_OutFile->WriteString( "{\\fonttbl{\\f0\\fmodern Courier;}}\n" );
	m_OutFile->WriteString( "{\\colortbl\n" );

	m_OutFile->WriteString( "}\n" );
	m_OutFile->WriteString( "\\paperw11880\\paperh16820\\margl1000\\margr500\n" );
	m_OutFile->WriteString( "\\margt910\\margb910\\sectd\\cols1\\pard\\plain\n" );

	_snprintf( color, 255, "\\fs%d\n", fontpoints * 2 );
	color[255] = 0;
	m_OutFile->WriteString( color );
	if ( fontbold ) {
		m_OutFile->WriteString( "\\b\n" );
	} else {
		m_OutFile->WriteString( "\\b0\n" );
	}


	m_bgcolor = -1;
	m_fcolor = -1;

} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
	return 0;
}
END_CATCH

return 1;
}


void
CRTFFile::StartLine()
{
}

void
CRTFFile::EndLine()
{
TRY {
	m_OutFile->WriteString( "\\line\n" );
	m_bgcolor = -1;
	m_fcolor = -1;
} 
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void CRTFFile::CharOut( char c, COLORREF ForeGround, COLORREF BackGround )
{
TRY {

	char obuff[256];

	if ( ForeGround != m_fcolor || BackGround != m_bgcolor) {
		m_fcolor = ForeGround;
		m_bgcolor = BackGround;
	}

	_snprintf( obuff, 256, "%c", c );
	m_OutFile->WriteString( obuff );
}
CATCH (CFileException, e ) {
	AfxMessageBox( "File Error" );
}
END_CATCH
}

void CRTFFile::StartBlock()
{
}

void CRTFFile::EndBlock()
{
}

void
CRTFFile::LineMiddle()
{
}

void
CRTFFile::LineBottom()
{
}

void
CRTFFile::LineLeft()
{
}

void
CRTFFile::LineRight()
{
}


void
CRTFFile::Exit()
{
	m_OutFile->WriteString( "}\n" );


	m_OutFile->Close();
	delete m_OutFile;
	
	return;
}
