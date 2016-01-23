// GraphSetup.cpp : implementation file
//

#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup dialog


CGraphSetup::CGraphSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CGraphSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGraphSetup)
	m_PageHeight = 0.0f;
	m_PageWidth = 0.0f;
	m_Set1Count = 0;
	m_Set2Count = 0;
	m_TSide = -1;
	m_ChartTitle = _T("");
	m_xChtTitPct = 0;
	m_LineWidth = 0;
	m_RoundingFactor = 0.0;
	m_xXAxTPct = 0;
	m_xBorderPct = 0;
	m_yBorderPct = 0;
	m_yYAxTPct = 0;
	m_XAxisTitle = _T("");
	m_YAxisTitle = _T("");
	//}}AFX_DATA_INIT
}


void CGraphSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGraphSetup)
	DDX_Text(pDX, IDC_PAGEHEIGHT, m_PageHeight);
	DDX_Text(pDX, IDC_PAGEWIDTH, m_PageWidth);
	DDX_Text(pDX, IDC_CHARTTITLE, m_ChartTitle);
	DDX_Text(pDX, IDC_CHARTTITLEPCT, m_xChtTitPct);
	DDX_Text(pDX, IDC_LINEWIDTH, m_LineWidth);
	DDX_Text(pDX, IDC_XAXISROUNDING, m_RoundingFactor);
	DDX_Text(pDX, IDC_XAXISTITLEPCT, m_xXAxTPct);
	DDX_Text(pDX, IDC_XBORDERPCT, m_xBorderPct);
	DDX_Text(pDX, IDC_YBORDERPCT, m_yBorderPct);
	DDX_Text(pDX, IDC_YAXISTITLEPCT, m_yYAxTPct);
	DDX_Text(pDX, IDC_XAXISTITLE, m_XAxisTitle);
	DDX_Text(pDX, IDC_YAXISTITLE, m_YAxisTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGraphSetup, CDialog)
	//{{AFX_MSG_MAP(CGraphSetup)
	ON_BN_CLICKED(IDC_CHGFONT, OnChgfont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup message handlers

void CGraphSetup::OnChgfont() 
{
	// TODO: Add your control notification handler code here
	CClientDC dc(NULL);
	LOGFONT lf = m_logFont;
	lf.lfHeight = -::MulDiv(-lf.lfHeight, dc.GetDeviceCaps(LOGPIXELSY), 72);
	CFontDialog dlg(&lf);
	// dlg.m_cf.rgbColors = m_crText;
	if (dlg.DoModal() == IDOK)
	{
		lf.lfHeight = -::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY));
		// m_crText = dlg.GetColor();
		m_logFont = lf;
	}
}


void CGraphSetup::OnEnChangeXborderpct2()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
