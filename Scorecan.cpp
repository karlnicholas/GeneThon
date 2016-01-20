// scorecan.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreCancelDialog dialog


CScoreCancelDialog::CScoreCancelDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CScoreCancelDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScoreCancelDialog)
	m_ShowStatus = "";
	//}}AFX_DATA_INIT
}

void CScoreCancelDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScoreCancelDialog)
	DDX_Text(pDX, IDC_SHOWSTATUS, m_ShowStatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScoreCancelDialog, CDialog)
	//{{AFX_MSG_MAP(CScoreCancelDialog)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CScoreCancelDialog message handlers

void CScoreCancelDialog::OnCancel()
{
	// TODO: Add extra cleanup here
	*m_CancelFlag = 1;
	
//	CDialog::OnCancel();
}

void CScoreCancelDialog::OnOK()
{
	// TODO: Add extra cleanup here
	*m_CancelFlag = 1;
	
//	CDialog::OnCancel();
}

void CScoreCancelDialog::MyCreate()
{
	// TODO: Add extra cleanup here
	Create( CScoreCancelDialog::IDD );
}

int CScoreCancelDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CenterWindow();
	
	return 0;
}

