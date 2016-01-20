// seqseldl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqSelDlg dialog

class CSeqSelDlg : public CDialog
{
// Construction
public:
	CSeqSelDlg(CWnd* pParent = NULL);	// standard constructor

	CGenethonDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CSeqSelDlg)
	enum { IDD = IDD_SEQSEL };
	CComboBox	m_cbOutTab;
	CListBox	m_listSequence;
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

	// Generated message map functions
	//{{AFX_MSG(CSeqSelDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeOuttab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
