// RepDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRepDlg dialog

class CRepDlg : public CPropertyPage
{
// Construction
public:
	CRepDlg();	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRepDlg)
	enum { IDD = IDD_REPDLG };
	BOOL	m_RepExactMatch;
	BOOL	m_RepJuxtaposition;
	BOOL	m_RepAlignedGaps;
	BOOL	m_RepAbsoluteVal;
	BOOL	m_RepPercentVal;
	int		m_RepOutMatrix;
	int		m_RepLabelSingle;
	int		m_RepLabelTop;
	BOOL	m_RepIncAA;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CRepDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
