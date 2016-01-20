// titlingf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTitlingFDialog dialog

class CTitlingFDialog : public CDialog
{
// Construction
public:
	CTitlingFDialog(CWnd* pParent = NULL);	// standard constructor
	
	CString m_CommentText;
	int m_CTChanged;
	int m_ICChanged;		// Initial Creation

// Dialog Data
	//{{AFX_DATA(CTitlingFDialog)
	enum { IDD = IDD_TITLINGF };
	CEdit	m_CommentEdit;
	CString	m_ExtendGap;
	CString	m_OpenGap;
	CString	m_Program;
	CString	m_ScoreMatrix;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CTitlingFDialog)
	afx_msg void OnChangeTitleedit();
	afx_msg void OnChangeTitleextendgap();
	afx_msg void OnChangeTitleopengap();
	afx_msg void OnChangeTitleprogram();
	afx_msg void OnChangeTitlescore();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
