// pdbdialo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPDBDialog dialog

typedef struct {
	COLORREF rgbText;
	COLORREF rgbBack;
} stcPDBCOLOR;

class CPDBDialog : public CDialog
{
// Construction
public:
	CPDBDialog(CWnd* pParent = NULL);	// standard constructor
	CPtrList m_ColorList;

// Dialog Data
	//{{AFX_DATA(CPDBDialog)
	enum { IDD = IDD_PDBDIALOG };
	CListBox	m_SideColorList;
	BOOL	m_ClearAll;
	BOOL	m_IncludeBase;
	BOOL	m_SafeMode;
	int		m_PDBOffset;
	BOOL	m_DispSidechain;
	CString	m_SideDisp;
	CString	m_ComboBack;
	int		m_ShadeWhich;
	BOOL	m_ExcludeO;
	BOOL	m_GroupSel;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CPDBDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnOK();
	afx_msg void OnDispside();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
