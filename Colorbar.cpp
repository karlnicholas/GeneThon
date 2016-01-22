// colorbar.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorBar dialog


CColorBar::CColorBar(CWnd* pParent)
	: CDialog(CColorBar::IDD, pParent)
{
	m_pParent = pParent;
	//{{AFX_DATA_INIT(CColorBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CColorBar::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBar)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CColorBar, CDialog)
	//{{AFX_MSG_MAP(CColorBar)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHANGEBACK, OnChangeback)
	ON_BN_CLICKED(IDC_CHANGETEXT, OnChangetext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CColorBar message handlers

BOOL CColorBar::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CGenethonDoc *pDoc = ((CGenethonView *)m_pParent)->GetDocument();
	
	CenterWindow();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CColorBar::OnOK()
{
	// TODO: Add extra validation here

	CDialog::OnOK();

	// m_ShadeLevel = m_ColorList.GetCurSel();
}


void CColorBar::OnDblclkColorlist()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CColorBar::OnChangeback() 
{
	// TODO: Add your control notification handler code here
	CColorDialog    tDlg(m_BackColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	// m_ColorChanged = 1;
        
	m_BackColor = tDlg.GetColor();

	RedrawWindow();
	
}

void CColorBar::OnChangetext() 
{
	// TODO: Add your control notification handler code here
	CColorDialog    tDlg(m_TextColor);
        
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
        
	// m_ColorChanged = 1;
        
	m_TextColor = tDlg.GetColor();

	RedrawWindow();
	
	
}

