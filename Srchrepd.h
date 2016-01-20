// srchrepd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrchRepDlg dialog

class CSrchRepDlg : public CDialog
{
// Construction
public:
	CSrchRepDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSrchRepDlg)
	enum { IDD = IDD_SRCHREP };
	BOOL	m_CutSites;
	BOOL	m_GroupFrag;
	BOOL	m_SortedCut;
	BOOL	m_SortedFrag;
	UINT	m_SimPer;
	UINT	m_UniqPer;
	UINT	m_UniqFragPer;
	BOOL	m_UniqFrag;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSrchRepDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
