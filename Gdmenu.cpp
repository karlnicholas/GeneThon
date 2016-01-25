
#include "stdafx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


void CGenethonDoc::OnGeneview()
{
	// TODO: Add your command handler code here
	if ( m_pGeneView == NULL ) {
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenGeneView();
	} else {
		m_pGeneView->GetParentFrame()->ActivateFrame();
		m_pGeneView->Invalidate();
	}
	
}

void CGenethonDoc::OnSummaryview()
{
	// TODO: Add your command handler code here
	if ( pGSFiller != NULL ) {
		// TODO: Add your command handler code here
		if ( m_pSummaryView == NULL ) {
			((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenSummaryView();
		} else {
			m_pSummaryView->GetParentFrame()->ActivateFrame();
			m_pSummaryView->Invalidate();
		}
	}
}

void CGenethonDoc::OnUpdateSummaryview(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(	pGSFiller != NULL );
}

void CGenethonDoc::OnFileexport() 
{
	// TODO: Add your command handler code here
	SequenceExport();
}


void CGenethonDoc::OnGeneloadini()
{

	GetIniDefaults();
	
	SetModifiedFlag();
}

void CGenethonDoc::OnGenereportview() 
{
	
	if ( m_pTextView == NULL ) {
	
		((CMainFrame *)(AfxGetApp()->m_pMainWnd))->OpenTextView();
	} else {

		m_pTextView->GetParentFrame()->ActivateFrame();
		m_pTextView->Invalidate();
	}
	
}


