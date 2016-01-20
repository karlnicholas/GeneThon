// findrepl.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindReplaceDlg dialog


CFindReplaceDlg::CFindReplaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindReplaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindReplaceDlg)
	m_FindString = _T("");
	m_ReplaceString = _T("");
	//}}AFX_DATA_INIT
}

void CFindReplaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindReplaceDlg)
	DDX_Text(pDX, IDC_FINDSTRING, m_FindString);
	DDX_Text(pDX, IDC_REPLACE, m_ReplaceString);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindReplaceDlg, CDialog)
	//{{AFX_MSG_MAP(CFindReplaceDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFindReplaceDlg message handlers

BOOL CFindReplaceDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
