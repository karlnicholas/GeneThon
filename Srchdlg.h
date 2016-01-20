// srchdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSrchDlg dialog

class CSrchDlg : public CDialog
{
// Construction
public:
	CSrchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSrchDlg)
	enum { IDD = IDD_SRCHDLG };
	CString	m_Descrip;
	CString	m_Motif;
	CString	m_Name;
	BOOL	m_iEnabled;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSrchDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
