// showtabl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowTableDialog dialog

class CShowTableDialog : public CDialog
{
// Construction
public:
	CShowTableDialog(CWnd* pParent = NULL);	// standard constructor
	
	CString m_ShowEditString;

// Dialog Data
	//{{AFX_DATA(CShowTableDialog)
	enum { IDD = IDD_SHOWTABLE };
	CEdit	m_ShowEdit;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CShowTableDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowtablecopy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
