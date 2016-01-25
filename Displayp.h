// displayp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisplayProperty dialog

class CDisplayProperty : public CPropertyPage
{
// Construction
public:
	CDisplayProperty();	// standard constructor
	CGenethonDoc *pDoc;

	// Dialog Data
	//{{AFX_DATA(CDisplayProperty)
	enum { IDD = IDD_CONFDISPLAY };
	int		m_AutoWidth;
	int		m_FixedWidth;
	int		m_ShowTail;
	int		m_PictHeight;
	int		m_PictAscent;
	int		m_PictWidth;
	CString	m_FontWeight;
	int		m_FontSize;
	int		m_MaxNameLength;
	CString	m_strTail;
	CString	m_strLead;
	int		m_SumColInch;
	int		m_Sum2Wid;
	BOOL	m_SumDefDis;
	int		m_SumColInchDis;
	BOOL	m_SumTextBlack;
	BOOL	m_LocAfterSeq;
	BOOL	m_LocAfterName;
	//}}AFX_DATA

// Implementation

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CDisplayProperty)
	afx_msg void OnChangeSumcolinch();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
