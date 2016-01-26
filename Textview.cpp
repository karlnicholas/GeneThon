// TextView.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, VIEWBASE)

CTextView::CTextView()
{
	m_pFont = new CFont;
	if ( m_pFont == NULL ) {
		AfxMessageBox("textview:new:fail");
	}
}

CTextView::~CTextView()
{
	CGenethonDoc* pDoc = (CGenethonDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->m_pTextView = NULL;
	delete m_pFont;
}


BEGIN_MESSAGE_MAP(CTextView, VIEWBASE)
	//{{AFX_MSG_MAP(CTextView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_REPSAVEFILE, OnRepsavefile)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_PRINT, VIEWBASE::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, VIEWBASE::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, VIEWBASE::OnFilePrintPreview)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnInitialUpdate()
{
	VIEWBASE::OnInitialUpdate();

	// Set the printing margins (720 twips = 1/2 inch).
	SetMargins(CRect(720, 720, 720, 720));
	
}


BOOL CTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

/*
void CTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

*/
CDocument *CTextView::GetDocument()
{
	return m_pDocument;
}

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

CFile *txtFile;


DWORD CALLBACK TextRead(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// CFile
	*pcb = txtFile->Read(pbBuff, cb );
	return 0;
}

void CTextView::LoadFile(CString& PathName)
{
	CGenethonDoc* pDoc = (CGenethonDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	txtFile = new CFile();
   
	txtFile->Open(PathName, CFile::modeRead );
//	CArchive archive(&txtFile, CArchive::load);

//	SerializeRaw( archive );

	EDITSTREAM es;
	es.pfnCallback = TextRead;

	GetRichEditCtrl().StreamIn( SF_TEXT, es );

	txtFile->Close();
	delete txtFile;

}


CMemFile *memFile;
DWORD CALLBACK MemfileRead(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// CFile
	*pcb = memFile->Read(pbBuff, cb);
	return 0;
}

void CTextView::LoadMemfile(CMemFile* writtenMemFile)
{
	CGenethonDoc* pDoc = (CGenethonDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	memFile = writtenMemFile;
	//	CArchive archive(&txtFile, CArchive::load);

	//	SerializeRaw( archive );

	EDITSTREAM es;
	es.pfnCallback = MemfileRead;

	GetRichEditCtrl().StreamIn(SF_TEXT, es);

}

int CTextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{                               
	m_nWordWrap = VIEWBASE::WrapNone;

	if (VIEWBASE::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_pFont->CreateFont(14,0,0,0,400,FALSE,FALSE,0,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		FIXED_PITCH,"Courier New"));
	SetFont(m_pFont);

	GetRichEditCtrl().SetOptions( ECOOP_OR, ECO_READONLY );
  
	CGenethonDoc* pDoc = (CGenethonDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->m_pTextView = this;

	return 0;
}

void CTextView::OnRepsavefile() 
{
	// TODO: Add your command handler code here
	CFileDialog tDlg(FALSE);

	if ( tDlg.DoModal() != IDOK ) return;


	SaveFile( tDlg.GetPathName() ); // Let em know



	
}

DWORD CALLBACK TextWrite(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb)
{
	// CFile
	txtFile->Write(pbBuff, cb );
	*pcb = cb;
	return 0;
}

void CTextView::SaveFile(CString& PathName)
{
	CGenethonDoc* pDoc = (CGenethonDoc*)GetDocument();
	ASSERT_VALID(pDoc);

	txtFile = new CFile();
   
	txtFile->Open( PathName, CFile::modeCreate | CFile::modeWrite );

	//	CArchive archive(&txtFile, CArchive::load);

//	SerializeRaw( archive );

	EDITSTREAM es;
	es.pfnCallback = TextWrite;

	GetRichEditCtrl().StreamOut( SF_TEXT, es );

	txtFile->Close();
	delete txtFile;

}
