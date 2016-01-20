// seqinp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqInput dialog

class CSeqInput : public CDialog
{
// Construction
public:
	CSeqInput(CWnd* pParent = NULL);	// standard constructor

	CString m_DataString;
// Dialog Data
	//{{AFX_DATA(CSeqInput)
	enum { IDD = IDD_SEQUENCEINPUT };
	CEdit	m_SeqInput;
	CString	m_SeqName;
	CString	m_Descr;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSeqInput)
	virtual void OnOK();
	afx_msg void OnPaste();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
