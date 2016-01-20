// proped.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertyEditDlg dialog

class CPropertyEditDlg : public CDialog
{
// Construction
public:
	CPropertyEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertyEditDlg)
	enum { IDD = IDD_PROPEDITDLG };
	CString	m_PropCont;
	CString	m_PropNum;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPropertyEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
