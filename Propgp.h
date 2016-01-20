// PropGp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyGroupProperty dialog

class CPropertyGroupProperty : public CPropertyPage
{
// Construction
public:
	CPropertyGroupProperty();	// standard constructor
	~CPropertyGroupProperty();	// standard destructor

	void ResetData();

// Dialog Data
	//{{AFX_DATA(CPropertyGroupProperty)
	enum { IDD = IDD_CONFPROPERTY };
	CButton	m_PropLevel3But;
	CButton	m_PropLevel2But;
	CButton	m_PropLevel1But;
	CListBox	m_ListBox;
	int		m_PropStyle;
	//}}AFX_DATA

	CPtrArray m_PropertyArray[3]; // Hoding a list of ShadePairStruct's
	int m_CurrentPropLevel;
	CGenethonDoc *pDoc;
	void ReBuildListBox(int PropLevel);
	
// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog(); 

	int m_DialogInited;

	// Generated message map functions
	//{{AFX_MSG(CPropertyGroupProperty)
	afx_msg void OnPropdel();
	afx_msg void OnPropedit();
	afx_msg void OnDblclkPropertylist();
	afx_msg void OnProplevel1();
	afx_msg void OnProplevel2();
	afx_msg void OnProplevel3();
	afx_msg void OnPropnew();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnProptextcolor();
	afx_msg void OnPropbkcolor();
	afx_msg void OnLeveldefaults();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
