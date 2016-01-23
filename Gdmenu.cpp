
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

void CGenethonDoc::OnFileimport() 
{
	// TODO: Add your command handler code here
	SequenceImport();

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


void CGenethonDoc::OnShowmanshade()
{
	m_UserVars.m_ShowManShade = !m_UserVars.m_ShowManShade;
}

void CGenethonDoc::OnUpdateShowman(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowManShade );

}

void CGenethonDoc::OnShowcomments()
{
	m_UserVars.m_ShowComments = !m_UserVars.m_ShowComments;
}

void CGenethonDoc::OnUpdateShowcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck( m_UserVars.m_ShowComments );

}

void CGenethonDoc::OnClearcomments() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			tCGSeg->ClearComments();
		}
	}

	SetModifiedFlag();
}

void CGenethonDoc::OnClearmanshade() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			tCGSeg->ClearShades();
		}
	}

	SetModifiedFlag();
}


void CGenethonDoc::OnSelectarrseq() 
{
	// TODO: Add your command handler code here
	CSelArrSeq tDlg;
	tDlg.pDoc = this;
	tDlg.DoModal();
	UpdateAllViews(NULL);
}


void CGenethonDoc::OnComplimentsel() 
{
	// TODO: Add your command handler code here
	if ( pGSFiller == NULL ) return;
		
	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() == LINESEQUENCE ) {
			if ( tCGSeg->GetArrangeFlag() ) {
				tCGSeg->SetArrangeFlag(0);
			} else {
				tCGSeg->SetArrangeFlag(1);
			}
		}
	}

	UpdateAllViews(NULL);
	
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


