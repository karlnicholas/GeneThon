// grppsht.cpp : implementation of the CGroupPropertySheet class
//

#include "stdafx.h"

IMPLEMENT_DYNAMIC(CGroupPropertySheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CGroupPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CGroupPropertySheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CGroupPropertySheet::CGroupPropertySheet(CWnd* pWndParent)
	: CPropertySheet(AFX_IDS_APP_TITLE, pWndParent)
{
	AddPage( &m_GroupPropPage );
	AddPage( &m_ShadeModePage );
	AddPage( &m_PropertyGroupPage );
	AddPage( &m_StructurePage );
	AddPage( &m_IdentityPage );

	m_SetActive = FALSE;
	m_SetActivePage = NULL;

}

CGroupPropertySheet::~CGroupPropertySheet()
{
}


int CGroupPropertySheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Add the preview window to the property sheet.
	// Get New DisplayVars ...

/*
	if ( !m_SetActive ) {
		if ( m_SetActivePage != 0 ) {
			SetActivePage ( m_SetActivePage );
		}
		m_SetActive = TRUE;
	}
*/

	int nReturn;
	if ((nReturn = CPropertySheet::OnCreate(lpCreateStruct))
		!= 0)
		return nReturn;

	CenterWindow();
	return 0;
}


void CGroupPropertySheet::OnApplyNow()
{
	CMDIFrameWnd* pMDIFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	ASSERT(pMDIFrameWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
	CView* pView = pMDIFrameWnd->MDIGetActive()->GetActiveView();
//	pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
//	m_stylePage.SetModified(FALSE);
//	m_colorPage.SetModified(FALSE);
}

void CGroupPropertySheet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if ( !m_SetActive ) {
		if ( m_SetActivePage != NULL ) {
			SetActivePage ( m_SetActivePage );
		} else if ( !m_NumGroups ) {
			RemovePage( &m_ShadeModePage );
			RemovePage( &m_PropertyGroupPage );
			RemovePage( &m_StructurePage );
			RemovePage( &m_IdentityPage );
		}
		m_SetActive = TRUE;
	}

	CPropertySheet::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
