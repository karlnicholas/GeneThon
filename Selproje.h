// selproje.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelProject dialog

class CSelProject : public CDialog
{
// Construction
public:
	CSelProject(CWnd* pParent = NULL);	// standard constructor
	CGenethonDoc *pDoc;
	CGenethonDoc *poDoc;

// Dialog Data
	//{{AFX_DATA(CSelProject)
	enum { IDD = IDD_SELPROJ };
	CListBox	m_listProj;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSelProject)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProjlist();
	afx_msg void OnDblclkProjlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
