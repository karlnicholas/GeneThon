// propsht.h : interface of the CModalDisplayPropSheet class
//
/////////////////////////////////////////////////////////////////////////////

class CModalDisplayPropSheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CModalDisplayPropSheet)
	CModalDisplayPropSheet(CWnd* pWndParent = NULL);

// Attributes
	CDisplayProperty m_DisplayPage;
	CPrintProperty m_PrintPage;
	CShadeModeProperty m_ShadeModePage;
	CRepDlg m_ReportPage;
	CPropertyGroupProperty m_PropertyGroupPage;
	CSearchPropPage m_SearchPropPage;
	CStructurePropDialog m_StructurePage;
	CChemPropProperty m_PhysioChemPage;
	CConfIdent m_IdentityPage;
	CLogOddsPropPage m_LogOddsPropPage;
	CScoreTableProperty m_ScoreTablePage;

	CPropertyPage* m_SetActivePage;

// Operations

protected:
	//{{AFX_MSG(CModalDisplayPropSheet)
	afx_msg void OnApplyNow();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_SetActive;


};
