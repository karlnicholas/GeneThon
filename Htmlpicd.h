// htmlpicd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHTMLPicDlg dialog

class CHTMLPicDlg : public CDialog
{
// Construction
public:
	CHTMLPicDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHTMLPicDlg)
	enum { IDD = IDD_HTMLPICK };
	int		m_HTMLType;
	int		m_FullWeb;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CHTMLPicDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
