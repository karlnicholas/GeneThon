// seqdetdi.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqDetDialog dialog

class CSeqDetDialog : public CDialog
{
// Construction
public:
	CSeqDetDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeqDetDialog)
	enum { IDD = IDD_SEQDETAILS };
	CString	m_SeqName;
	CString	m_Instruct;
	DWORD	m_TextStart;
	CString	m_Descr;
	//}}AFX_DATA

	int m_NameChanged;
	int m_DescrChanged;
	int m_StartChanged;

// Overrides
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeqDetDialog)
	afx_msg void OnChangeSeqdetname();
	afx_msg void OnChangeTextstart();
	afx_msg void OnChangeDescr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
