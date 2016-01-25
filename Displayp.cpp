// displayp.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty dialog


CDisplayProperty::CDisplayProperty() : CPropertyPage(CDisplayProperty::IDD)
{
	//{{AFX_DATA_INIT(CDisplayProperty)
	m_AutoWidth = -1;
	m_FixedWidth = 0;
	m_ShowTail = -1;
	m_PictHeight = 0;
	m_PictAscent = 0;
	m_PictWidth = 0;
	m_FontWeight = "";
	m_FontSize = 0;
	m_MaxNameLength = 0;
	m_strTail = _T("");
	m_strLead = _T("");
	m_SumColInch = 0;
	m_Sum2Wid = -1;
	m_SumDefDis = FALSE;
	m_SumColInchDis = 0;
	m_SumTextBlack = FALSE;
	m_LocAfterSeq = TRUE;
	m_LocAfterName = FALSE;
	//}}AFX_DATA_INIT
}

void CDisplayProperty::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisplayProperty)
	DDX_Radio(pDX, IDC_GENEAUTOWIDTH, m_AutoWidth);
	DDX_Text(pDX, IDC_EDITWIDTH, m_FixedWidth);
	DDV_MinMaxInt(pDX, m_FixedWidth, 10, 1000000);
	DDX_Radio(pDX, IDC_SEQINDON, m_ShowTail);
	DDX_Text(pDX, IDC_PICTHEIGHT, m_PictHeight);
	DDV_MinMaxInt(pDX, m_PictHeight, -9, 9);
	DDX_Text(pDX, IDC_PICTASCENT, m_PictAscent);
	DDV_MinMaxInt(pDX, m_PictAscent, -9, 9);
	DDX_Text(pDX, IDC_PICTWIDTH, m_PictWidth);
	DDV_MinMaxInt(pDX, m_PictWidth, -9, 9);
	DDX_CBString(pDX, IDC_FONTWEIGHT, m_FontWeight);
	DDX_Text(pDX, IDC_EDITFONTPOINTS, m_FontSize);
	DDX_Text(pDX, IDC_MAXNAME, m_MaxNameLength);
	DDV_MinMaxInt(pDX, m_MaxNameLength, 0, 50);
	DDX_Text(pDX, IDC_INDSEP, m_strTail);
	DDV_MaxChars(pDX, m_strTail, 10);
	DDX_Text(pDX, IDC_NAMESEP, m_strLead);
	DDV_MaxChars(pDX, m_strLead, 10);
	DDX_Text(pDX, IDC_SUMCOLINCH, m_SumColInch);
	DDX_Radio(pDX, IDC_COL2WID11, m_Sum2Wid);
	DDX_Check(pDX, IDC_SUMDEFDIS, m_SumDefDis);
	DDX_Text(pDX, IDC_SUMCOLINCHDIS, m_SumColInchDis);
	DDX_Check(pDX, IDC_SUMTEXTBLACK, m_SumTextBlack);
	DDX_Check(pDX, IDC_LOCAFTERSEQ, m_LocAfterSeq);
	DDX_Check(pDX, IDC_LOCAFTERNAME, m_LocAfterName);
	//}}AFX_DATA_MAP
}

BOOL CDisplayProperty::OnStyleClicked(UINT /*nCmdID*/)
{
	// The CStylePage property page is used for both the
	// CModalShapePropSheet and the CModelessShapePropSheet.
	// Both these versions of the property sheet share a common
	// feature that they immediately update a shape.  In the
	// case of CModalShapePropSheet, the shape is in the preview
	// window.  In the case of CModelessShapePropSheet, the shape
	// is the currently selected shape in the view.

	CPropertySheet* pPropertySheet = (CPropertySheet*)GetParent();

	if (pPropertySheet->IsKindOf(RUNTIME_CLASS(CModalDisplayPropSheet)))
	{
		UpdateData();
//		((CModalDisplayPropSheet*)pPropertySheet)->UpdateShapePreview();
		SetModified(); // enable Apply Now button
	}
	return TRUE;
}

BEGIN_MESSAGE_MAP(CDisplayProperty, CPropertyPage)
	//{{AFX_MSG_MAP(CDisplayProperty)
	ON_EN_CHANGE(IDC_SUMCOLINCH, OnChangeSumcolinch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty message handlers


BOOL CDisplayProperty::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	OnChangeSumcolinch();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CDisplayProperty::OnChangeSumcolinch() 
{
	// TODO: Add your control notification handler code here

//	UpdateData();
	CWnd *pWnd = GetDlgItem( IDC_SUMCOLINCH );
	CString strVal;
	pWnd->GetWindowText( strVal );
	int SumColInch = atoi ( (const char *)strVal );
	if ( SumColInch == 0 ) return;

	CDC *cDC = GetDC();
	int PixInch = cDC->GetDeviceCaps( LOGPIXELSX );		// Pixels Per Inch

	int SumWidth = PixInch / SumColInch;
	if ( SumWidth == 0 ) SumWidth = 1;
	PixInch = PixInch / SumWidth;

	char str[20];
	_itoa( PixInch, str, 10 );

	pWnd = GetDlgItem( IDC_SUMCOLINCHDIS );
	pWnd->SetWindowText( str );
	pWnd->Invalidate();
	ReleaseDC(cDC);
//	UpdateData(FALSE);
	
}
