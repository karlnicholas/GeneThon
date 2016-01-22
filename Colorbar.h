// colorbar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorBar dialog

class CColorBar : public CDialog
{
// Construction
public:
	CColorBar(CWnd* pParent = NULL);	// standard constructor

	COLORREF m_TextColor;
	COLORREF m_BackColor;

// Dialog Data
	//{{AFX_DATA(CColorBar)
	enum { IDD = IDD_COLORBAR };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	CWnd *m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CColorBar)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDblclkColorlist();
	afx_msg void OnChangeback();
	afx_msg void OnChangetext();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
