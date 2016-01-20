// selproje.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelProject dialog


CSelProject::CSelProject(CWnd* pParent /*=NULL*/)
	: CDialog(CSelProject::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelProject)
	//}}AFX_DATA_INIT
}

void CSelProject::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelProject)
	DDX_Control(pDX, IDC_PROJLIST, m_listProj);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelProject, CDialog)
	//{{AFX_MSG_MAP(CSelProject)
	ON_LBN_SELCHANGE(IDC_PROJLIST, OnSelchangeProjlist)
	ON_LBN_DBLCLK(IDC_PROJLIST, OnDblclkProjlist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSelProject message handlers

BOOL CSelProject::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString DocName;
	// CWinApp
	CMultiDocTemplate* pMDTmpl = ((CGenedocApp *)AfxGetApp())->m_pGenedocTemplate;

	POSITION dPos = pMDTmpl->GetFirstDocPosition( );
	while ( dPos != NULL ) {
		poDoc = (CGenedocDoc*)pMDTmpl->GetNextDoc(dPos);
		if ( poDoc == pDoc ) continue;
		DocName = poDoc->GetTitle();
		int aloc = m_listProj.AddString( DocName );
		m_listProj.SetItemDataPtr( aloc, poDoc );
	}
	
	poDoc = NULL;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSelProject::OnSelchangeProjlist() 
{
	// TODO: Add your control notification handler code here
	int aloc = m_listProj.GetCurSel();
	if ( aloc == LB_ERR ) return;
	poDoc = (CGenedocDoc *)m_listProj.GetItemDataPtr(aloc);
	
}

void CSelProject::OnDblclkProjlist() 
{
	// TODO: Add your control notification handler code here
	OnOK();
	
}
