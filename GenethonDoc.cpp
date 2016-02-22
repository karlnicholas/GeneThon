// geneddoc.cpp : implementation of the CGenethonDoc class
//

#include "stdafx.h"
#include <vector>
#include <Python.h>
#include <frameobject.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenethonDoc

IMPLEMENT_DYNCREATE(CGenethonDoc, CDocument)

BEGIN_MESSAGE_MAP(CGenethonDoc, CDocument)
	//{{AFX_MSG_MAP(CGenethonDoc)
	ON_COMMAND(IDM_CONFIGURE, OnConfigure)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(IDM_GENEVIEW, OnGeneview)
	ON_COMMAND(IDM_FILEEXPORT, OnFileexport)
	ON_COMMAND(IDM_SUMMARYVIEW, OnSummaryview)
	ON_UPDATE_COMMAND_UI(IDM_SUMMARYVIEW, OnUpdateSummaryview)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(IDM_GENEREPORTVIEW, OnGenereportview)
	//}}AFX_MSG_MAP
	ON_COMMAND(IDM_PLAYPYTHON, &CGenethonDoc::OnPlaypython)
END_MESSAGE_MAP()


CGenethonDoc::CGenethonDoc()
{
	int i;
	// TODO: add one-time construction code here
	pGSFiller = NULL;
	m_pTextView = NULL;
	m_pSummaryView = NULL;

	m_SummaryMessaged = 0;
	
	// Add the Base DisplayVars entry ..
	// CDisplayVars *DisplayVars = new CDisplayVars;
	// m_UserVars.m_DisplayVars.AddTail( DisplayVars );

	// Load User Defaults
	GetIniDefaults();

	((CGenethonApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );

	Py_Initialize();
}

CGenethonDoc::~CGenethonDoc()
{
	if ( pGSFiller != NULL ) {
		delete pGSFiller;
	}

	ClearUserVars( &m_UserVars );

	Py_Finalize();
}


CString CGenethonDoc::ConvertPathname( const char *nExt )
{
	char *pName;
   	CString PathName = GetPathName();

	int NameLen = PathName.GetLength();

	pName = PathName.GetBuffer(NameLen);

	int tLen = NameLen - 1;
	int i;
	for ( i = 0; i < 4; ++i ) {
		if ( pName[tLen] == '.' ) {
			break;
		}
		tLen--;
	}

	if ( pName[tLen] == '.' ) {
		i = 0;
		while ( (tLen < NameLen) && (i < 4) ) {
			pName[tLen] = nExt[i];
			i++;
			tLen++;
		}
		PathName.ReleaseBuffer();
	} else {
		PathName.ReleaseBuffer();
		PathName += nExt;
	}
	
	return PathName;
}


void
CGenethonDoc::CheckOrientation()
{
	int nLS = ((CGenethonApp *)AfxGetApp())->GetLandscape();
	if ( nLS != m_UserVars.m_Orientation ) {
		m_UserVars.m_Orientation = nLS;
		SetModifiedFlag();
	}
}

void
CGenethonDoc::SetFilePath(const char *pszPathName)
{
   	m_PathName = pszPathName;

	int NameLen = m_PathName.GetLength();

	char *pName = m_PathName.GetBuffer(NameLen);

	while ( NameLen != -1 ) {
		if ( pName[NameLen] == '\\' ) break;
		if ( pName[NameLen] == ':' ) break;
		
		NameLen -= 1;
	}
	
	NameLen++;

	m_PathName.ReleaseBuffer(NameLen);

}

void
CGenethonDoc::GetProjectType()
{

	int tType = 0, rc;

	if (pGSFiller != NULL) {
		if (!pGSFiller->SegHeaderList.IsEmpty()) {

			CString *cStr = (CString *)pGSFiller->SegHeaderList.GetTail();
			// Looking for Master Checksum location ...

			if ((rc = cStr->Find("Type: ")) != -1) {
				const char *rStr = (const char *)*cStr;
				rStr += rc + strlen("Type: ");
				if (*rStr == 'N') {
					tType = 1;
				}
			}
		}
	}


	m_UserVars.m_ProjectType = tType + 1;
}

BOOL
CGenethonDoc::OnOpenDocument(const char *pszPathName)
{
	if (IsModified())
		TRACE0("Warning: OnOpenDocument replaces an unsaved document\n");


	BeginWaitCursor();

	DeleteContents();

	if ( pGSFiller != NULL ) {
		delete pGSFiller;
		pGSFiller = NULL;
	}
	
	if ( !GetMSFFile( pszPathName ) ) {
		EndWaitCursor();
		return FALSE;
	}
	
	// Save the File Path
	
	SetFilePath(pszPathName);

	// user defaults 
	GetNewUserDefaults( );

	// Set printer orientation for this file.
	((CGenethonApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );
		
	SetModifiedFlag(FALSE);     // start off with unmodified

	EndWaitCursor();


	return TRUE;
}


void CGenethonDoc::OnFileSave() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) {
		AfxMessageBox("Empty Project: Cannot Save!");
		return;
	}
	
	CDocument::OnFileSave();
}

void CGenethonDoc::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) {
		AfxMessageBox("Empty Project: Cannot Save!");
		return;
	}

	CDocument::OnFileSaveAs();
}


BOOL 
CGenethonDoc::OnSaveDocument(const char *pszPathName)
{

	// Get printer orientation for this file.
	m_UserVars.m_Orientation = ((CGenethonApp *)AfxGetApp())->GetLandscape();

	BeginWaitCursor();

	// Write new user defaults to the comment list
	SetUserDefaults();

	WriteMSFFile( pszPathName );
	
	EndWaitCursor();
	SetModifiedFlag(FALSE);     // start off with unmodified

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CGenethonDoc serialization

void CGenethonDoc::Serialize(CArchive& ar)
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
// CGenethonDoc diagnostics

#ifdef _DEBUG
void CGenethonDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGenethonDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGenethonDoc commands

// Working Spot

void
CGenethonDoc::CopyGSFiller( CGSFiller *npGSFiller )
{
	pGSFiller = npGSFiller;

	SetModifiedFlag();     // start off with unmodified

	UpdateAllViews(NULL);
}

void 
CGenethonDoc::ClearShade() 
{
	if ( pGSFiller == NULL ) {
		return;
	}

	CGeneSegment *tCGSeg;
	int i = 0;
	HANDLE tSegHandle;

	int RowCount = pGSFiller->SegDataList.GetCount();	// Subtract 1 for comment rows
	
	ShadeSegStc* pSegArr = new ShadeSegStc[RowCount];	// Gonna need access to comment row

	if ( pSegArr == 0 ) {
		AfxMessageBox( "Geneddoc:new:fail:" );
		return;
	}

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		pSegArr[i].pGeneStor = (GeneStor *) GlobalLock( tSegHandle );
		pSegArr[i].pCGSeg = tCGSeg;
		if ( pSegArr[i].pGeneStor == NULL ) { 
			AfxMessageBox("ClearShade:GlobalLock:Fail");
			delete pSegArr;
			return;
		}

		i++;
	}
	
	DWORD OuterCount = tCGSeg->GetTextLength();

	for ( DWORD tCount = 0L; tCount < OuterCount; ++tCount ) {
		// Inner Loop
		for ( i = 0; i < RowCount; ++i ) {
			if ( pSegArr[i].pCGSeg->GetStyle() != LINESEQUENCE ) {
				(pSegArr[i].pGeneStor)[tCount].CharDisplay = ' ';
				(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.m_BackColor;
				(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.m_ForeColor;
				continue;
			}
			// Lets Clear out old shades here.
			(pSegArr[i].pGeneStor)[tCount].BackColor = m_UserVars.m_BackColor;
			(pSegArr[i].pGeneStor)[tCount].TextColor = m_UserVars.m_ForeColor;
			// (pSegArr[i].pGeneStor)[tCount].CharScore = 0;
			// Lets Clear out old Displays
			char tChar = (pSegArr[i].pGeneStor)[tCount].CharGene;
			(pSegArr[i].pGeneStor)[tCount].CharDisplay = tChar;

		}
	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		tSegHandle = tCGSeg->GetTextHandle();
		GlobalUnlock( tSegHandle );
	}

	delete pSegArr;
}

void
CGenethonDoc::GetColors( COLORREF * TextColor, COLORREF *BkColor )
{
	*BkColor = m_UserVars.m_BackColor;
	*TextColor = m_UserVars.m_ForeColor;
}


CGeneSegment* 
CGenethonDoc::GetSequenceFromName( const CString& Name )
{
	if ( pGSFiller == NULL ) return NULL;

	CGeneSegment *pCGSeg;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		pCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		
		if ( pCGSeg->GetStyle() != LINESEQUENCE ) continue;

		// CString
		if ( !pCGSeg->GetTitle().CompareNoCase( Name ) ) {
			return pCGSeg;
		}
	}
	
	return NULL;
}


void 
CGenethonDoc::CopyUserVars( UserVars * nUserVars, UserVars * oUserVars  )
{

	// Start User Variables ....

	nUserVars->m_FontWeight = oUserVars->m_FontWeight;
	nUserVars->m_FontSize = oUserVars->m_FontSize;
	nUserVars->m_ForeColor = oUserVars->m_ForeColor;

	nUserVars->m_BackColor = oUserVars->m_BackColor;
	nUserVars->m_WidthMode = oUserVars->m_WidthMode;
	nUserVars->m_FixedXSize = oUserVars->m_FixedXSize;

	nUserVars->m_LeftBorder = oUserVars->m_LeftBorder;
	nUserVars->m_RightBorder = oUserVars->m_RightBorder;
	nUserVars->m_TopBorder = oUserVars->m_TopBorder;
	nUserVars->m_BottomBorder = oUserVars->m_BottomBorder;

	// Copy DisplayVars

	nUserVars->m_Vars.CopyVars( &oUserVars->m_Vars, this );
	// Will Need to copy all of em ...
	POSITION tPos = oUserVars->m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars *pVars = (CDisplayVars *)oUserVars->m_DisplayVars.GetNext( tPos );
		CDisplayVars *pnVars = new CDisplayVars;

		pnVars->CopyVars( pVars, this );

		nUserVars->m_DisplayVars.AddTail( pnVars );
	}
	
	nUserVars->m_ConsensusLine = oUserVars->m_ConsensusLine;
	
	// Copy this	
	nUserVars->m_ShowTail = oUserVars->m_ShowTail;

	nUserVars->m_Orientation = oUserVars->m_Orientation;
	((CGenethonApp *)AfxGetApp())->SetLandscape( nUserVars->m_Orientation );

	nUserVars->m_ProjectType = oUserVars->m_ProjectType;
	
	//	This is basically static for now. When user tables are supported, 
//	Then we will copy it/
//	CPtrArray	nUserVars->m_ScoreTableArray;


//	nUserVars->m_DisplayMethod = oUserVars->m_DisplayMethod;

	nUserVars->m_PrintShading = oUserVars->m_PrintShading;
	nUserVars->m_PrintString = oUserVars->m_PrintString;
	nUserVars->m_PrintStringFlag = oUserVars->m_PrintStringFlag;
	nUserVars->m_PrintPageNumber = oUserVars->m_PrintPageNumber;
	nUserVars->m_PrintPageOffset = oUserVars->m_PrintPageOffset;
	nUserVars->m_PrintFontWeight = oUserVars->m_PrintFontWeight;
	nUserVars->m_PrintFontSize = oUserVars->m_PrintFontSize;
	nUserVars->m_PrintFontName = oUserVars->m_PrintFontName;
	nUserVars->m_PrintGeneBlock = oUserVars->m_PrintGeneBlock;


	nUserVars->m_PictWidth = oUserVars->m_PictWidth;
	nUserVars->m_PictHeight = oUserVars->m_PictHeight;
	nUserVars->m_PictAscent = oUserVars->m_PictAscent;

	nUserVars->m_strLead = oUserVars->m_strLead;
	nUserVars->m_strTail = oUserVars->m_strTail;
	nUserVars->m_MaxNameLength = oUserVars->m_MaxNameLength;

	nUserVars->m_SumColInch = oUserVars->m_SumColInch;
	nUserVars->m_Sum2Wid = oUserVars->m_Sum2Wid;
	nUserVars->m_SumDefDis = oUserVars->m_SumDefDis;
	nUserVars->m_SumTextBlack = oUserVars->m_SumTextBlack;

	nUserVars->m_PrintFileName = oUserVars->m_PrintFileName;
	nUserVars->m_PrintDate = oUserVars->m_PrintDate;

	nUserVars->m_MakeBackups = oUserVars->m_MakeBackups;
	nUserVars->m_LocAfterName = oUserVars->m_LocAfterName;
	nUserVars->m_LocAfterSeq = oUserVars->m_LocAfterSeq;

}

void
CGenethonDoc::ClearUserVars( UserVars * dUserVars )
{
	ShadePairStruct *tSPS;
	int count = dUserVars->m_ShadePairArray.GetSize();
	for ( int i = 0; i < count; ++i ) {
		tSPS = (ShadePairStruct *)dUserVars->m_ShadePairArray[i];
		delete tSPS;
	}
	dUserVars->m_ShadePairArray.RemoveAll();

	// DisplayVars
	POSITION tPos = dUserVars->m_DisplayVars.GetHeadPosition();
	while ( tPos != NULL ) {
		CDisplayVars *pVars = (CDisplayVars *)dUserVars->m_DisplayVars.GetNext( tPos );
		delete pVars;
	}
	dUserVars->m_DisplayVars.RemoveAll();

}




void CGenethonDoc::OnConfigure() 
{
	DoConfigure();
}	


void CGenethonDoc::DoConfigure(int ActivePage, int ReDraw ) 
{
	// TODO: Add your command handler code here

	char tBuff[100];
	int DisplayChanged = 0;
	int ScoreChanged = 0;

	CModalDisplayPropSheet tDlg;
	// Get Base Display Vars

	// Display Page	
	tDlg.m_DisplayPage.pDoc = this;
	if ( m_UserVars.m_FontWeight == FW_NORMAL ) {
		tDlg.m_DisplayPage.m_FontWeight = "Normal";
	} else {
		tDlg.m_DisplayPage.m_FontWeight = "Bold";
	}

	tDlg.m_DisplayPage.m_FontSize = m_UserVars.m_FontSize;
	
	tDlg.m_DisplayPage.m_AutoWidth = m_UserVars.m_WidthMode;
	tDlg.m_DisplayPage.m_FixedWidth = m_UserVars.m_FixedXSize;
	tDlg.m_DisplayPage.m_ShowTail = m_UserVars.m_ShowTail;

	tDlg.m_DisplayPage.m_PictWidth = m_UserVars.m_PictWidth;
	tDlg.m_DisplayPage.m_PictHeight = m_UserVars.m_PictHeight;
	tDlg.m_DisplayPage.m_PictAscent = m_UserVars.m_PictAscent;

	tDlg.m_DisplayPage.m_MaxNameLength = m_UserVars.m_MaxNameLength;
	tDlg.m_DisplayPage.m_strLead = m_UserVars.m_strLead;
	tDlg.m_DisplayPage.m_strTail = m_UserVars.m_strTail;

	tDlg.m_DisplayPage.m_SumColInch = m_UserVars.m_SumColInch;
	tDlg.m_DisplayPage.m_Sum2Wid = m_UserVars.m_Sum2Wid;
	tDlg.m_DisplayPage.m_SumDefDis = m_UserVars.m_SumDefDis;
	tDlg.m_DisplayPage.m_SumTextBlack = m_UserVars.m_SumTextBlack;
	tDlg.m_DisplayPage.m_LocAfterName = m_UserVars.m_LocAfterName;
	tDlg.m_DisplayPage.m_LocAfterSeq = m_UserVars.m_LocAfterSeq;
	

	// Print Page	
	tDlg.m_PrintPage.m_TopBorder = m_UserVars.m_TopBorder;
	tDlg.m_PrintPage.m_BottomBorder = m_UserVars.m_BottomBorder;
	tDlg.m_PrintPage.m_LeftBorder = m_UserVars.m_LeftBorder;
	tDlg.m_PrintPage.m_RightBorder = m_UserVars.m_RightBorder;

	tDlg.m_PrintPage.m_Orientation = m_UserVars.m_Orientation;
	
	tDlg.m_PrintPage.m_PrintFontName = m_UserVars.m_PrintFontName;

	if ( m_UserVars.m_PrintFontWeight == FW_NORMAL ) {
		tDlg.m_PrintPage.m_PrintFontWeight = "Normal";
	} else {
		tDlg.m_PrintPage.m_PrintFontWeight = "Bold";
	}

	itoa( m_UserVars.m_PrintFontSize, tBuff, 10 );
	tDlg.m_PrintPage.m_PrintFontPoints = tBuff;

	tDlg.m_PrintPage.m_PrintPage = m_UserVars.m_PrintPageNumber;
	tDlg.m_PrintPage.m_PrintPageOffset = m_UserVars.m_PrintPageOffset;
	tDlg.m_PrintPage.m_PrintString = m_UserVars.m_PrintString;
	tDlg.m_PrintPage.m_GeneBlockPos = m_UserVars.m_PrintGeneBlock;
	tDlg.m_PrintPage.m_PrintStringFlag = m_UserVars.m_PrintStringFlag;
	tDlg.m_PrintPage.m_PrintShading = m_UserVars.m_PrintShading;
	tDlg.m_PrintPage.m_PrintFileName = m_UserVars.m_PrintFileName;
	tDlg.m_PrintPage.m_PrintDate = m_UserVars.m_PrintDate;

	// For Project Type;
//	tDlg.m_ScoreTablePage.m_DialogInited = 0;
//	tDlg.m_PropertyGroupPage.m_DialogInited = 0;

	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	if ( tDlg.m_DisplayPage.m_FontWeight == "Normal" ) {
		m_UserVars.m_FontWeight = FW_NORMAL;
	} else {
		m_UserVars.m_FontWeight = FW_BOLD;
	}
    m_UserVars.m_FontSize = tDlg.m_DisplayPage.m_FontSize;

	m_UserVars.m_WidthMode = tDlg.m_DisplayPage.m_AutoWidth;
	m_UserVars.m_FixedXSize = tDlg.m_DisplayPage.m_FixedWidth;
	m_UserVars.m_ShowTail = tDlg.m_DisplayPage.m_ShowTail;

	m_UserVars.m_PictWidth = tDlg.m_DisplayPage.m_PictWidth;
	m_UserVars.m_PictHeight = tDlg.m_DisplayPage.m_PictHeight;
	m_UserVars.m_PictAscent = tDlg.m_DisplayPage.m_PictAscent;
	
	m_UserVars.m_MaxNameLength = tDlg.m_DisplayPage.m_MaxNameLength;
	m_UserVars.m_strLead = tDlg.m_DisplayPage.m_strLead;
	m_UserVars.m_strTail = tDlg.m_DisplayPage.m_strTail;
	m_UserVars.m_SumColInch = tDlg.m_DisplayPage.m_SumColInch;
	m_UserVars.m_Sum2Wid = tDlg.m_DisplayPage.m_Sum2Wid;
	m_UserVars.m_SumDefDis = tDlg.m_DisplayPage.m_SumDefDis;
	m_UserVars.m_SumTextBlack = tDlg.m_DisplayPage.m_SumTextBlack;

	m_UserVars.m_LocAfterName = tDlg.m_DisplayPage.m_LocAfterName;
	m_UserVars.m_LocAfterSeq = tDlg.m_DisplayPage.m_LocAfterSeq;
		

	// PrintPage
	m_UserVars.m_TopBorder = tDlg.m_PrintPage.m_TopBorder;
	m_UserVars.m_BottomBorder = tDlg.m_PrintPage.m_BottomBorder;
	m_UserVars.m_LeftBorder = tDlg.m_PrintPage.m_LeftBorder;
	m_UserVars.m_RightBorder = tDlg.m_PrintPage.m_RightBorder;

	m_UserVars.m_Orientation = tDlg.m_PrintPage.m_Orientation;

	m_UserVars.m_PrintFontName = tDlg.m_PrintPage.m_PrintFontName;

	if ( tDlg.m_PrintPage.m_PrintFontWeight == "Normal" ) {
		m_UserVars.m_PrintFontWeight = FW_NORMAL;
	} else {
		m_UserVars.m_PrintFontWeight = FW_BOLD;
	}
	m_UserVars.m_PrintFontSize = atoi ( tDlg.m_PrintPage.m_PrintFontPoints );

	m_UserVars.m_PrintPageNumber= tDlg.m_PrintPage.m_PrintPage;
	m_UserVars.m_PrintPageOffset = tDlg.m_PrintPage.m_PrintPageOffset;
	m_UserVars.m_PrintString = tDlg.m_PrintPage.m_PrintString;
	m_UserVars.m_PrintGeneBlock = tDlg.m_PrintPage.m_GeneBlockPos;
	m_UserVars.m_PrintStringFlag = tDlg.m_PrintPage.m_PrintStringFlag;
	m_UserVars.m_PrintShading = tDlg.m_PrintPage.m_PrintShading;
	m_UserVars.m_PrintFileName = tDlg.m_PrintPage.m_PrintFileName;
	m_UserVars.m_PrintDate = tDlg.m_PrintPage.m_PrintDate;

	// Set printer orientation for this file.
	((CGenethonApp *)AfxGetApp())->SetLandscape( m_UserVars.m_Orientation );

//
//	if ( tDlg.m_PrintPage.m_DisplayMethodChanged ) {
//
//		m_UserVars.m_DisplayMethod = tDlg.m_PrintPage.m_DisplayMethod;
//		
//		DisplayChanged = 1;
//	}
//

	// Dirty the document
	SetModifiedFlag();

}

void SplitFilename(CString fileName, CString* filePath, CString* appName) {
	int lastSep = fileName.ReverseFind('/');
	*filePath = fileName.Mid(0, lastSep);
	int dotPy = fileName.Find(".py");
	*appName = fileName.Mid(lastSep+1, dotPy-lastSep-1);
}

static int numargs = 0;
static CString someString;
/* Return the number of arguments of the application command line */

static PyObject*
emb_somestring(PyObject *self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, ":somestring"))
		return NULL;
	return PyUnicode_FromString(someString);
}

static PyObject*
emb_numargs(PyObject *self, PyObject *args)
{
	if (!PyArg_ParseTuple(args, ":numargs"))
		return NULL;
	return PyLong_FromLong(numargs);
}

static PyMethodDef EmbMethods[] = {
	{ "numargs", emb_numargs, METH_VARARGS, "Return the number of arguments received by the process." },
	{ "somestring", emb_somestring, METH_VARARGS, "A String for writing." },
	{ NULL, NULL, 0, NULL }
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
	NULL, NULL, NULL, NULL
};

static PyObject*
PyInit_emb(void)
{
	return PyModule_Create(&EmbModule);
}

void CGenethonDoc::anything()
{
}
void CGenethonDoc::OnPlaypython()
{
//	CString fileName = "c:/users/karl/plotstdvectors.py";
//	CString function = "plotStdVectors";
//	this->runTest1(fileName, function);
//	CString fileName = "c:/users/karl/multiply.py";
//	CString function = "multiply";
//	CString output = this->runTest2(fileName, function);
	CString output = this->runTest3();
	TRACE(output);
	writeToReport(output);
}

CString CGenethonDoc::runTest2(CString& fileName, CString& function) {
	CString output = CString();
//	CString fileName = "c:/users/karl/multiply.py";
	/*
	CString fileName;
	GetTempFileName(fileName);
	fileName.Replace(".tmp", ".py");

	CStdioFile wFile(fileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate);
	wFile.WriteString("def multiply(a,b):\n");
	wFile.WriteString("  print(\"Will compute\", a, \"times\", b)\n");
	wFile.WriteString("  c = 0\n");
	wFile.WriteString("  for i in range(0, a):\n");
	wFile.WriteString("    c = c + b\n");
	wFile.WriteString("  return c\n");
	wFile.Close();
	*/

	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	PyObject *ptype, *pvalue, *ptraceback;
	int i;

	numargs = 4;
	someString = CString("Very well done sir.");
	PyImport_AppendInittab("emb", &PyInit_emb);

	// Error checking of pName left out
	wchar_t *program = Py_DecodeLocale("GeneDoc", NULL);
	Py_SetProgramName(program);
	Py_Initialize();

	CString filePath;
	CString appName;
	SplitFilename(fileName, &filePath, &appName);

	pName = PyUnicode_DecodeFSDefault(appName);


	PyObject* sysPath = PySys_GetObject("path");
	PyObject* pyPath = PyUnicode_FromString(filePath);
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Lib");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Dlls");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Lib/site-packages");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, function);
		// pFunc is a new reference 

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(2);
			pValue = PyLong_FromLong(2);
			if (!pValue) {
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				TRACE("Cannot convert argument\n");
				return output;
			}
			PyTuple_SetItem(pArgs, 0, pValue);
			pValue = PyLong_FromLong(3);
			if (!pValue) {
				Py_DECREF(pArgs);
				Py_DECREF(pModule);
				TRACE("Cannot convert argument\n");
				return output;
			}
			PyTuple_SetItem(pArgs, 1, pValue);
			// pValue reference stolen here:
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				Py_DECREF(pValue);
				PyObject* v = PyObject_GetAttrString(pModule, "richTextOutput");
				output.Format("Result of call: %ld\n%s", PyLong_AsLong(pValue), PyUnicode_AsUTF8(v));
				TRACE(output);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				output = handlePyError();
				TRACE(output);
				return output;
			}
		}
		else {
			if (PyErr_Occurred()) {
				output = handlePyError();
				TRACE("Cannot find function \"%s\"\n", "multiply");
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		TRACE("Failed to load \"%s\"\n", appName);
	}

	return output;

	//	DeleteTempFile(fileName);
	/*
	CString FileName;
	GetTempFileName(FileName);
	CStdioFile wFile(FileName, CFile::modeWrite | CFile::typeText | CFile::modeCreate);
	wFile.WriteString("Test test test test test test\n");
	wFile.Close();

	m_pTextView->LoadFile(FileName);

	DeleteTempFile(FileName);
	*/

}

CString CGenethonDoc::runTest1(CString& fileName, CString& function) {

	CString output = CString();
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgTuple, *pValue, *pXVec, *pYVec;
	PyObject *ptype, *pvalue, *ptraceback;

	int i;

	// Set the path to include the current directory in case the module is located there. Found from
	// http://stackoverflow.com/questions/7624529/python-c-api-doesnt-load-module
	// and http://stackoverflow.com/questions/7283964/embedding-python-into-c-importing-modules

	CString filePath;
	CString appName;
	SplitFilename(fileName, &filePath, &appName);

	pName = PyUnicode_DecodeFSDefault(appName);

	PyObject *sys = PyImport_ImportModule("sys");
	PyObject *path = PyObject_GetAttrString(sys, "path");
	PyList_Append(path, PyUnicode_FromString(filePath));
	PyList_Append(path, PyUnicode_FromString("c:/users/karl/Anaconda3"));
	PyList_Append(path, PyUnicode_FromString("c:/users/karl/Anaconda3/Lib"));
	PyList_Append(path, PyUnicode_FromString("c:/users/karl/Anaconda3/DLLs"));

	pName = PyUnicode_FromString(appName);   //Get the name of the module
	pModule = PyImport_Import(pName);     //Get the module

	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, function);   //Get the function by its name
															/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {

			//Set up a tuple that will contain the function arguments. In this case, the
			//function requires two tuples, so we set up a tuple of size 2.
			pArgTuple = PyTuple_New(2);

			//Make some vectors containing the data
			static const double xarr[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
			std::vector<double> xvec(xarr, xarr + sizeof(xarr) / sizeof(xarr[0]));
			static const double yarr[] = { 0,0,1,1,0,0,2,2,0,0,1,1,0,0 };
			std::vector<double> yvec(yarr, yarr + sizeof(yarr) / sizeof(yarr[0]));

			//Transfer the C++ vector to a python tuple
			pXVec = PyTuple_New(xvec.size());
			for (i = 0; i < xvec.size(); ++i) {
				pValue = PyFloat_FromDouble(xvec[i]);
				if (!pValue) {
					Py_DECREF(pXVec);
					Py_DECREF(pModule);
					return "Cannot convert array value\n";
				}
				PyTuple_SetItem(pXVec, i, pValue);
			}

			//Transfer the other C++ vector to a python tuple
			pYVec = PyTuple_New(yvec.size());
			for (i = 0; i < yvec.size(); ++i) {
				pValue = PyFloat_FromDouble(yvec[i]);
				if (!pValue) {
					Py_DECREF(pYVec);
					Py_DECREF(pModule);
					return "Cannot convert array value\n";
				}
				PyTuple_SetItem(pYVec, i, pValue); //
			}

			//Set the argument tuple to contain the two input tuples
			PyTuple_SetItem(pArgTuple, 0, pXVec);
			PyTuple_SetItem(pArgTuple, 1, pYVec);

			//Call the python function
			pValue = PyObject_CallObject(pFunc, pArgTuple);

			Py_DECREF(pArgTuple);
//			Py_DECREF(pXVec);
//			Py_DECREF(pYVec);

			if (pValue != NULL) {
				PyObject* v = PyObject_GetAttrString(pModule, "richTextOutput");
				output.Format("Result of call: %ld", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}

			//Some error catching
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				return handlePyError();
			}
		}
		else {
			if (PyErr_Occurred()) {
				return handlePyError();
			}
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		return handlePyError();
	}
	return output;
}

void CGenethonDoc::writeToReport(CString& output) {
	if (m_pTextView == NULL) {

		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
	}
	else {

		m_pTextView->GetParentFrame()->ActivateFrame();
		m_pTextView->Invalidate();
	}

	CMemFile* memFile = new CMemFile();
	//serialize object into the pData
	//	char* cBuff = new char[128];
	//	sprintf_s(cBuff, 128, "%s", "Test test test test test test\n");

	memFile->Write(output, output.GetLength());
	memFile->SeekToBegin();

	//	txtFile->Open(PathName, CFile::modeRead);
	//	CArchive archive(&txtFile, CArchive::load);

	//	SerializeRaw( archive );
	m_pTextView->LoadMemfile(memFile);

	memFile->Close();
	delete memFile;
}

CString CGenethonDoc::handlePyError() {
	CString retVal = CString();

	PyObject* excType, *excValue, *excTraceback;
	PyErr_Fetch(&excType, &excValue, &excTraceback);
	PyErr_NormalizeException(&excType, &excValue, &excTraceback);

	CString callBacks = CString();
	CString work = CString();
	PyTracebackObject* ptraceback = (PyTracebackObject*)excTraceback;
	work.Format("File: %s\nLine no: %d\n", PyUnicode_AsUTF8(PyObject_Str(((PyTracebackObject*)ptraceback)->tb_frame->f_code->co_filename)), ((PyTracebackObject*)ptraceback)->tb_lineno);
	callBacks.Append(work.GetString());
	// Advance to the last frame (python puts the most-recent call at the end)
	while (ptraceback->tb_next != NULL) {
		ptraceback = ptraceback->tb_next;
		work.Format("File: %s\nLine no: %d\n", PyUnicode_AsUTF8(PyObject_Str(((PyTracebackObject*)ptraceback)->tb_frame->f_code->co_filename)), ((PyTracebackObject*)ptraceback)->tb_lineno);
		callBacks.Append(work.GetString());
	}
	// At this point I have access to the line number via traceback->tb_lineno,
	// but where do I get the file name from?
	int line = ptraceback->tb_lineno;
	retVal.Format("Error type: %s\n%s\nError: %s", 
		PyUnicode_AsUTF8(PyObject_Str(excType)), 
		callBacks.GetString(),
		PyUnicode_AsUTF8(PyObject_Str(excValue))
	);
	// Now you have two options, restoring the exception or disposing it.
	PyErr_Restore(excType, excValue, excTraceback);

	//---->

	Py_XDECREF(excType);
	Py_XDECREF(excValue);
	Py_XDECREF(excTraceback);

	return retVal;

}

CString CGenethonDoc::runTest3() {
	PyObject* sysPath = PySys_GetObject("path");
	PyObject* pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Lib");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Dlls");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);
	pyPath = PyUnicode_FromString("c:/users/karl/Anaconda3/Lib/site-packages");
	PyList_Append(sysPath, pyPath);
	Py_DECREF(pyPath);

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("import pylab");
	PyRun_SimpleString("print(sys.version)");
	PyRun_SimpleString("print()");
	PyRun_SimpleString("pylab.plot(range(10))");
	PyRun_SimpleString("pylab.show()");
	return "Test3 Run";
}

