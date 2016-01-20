// CGroupProp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupProp dialog

class CGroupProp : public CPropertyPage
{
// Construction
public:
	CGroupProp();	// standard constructor
	~CGroupProp();	// standard destructor
	
	CGenethonDoc *pDoc;

	CString m_CurrentGroupName;
	
	CString m_InitSimilarities;

// Dialog Data
	//{{AFX_DATA(CGroupProp)
	enum { IDD = IDD_GROUPPROP };
	CComboBox	m_PCRSimilarities;
	CButton	m_DeleteGroup;
	CButton	m_RemoveSeq;
	CButton	m_SeqAdd;
	CButton	m_GroupColor;
	CComboBox	m_GroupCombo;
	CListBox	m_SequenceList;
	BOOL	m_ModifyAll;
	BOOL	m_ColorSeqNames;
	double	m_GroupConsLevel;
	double	m_PCRLevel;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void SetDisplayGroup( const CString& GroupName );

	typedef struct sGroupDisplay {
		int	DisplayGroup;
		COLORREF TextColor;
		COLORREF BkColor;
		CGeneSegment *pCGSeg;
	} GroupDisplay;

	void SetSeqColors();
	int m_SaveCurSel;


	// Generated message map functions
	//{{AFX_MSG(CGroupProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnNewgroup();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnGrouptextcolor();
	afx_msg void OnGroupbackcolor();
	afx_msg void OnDblclkSeqlist();
	afx_msg void OnSelchangeGroupcombo();
	afx_msg void OnDestroy();
	afx_msg void OnModifyall();
	afx_msg void OnSelchangeSeqlist();
	afx_msg void OnSeqadd();
	afx_msg void OnSelcancelSeqlist();
	afx_msg void OnRemoveseq();
	afx_msg void OnDeletegroup();
	afx_msg void OnColorseqnames();
	afx_msg void OnChangeGroupconslevel();
	afx_msg void OnChangeGrouppcrlevel();
	afx_msg void OnEditchangeGrouppcrsim();
	afx_msg void OnSelchangeGrouppcrsim();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()

};
