// scorecan.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoreCancelDialog dialog

class CScoreCancelDialog : public CDialog
{
// Construction
public:
	CScoreCancelDialog(CWnd* pParent = NULL);	// standard constructor
	void MyCreate();

	int *m_CancelFlag;
	int *m_ScoreWaitCursor;

// Dialog Data
	//{{AFX_DATA(CScoreCancelDialog)
	enum { IDD = IDD_SCORECANDIALOG };
	CString	m_ShowStatus;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CScoreCancelDialog)
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
