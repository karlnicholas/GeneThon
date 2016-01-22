// exportdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExportDlg dialog

class CExportDlg : public CDialog
{
// Construction
public:
	CExportDlg(CWnd* pParent = NULL);	// standard constructor
	CGenethonDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CExportDlg)
	enum { IDD = IDD_EXPORTDLG };
	CListBox	m_listSequence;
	int		m_Device;
	int		m_SelAllSeq;
	int		m_ExportType;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CExportDlg)
	afx_msg void OnExport();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelallseq();
	afx_msg void OnSellistseq();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
