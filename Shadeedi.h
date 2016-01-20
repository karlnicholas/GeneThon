// shadeedi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShadeEditDlg dialog

class CShadeEditDlg : public CDialog
{
// Construction
public:
	CShadeEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShadeEditDlg)
	enum { IDD = IDD_SHADEEDITDLG };
	CString	m_ShadeCont;
	CString	m_ShadeNum;
	//}}AFX_DATA


// Overrides
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShadeEditDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
