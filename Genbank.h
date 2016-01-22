// genbank.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenbank dialog

class CGenbank : public CDialog
{
// Construction
public:
	CGenbank(CWnd* pParent = NULL);	// standard constructor

	CString LOCUS;
	CString ACCESSION;
	CString NID;
	CString PID;
// Dialog Data
	//{{AFX_DATA(CGenbank)
	enum { IDD = IDD_GENBANK };
	int		m_Locus;
	int		m_Trans;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGenbank)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
