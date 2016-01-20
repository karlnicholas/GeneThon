
class CPhyloMDIChildWnd: public CMDIChildWnd
{
	DECLARE_DYNCREATE(CPhyloMDIChildWnd)

//	CDialogBar m_PhyloBar;
	CToolBar m_PhyloBar;
public:

protected:

public:

	// Generated message map functions
	//{{AFX_MSG(CPhyloMDIChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
};

