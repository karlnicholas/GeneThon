// propsht.cpp : implementation of the CModalDisplayPropSheet class
//

#include "stdafx.h"

IMPLEMENT_DYNAMIC(CModalDisplayPropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CModalDisplayPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModalDisplayPropSheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModalDisplayPropSheet::CModalDisplayPropSheet(CWnd* pWndParent)
	: CPropertySheet(AFX_IDS_APP_TITLE, pWndParent)
{
	AddPage( &m_DisplayPage );
	AddPage( &m_PrintPage );
	m_SetActive = FALSE;
	m_SetActivePage = NULL;
}

int CModalDisplayPropSheet::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	// Add the preview window to the property sheet.

	int nReturn;
	if ((nReturn = CPropertySheet::OnCreate(lpCreateStruct))
		!= 0)
		return nReturn;

	CenterWindow();
	return 0;
}


void CModalDisplayPropSheet::OnApplyNow()
{
	CMDIFrameWnd* pMDIFrameWnd = (CMDIFrameWnd*)AfxGetMainWnd();
	ASSERT(pMDIFrameWnd->IsKindOf(RUNTIME_CLASS(CMDIFrameWnd)));
	CView* pView = pMDIFrameWnd->MDIGetActive()->GetActiveView();
//	pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
//	m_stylePage.SetModified(FALSE);
//	m_colorPage.SetModified(FALSE);
}


void CModalDisplayPropSheet::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	// TODO: Add your message handler code here
	if ( !m_SetActive ) {
		if ( m_SetActivePage != NULL ) {
			SetActivePage ( m_SetActivePage );
		}
		m_SetActive = TRUE;
	}

	CPropertySheet::OnShowWindow(bShow, nStatus);
	
}
