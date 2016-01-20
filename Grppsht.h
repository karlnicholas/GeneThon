// grppsht.h : interface of the CGroupPropertySheet class
//
/////////////////////////////////////////////////////////////////////////////

class CGroupPropertySheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CGroupPropertySheet)
	CGroupPropertySheet(CWnd* pWndParent = NULL);
	~CGroupPropertySheet();

// Attributes
	CGroupProp		m_GroupPropPage;

	CShadeModeProperty m_ShadeModePage;
	CPropertyGroupProperty m_PropertyGroupPage;
	CStructurePropDialog	m_StructurePage;
	CConfIdent			m_IdentityPage;

	CPropertyPage *m_SetActivePage;

	int m_SetActive;
	int m_NumGroups;
	
// Operations

protected:
	//{{AFX_MSG(CGroupPropertySheet)
	afx_msg void OnApplyNow();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
