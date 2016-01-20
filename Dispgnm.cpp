// dispgnm.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayGroupNameDialog dialog


CDisplayGroupNameDialog::CDisplayGroupNameDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayGroupNameDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisplayGroupNameDialog)
	m_GroupName = "";
	//}}AFX_DATA_INIT
}

void CDisplayGroupNameDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayGroupNameDialog)
	DDX_Text(pDX, IDC_GROUPNAME, m_GroupName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDisplayGroupNameDialog, CDialog)
	//{{AFX_MSG_MAP(CDisplayGroupNameDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDisplayGroupNameDialog message handlers

BOOL CDisplayGroupNameDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
