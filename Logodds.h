// logodds.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogOddsPropPage dialog

class CLogOddsPropPage : public CPropertyPage
{
// Construction
public:
	CLogOddsPropPage();	// standard constructor

	CGenethonDoc *pDoc;
	int m_LogOddsChanged;
	CPtrList m_listCopy;

	COLORREF m_OverlapColor;
	CString m_strLogOddsFile;
	void ColorCopyList();
	void ChangeProjectType(int nType);

// Dialog Data
	//{{AFX_DATA(CLogOddsPropPage)
	enum { IDD = IDD_LOGODDS };
	CComboBox	m_cbOutTab;
	CListBox	m_listLogOdds;
	BOOL	m_iLogOddsNoOv;
	double	m_dLogOddsMin;
	int		m_iLogOddsBestN;
	int		m_iLogOddsMode;
	double	m_dLogOddsTL1;
	double	m_dLogOddsTL2;
	double	m_dLogOddsTL3;
	BOOL	m_iEnabled;
	double	m_dLogOddsMPC;
	int		m_iLogOddsOutTab;
	int		m_iLogOddsBack;
	double	m_dLogOddsStA;
	double	m_dLogOddsStC;
	double	m_dLogOddsStG;
	double	m_dLogOddsStT;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void ReBuildListBox();
	int m_DialogInited;
	int m_ProjectType;

	// Generated message map functions
	//{{AFX_MSG(CLogOddsPropPage)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnBackcolor();
	afx_msg void OnDelete();
	afx_msg void OnEdit();
	afx_msg void OnMeme();
	afx_msg void OnTextcolor();
	afx_msg void OnDblclkMotiflist();
	virtual BOOL OnInitDialog();
	afx_msg void OnOverlap();
	afx_msg void OnSelchangeMotiflist();
	afx_msg void OnEnabled();
	afx_msg void OnSelchangeOuttab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
