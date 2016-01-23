// importty.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportTypeDlg dialog

class CImportTypeDlg : public CDialog
{
// Construction
public:
	CImportTypeDlg(CWnd* pParent = NULL);	// standard constructor
	CGenethonDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CImportTypeDlg)
	enum { IDD = IDD_IMPORTTYPE };
	int		m_ImportType;
	int		m_Device;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CImportTypeDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
