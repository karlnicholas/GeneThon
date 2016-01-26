// Genethon.h : main header file for the Genethon application
//

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGenethonApp:
// See CGenethon.cpp for the implementation of this class
//

class CGenethonApp : public CWinApp
{
public:
	CGenethonApp();

// Overrides
	virtual BOOL InitInstance();
//	virtual CDocument* OpenDocumentFile( LPCSTR lpszFileName );

// Implementation
	CMultiDocTemplate* m_pGenethonTemplate;

	CDocument* CreateNewDocument();
	void SetLandscape(int LSFlag );
	int GetLandscape();
	void OnMyFilePrintSetup();
	int m_OKOrientCheck;
	CMultiDocTemplate *m_pSummaryViewTemplate;
	CMultiDocTemplate *m_pTextViewTemplate;
	int ExitInstance();
	
	int m_ReallyNewFlag;


	//{{AFX_MSG(CGenethonApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
