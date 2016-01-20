// shadeedi.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShadeEditDlg dialog


CShadeEditDlg::CShadeEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShadeEditDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShadeEditDlg)
	m_ShadeCont = _T("");
	m_ShadeNum = _T("");
	//}}AFX_DATA_INIT
}


void CShadeEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShadeEditDlg)
	DDX_Text(pDX, IDC_SHADEEDITCONT, m_ShadeCont);
	DDX_Text(pDX, IDC_SHADEEDITNUM, m_ShadeNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShadeEditDlg, CDialog)
	//{{AFX_MSG_MAP(CShadeEditDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CShadeEditDlg message handlers
