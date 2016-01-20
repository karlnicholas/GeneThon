// proped.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditDlg dialog


CPropertyEditDlg::CPropertyEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropertyEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropertyEditDlg)
	m_PropCont = "";
	m_PropNum = "";
	//}}AFX_DATA_INIT
}

void CPropertyEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropertyEditDlg)
	DDX_Text(pDX, IDC_PROPEDITCONT, m_PropCont);
	DDX_Text(pDX, IDC_PROPEDITNUM, m_PropNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPropertyEditDlg, CDialog)
	//{{AFX_MSG_MAP(CPropertyEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPropertyEditDlg message handlers
