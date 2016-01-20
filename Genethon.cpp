// Genethon.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenethonApp

BEGIN_MESSAGE_MAP(CGenethonApp, CWinApp)
	//{{AFX_MSG_MAP(CGenethonApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CGenethonApp::OnMyFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenethonApp construction

CGenethonApp::CGenethonApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGenethonApp object

CGenethonApp NEAR theApp;

/////////////////////////////////////////////////////////////////////////////
// CGenethonApp initialization
static BOOL NEAR PASCAL SetRegKey(LPCSTR lpszKey, LPCSTR lpszValue) { 
   if (::RegSetValue(HKEY_CLASSES_ROOT, lpszKey, REG_SZ, lpszValue,
          lstrlen(lpszValue)) != ERROR_SUCCESS)
      {
      TRACE1("Warning: registration database update failed for key '%Fs'\n", lpszKey);
      return FALSE;
      }

  return TRUE;

} 


BOOL CGenethonApp::InitInstance()
{
	// A flag to test if really a NewDocument or a 'CreateNewWindow' command
	m_ReallyNewFlag = 1;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	SetRegistryKey( "" );

	SetDialogBkColor();        // Set dialog background color to gray
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)


	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pGenethonTemplate = new CMultiDocTemplate(
		IDR_GENEDOTYPE,
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CGeneMDIChildWnd),        // standard MDI child frame
		RUNTIME_CLASS(CGenethonView)
	);

	AddDocTemplate(m_pGenethonTemplate);

	m_pSummaryViewTemplate = new CMultiDocTemplate(
		IDR_SUMMARYVIEW,	
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CGeneMDIChildWnd),
		RUNTIME_CLASS(CSummaryView)
	);

	m_pTextViewTemplate = new CMultiDocTemplate(
		IDR_TEXTVIEW,
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CTextView)
	);

	m_pTreeViewTemplate = new CMultiDocTemplate(
		IDR_PHYLOVIEW,
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CPhyloMDIChildWnd),
		RUNTIME_CLASS(CPhylogenView)
	);

	m_pDStatViewTemplate = new CMultiDocTemplate(
		IDR_DSTATVIEW,
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CDStatMDIChildWnd),
		RUNTIME_CLASS(CDStatView)
	);
	m_pGelViewTemplate = new CMultiDocTemplate(
		IDR_GELVIEW,
		RUNTIME_CLASS(CGenethonDoc),
		RUNTIME_CLASS(CMDIChildWnd),
		RUNTIME_CLASS(CGelView)
	);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;


	RegisterShellFileTypes(true);

	// do other initialization after (possibly) creating the splash window
	EnableShellOpen();
	m_pMainWnd->DragAcceptFiles();


	
	// Registration Type Name
   CString      strFileTypeName;

   // Position used if more than one document template.
   m_pGenethonTemplate->GetDocString(strFileTypeName, CDocTemplate::regFileTypeId);

   // Add another file extension to registration database.
   // If you double-click a .APP or .SAV file in File Manager it
   // automatically starts this application.
   //
   // SetRegKey adds a file extension to the Registration Database
   SetRegKey(".msb", strFileTypeName);

	// create a new (empty) document
//	OnFileNew();
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
//	pMainFrame->ShowWindow(m_nCmdShow);
//	pMainFrame->UpdateWindow();

	// The main window has been initialized, so show and update it.
	// Old style ..pMainFrame->ShowWindow(m_nCmdShow);

	((CMainFrame*)m_pMainWnd)->InitialShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	m_OKOrientCheck = 1;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
	CBitmapButton m_SmallLogo;
	CBitmapButton m_GeneBut;

public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGenethonApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGenethonApp commands

CDocument* CGenethonApp::CreateNewDocument()
{
	CDocument* tDoc;
	m_ReallyNewFlag = 0;

	tDoc = m_pGenethonTemplate->OpenDocumentFile(NULL);
    // if returns NULL, the user has already been alerted
    
	m_ReallyNewFlag = 1;
    
    
    return tDoc;
}

void CGenethonApp::OnMyFilePrintSetup()
{
	m_OKOrientCheck = 0;

	CWinApp::OnFilePrintSetup();

		
	CMDIChildWnd * tp = (CMDIChildWnd *)((CMainFrame *)m_pMainWnd)->GetActiveFrame();

	CDocument *tDoc = tp->GetActiveDocument();

	if ( tDoc != NULL ) {

		ASSERT( tDoc->IsKindOf(RUNTIME_CLASS(CGenethonDoc)) );
		CGenethonDoc *pDoc = (CGenethonDoc *)tDoc;
		
		pDoc->CheckOrientation();
	}

	m_OKOrientCheck = 1;
}

void CGenethonApp::SetLandscape(int LSFlag)
{
    // Get default printer settings.
    PRINTDLG   pd;
    pd.lStructSize = (DWORD) sizeof(PRINTDLG);

    if (GetPrinterDeviceDefaults(&pd))
	{
        // Lock memory handle.
        DEVMODE * pDevMode =
            (DEVMODE *)GlobalLock(m_hDevMode);
        if (pDevMode)
		{
			if ( LSFlag ) {
				// Change printer settings in here.
				pDevMode->dmOrientation = DMORIENT_LANDSCAPE;
			} else {
				// Change printer settings in here.
				pDevMode->dmOrientation = DMORIENT_PORTRAIT;
			}

            // Unlock memory handle.
            GlobalUnlock(m_hDevMode);
		}
	}

}

int 
CGenethonApp::GetLandscape()
{

    // Get default printer settings.
    PRINTDLG   pd;
    pd.lStructSize = (DWORD) sizeof(PRINTDLG);
	int rc = 0;

    if (GetPrinterDeviceDefaults(&pd))
	{
        // Lock memory handle.
        DEVMODE * pDevMode =
            (DEVMODE *)GlobalLock(m_hDevMode);
        if (pDevMode)
		{
            // Change printer settings in here.
            if ( pDevMode->dmOrientation == DMORIENT_LANDSCAPE ) {
				rc = 1;
			} else {
				rc = 0;
			}
 
            // Unlock memory handle.
            GlobalUnlock(m_hDevMode);
		}
	}

	return rc;
}


int 
CGenethonApp::ExitInstance()
{
	delete m_pSummaryViewTemplate;
	delete m_pTextViewTemplate;
	delete m_pTreeViewTemplate;
	delete m_pDStatViewTemplate;
	delete m_pGelViewTemplate;
	return CWinApp::ExitInstance();
}

void CAboutDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CBitmap bmp, *poldbmp;
	CDC memdc;
 
	// Create a compatible memory DC
	memdc.CreateCompatibleDC( &dc );
 
	// Load the bitmap resource
	bmp.LoadBitmap( IDB_SMALLLOGO );

	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject( &bmp );
 
      // Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt( 10, 10, 153, 198, &memdc, 0, 0, SRCCOPY );

	bmp.DeleteObject();      
      
	bmp.LoadBitmap( IDB_GENETHON );
 
	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject( &bmp );
      
	// Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt( 175, 3, 95, 38, &memdc, 0, 0, SRCCOPY );

	memdc.SelectObject( poldbmp );
	
	bmp.DeleteObject();      
      
	bmp.LoadBitmap( IDB_INLOVE );
 
	// Select the bitmap into the DC
	poldbmp = memdc.SelectObject( &bmp );
      
	// Copy (BitBlt) bitmap from memory DC to screen DC
	dc.BitBlt( 169, 139, 107, 69, &memdc, 0, 0, SRCCOPY );

	memdc.SelectObject( poldbmp );

	//	bmp.DeleteObject();      

	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
