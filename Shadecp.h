// ShadeColorp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShadeColorProperty dialog

class CShadeColorProperty : public CPropertyPage
{
// Construction
public:
	CShadeColorProperty();	// standard constructor



// Dialog Data
	//{{AFX_DATA(CShadeColorProperty)
	enum { IDD = IDD_CONFSHADECOLOR };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();

	// Generated message map functions
	//{{AFX_MSG(CShadeColorProperty)
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
