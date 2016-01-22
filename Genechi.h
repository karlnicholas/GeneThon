
class CGeneMDIChildWnd: public CMDIChildWnd
{
	DECLARE_DYNCREATE(CGeneMDIChildWnd)

	CToolBar m_GeneBar;
public:

protected:

public:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs );
	
	// Generated message map functions
	//{{AFX_MSG(CGeneMDIChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	

};

