// htmlpicd.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHTMLPicDlg dialog


CHTMLPicDlg::CHTMLPicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHTMLPicDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHTMLPicDlg)
	m_HTMLType = 0;
	m_FullWeb = 0;
	//}}AFX_DATA_INIT
}

void CHTMLPicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHTMLPicDlg)
	DDX_Radio(pDX, IDC_FULLTABLE, m_HTMLType);
	DDX_Radio(pDX, IDC_FULLWEB, m_FullWeb);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHTMLPicDlg, CDialog)
	//{{AFX_MSG_MAP(CHTMLPicDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHTMLPicDlg message handlers
