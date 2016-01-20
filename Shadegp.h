// ShadeGroupp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShadeGroupProperty dialog

class CShadeGroupProperty : public CPropertyPage
{
// Construction
public:
	CShadeGroupProperty();	// standard constructor
	~CShadeGroupProperty();	// standard destructor

// Dialog Data
	//{{AFX_DATA(CShadeGroupProperty)
	enum { IDD = IDD_CONFSHADEGROUP };
	//}}AFX_DATA


// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog(); 
	void ReBuildListBox();

	// Generated message map functions
	//{{AFX_MSG(CShadeGroupProperty)
	//}}AFX_MSG
	afx_msg BOOL OnStyleClicked(UINT nCmdID);
	DECLARE_MESSAGE_MAP()
};
