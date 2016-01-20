// refiltdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReFiltDlg dialog

class CReFiltDlg : public CDialog
{
// Construction
public:
	CReFiltDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CReFiltDlg)
	enum { IDD = IDD_REFILT };
	CString	m_Exclude;
	CString	m_Include;
	int		m_Maxlen;
	int		m_Minlen;
	BOOL	m_NonAmbig;
	BOOL	m_Palin;
	int		m_Occur;
	BOOL	m_ExclDup;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CReFiltDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
