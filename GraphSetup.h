// GraphSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphSetup dialog

class CGraphSetup : public CDialog
{
// Construction
public:
	CGraphSetup(CWnd* pParent = NULL);   // standard constructor

	LOGFONT m_logFont;

// Dialog Data
	//{{AFX_DATA(CGraphSetup)
	enum { IDD = IDD_GRAPHSETUP };
	float	m_PageHeight;
	float	m_PageWidth;
	int		m_Set1Count;
	int		m_Set2Count;
	int		m_TSide;
	CString	m_ChartTitle;
	int		m_xChtTitPct;
	int		m_LineWidth;
	double	m_RoundingFactor;
	int		m_xXAxTPct;
	int		m_xBorderPct;
	int		m_yBorderPct;
	int		m_yYAxTPct;
	CString	m_XAxisTitle;
	CString	m_YAxisTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphSetup)
	afx_msg void OnChgfont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeXborderpct2();
};
