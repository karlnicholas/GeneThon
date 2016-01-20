// phylodlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog dialog

class CPhyloGenDialog : public CDialog
{
// Construction
public:
	CPhyloGenDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPhyloGenDialog)
	enum { IDD = IDD_PHYLOGEN };
	CEdit	m_PhyloEdit;
	CString	m_ParseString;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	void GetParseFile( const CString& FileName );
	

	// Generated message map functions
	//{{AFX_MSG(CPhyloGenDialog)
	afx_msg void OnPhyloexport();
	afx_msg void OnPhyloimport();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPhylocopy();
	afx_msg void OnPhylopaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
