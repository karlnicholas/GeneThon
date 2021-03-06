
#include "stdafx.h"
#include <ctype.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int CGenethonDoc::SequenceExport(int Selected) 
{
	// TODO: Add your command handler code here

	if ( pGSFiller == NULL ) return 0;

	CExportDlg typeDlg;

	typeDlg.pDoc = this;

	typeDlg.DoModal();

	return 1;

}

int
CGenethonDoc::GetPhylipFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	if ( !ReadPhylipIFile( &CommentList, &SequenceList, PathName ) ) {
		while ( !CommentList.IsEmpty() ) {
			delete (CString *)CommentList.RemoveHead();
		}
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

	SeqNameStruct *tSNS = (SeqNameStruct *)SequenceList.GetHead();
	gMaxStrSize = tSNS->Len;

	return ProcessRows( CommentList, SequenceList, Append );

}


int
CGenethonDoc::GetPIRFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	if ( !ReadPIRFile( &CommentList, &SequenceList, PathName ) ) {
		while ( !CommentList.IsEmpty() ) {
			delete (CString *)CommentList.RemoveHead();
		}
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

//	gMaxStrSize;

	return ProcessRows( CommentList, SequenceList, Append );

}

int
CGenethonDoc::GetALNFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	if ( !ReadALNFile( &CommentList, &SequenceList, PathName ) ) {
		while ( !CommentList.IsEmpty() ) {
			delete (CString *)CommentList.RemoveHead();
		}
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}


	SeqNameStruct *tSNS = (SeqNameStruct *)SequenceList.GetHead();
	gMaxStrSize = tSNS->Len;

	return ProcessRows( CommentList, SequenceList, Append );

}

int
CGenethonDoc::GetMSFFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	if ( !ReadMSFFile( &CommentList, &SequenceList, PathName ) ) {
		while ( !CommentList.IsEmpty() ) {
			delete (CString *)CommentList.RemoveHead();
		}
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}


	SeqNameStruct *tSNS = (SeqNameStruct *)SequenceList.GetHead();
	gMaxStrSize = tSNS->Len;

	return ProcessRows( CommentList, SequenceList, Append );

}

int 
CGenethonDoc::GetFasNTFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	gMaxStrSize = 0L;

	if ( !ReadFasNTFile ( &CommentList, &SequenceList, PathName ) ) {
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

	return ProcessRows( CommentList, SequenceList, Append );
}

int 
CGenethonDoc::GetFastaFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	gMaxStrSize = 0L;

	if ( !ReadFastaFile ( &CommentList, &SequenceList, PathName ) ) {
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

	return ProcessRows( CommentList, SequenceList, Append );
}

int 
CGenethonDoc::GetTextFile( CString PathName, int Append, 
	const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	gMaxStrSize = 0L;

	if ( !ReadTextFile ( &CommentList, &SequenceList, PathName, SeqName, SeqWeight, TextStart, Descr, IUPAC ) ) {
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

	return ProcessRows( CommentList, SequenceList, Append );
}

int 
CGenethonDoc::GetGenbankFile( CString PathName, int Append )
{

	CPtrList CommentList;
	CPtrList SequenceList;

	gMaxStrSize = 0L;

	if ( !ReadGenbankFile ( &CommentList, &SequenceList, PathName ) ) {
		while ( !SequenceList.IsEmpty() ) {
			delete (SeqNameStruct *)SequenceList.RemoveHead();
		}
		return 0;
	}

	return ProcessRows( CommentList, SequenceList, Append );
}

int
CGenethonDoc::ProcessRows( CPtrList& CommentList, CPtrList& SequenceList, int Append )
{
	CGeneSegment *SaveCGSeg;

	if ( pGSFiller == NULL ) {
		Append = 0;
	}

	if ( !Append ) {

		pGSFiller = new CGSFiller();
		if ( pGSFiller == 0 ) {
			AfxMessageBox("GetMSFFile:new Fail 1" );
			pGSFiller = NULL;
			return 0;
		}

		// Create Score Row and Comment Row ..
		if ( ! CreateTopRows() ) return 0;
		
	} else {

		// Check Sizes against what already there ...
  		SaveCGSeg = (CGeneSegment *)pGSFiller->SegDataList.RemoveTail();

	}


	if ( !AppendDataRows(SequenceList, Append) ) return 0;

	if ( !Append ) {	
	
		if ( !CreateBottomRows() ) return 0;

		pGSFiller->pGeneSegParent = NULL;
		
		// move comments into GFiller head list
		POSITION tPos = CommentList.GetHeadPosition();
		while (tPos != NULL ) {
			CString * tStr = (CString *)CommentList.GetNext(tPos);
			pGSFiller->AddHeader( tStr );
		}
	} else {
		pGSFiller->AddData( SaveCGSeg );
		
		// Delete comments 
		POSITION tPos = CommentList.GetHeadPosition();
		while (tPos != NULL ) {
			CString * tStr = (CString *)CommentList.GetNext(tPos);
			delete tStr;
		}
	}

	if ( !ReSizeRows() ) return 0;


	// Header List must have a string in it with "MSF:" and ".."
	int iFind = 0;
	POSITION tPos = pGSFiller->SegHeaderList.GetHeadPosition();
	while (tPos != NULL ) {
		CString *strT = (CString *)pGSFiller->SegHeaderList.GetNext(tPos);
		if ( strT->Find( "MSF:") != -1 && strT->Find( "..") != -1 ) {
			iFind = 1;
			break;
		}
	}

	if ( !iFind ) {
		pGSFiller->AddHeader( new CString("MSF: Main Filler ..") );
	}
		

	return 1;
	
}

int
CGenethonDoc::ReSizeRows()
{
	DWORD MaxSize = 0;

	POSITION tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetTextLength() > MaxSize ) {
			MaxSize = tCGSeg->GetTextLength();
		}
	}

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	while (tPos != NULL ) {
		CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetTextLength() < MaxSize ) {
			if ( !tCGSeg->AppendFiller( MaxSize - tCGSeg->GetTextLength() ) ) {
				AfxMessageBox("GetMSFFile:AppendFiller Fail 2" );
				delete pGSFiller;
				pGSFiller = NULL;
				return 0;
			}
		}
	}

	return 1;
}		
		


int
CGenethonDoc::AppendDataRows(CPtrList& SequenceList, int Append )
{

	int SkippedName = 0;
	POSITION tPos = SequenceList.GetHeadPosition();
	while ( tPos != NULL ) {

		SeqNameStruct *tSNS = (SeqNameStruct *)SequenceList.GetNext(tPos);

		int DupName = 0;

		POSITION testPos = pGSFiller->SegDataList.GetHeadPosition();
		while (testPos != NULL ) {
			CGeneSegment *tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(testPos);
			if ( tCGSeg->GetTitle() == tSNS->Name ) {
				DupName = 1;
				break;
			}
		}
		
		if ( DupName ) {
			SkippedName = 1;
			delete tSNS;
			continue;
		}
		
		CGeneSegment *tCGSeg = new CGeneSegment();

		if ( tCGSeg == 0 ) {
			AfxMessageBox("GetMSFFile:new Fail 4" );
			delete pGSFiller;
			pGSFiller = NULL;
			return 0;
		}

		if ( !tCGSeg->Create( LINESEQUENCE, tSNS->Name, tSNS->Descr, tSNS->Weight, tSNS->hText, tSNS->Len, tSNS->Start, &m_UserVars.m_ForeColor, &m_UserVars.m_BackColor ) ) {
			AfxMessageBox("GetMSFFile:Create Fail 2" );
			delete pGSFiller;
			pGSFiller = NULL;
			return 0;
		}			
		
		// Cleanup
		delete tSNS;

		// put it on the list
		pGSFiller->AddData( tCGSeg );
		

	}

	if ( SkippedName ) {
		AfxMessageBox( "Duplicate Sequences (Names) have been discarded!" );
	}

	return 1;
}



int
CGenethonDoc::CreateBottomRows()
{
	HGLOBAL hComSeg;
	char *pc;
	DWORD tCnt;

	// Create Lowest row .. the Comment Row.
	hComSeg = GlobalAlloc( GMEM_FLAG, gMaxStrSize);
	if ( hComSeg == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalAlloc Fail 3" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	pc = (char *)GlobalLock( hComSeg );
	if ( pc == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalLock Fail 3" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	tCnt = gMaxStrSize;
	while ( tCnt-- ) {
		*pc++ = ' ';
	}
	GlobalUnlock ( hComSeg );
	
	CGeneSegment *tCGSeg = new CGeneSegment();

	if ( tCGSeg == 0 ) {
		AfxMessageBox("GetMSFFile:new Fail 5" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}

	if ( !tCGSeg->Create( LINECOMMENT, "Comment" , "Comment", 0.0, hComSeg, gMaxStrSize, 1, &m_UserVars.m_ForeColor, &m_UserVars.m_BackColor ) ) {
		AfxMessageBox("GetMSFFile:Create Fail 3" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}			
	
	pGSFiller->AddData( tCGSeg );
	// Created Comment Row

	return 1;

}

int
CGenethonDoc::CreateTopRows()
{
	HGLOBAL hComSeg;
	char *pc;
	DWORD tCnt;

	// Create First row .. the Score Row.
	hComSeg = GlobalAlloc( GMEM_FLAG, gMaxStrSize);
	if ( hComSeg == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalAlloc Fail 1" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	pc = (char *)GlobalLock( hComSeg );
	if ( pc == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalLock Fail 1" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	tCnt = gMaxStrSize;
	while ( tCnt-- ) {
		*pc++ = ' ';
		
	}
	GlobalUnlock ( hComSeg );
	
	CGeneSegment *tCGSeg = new CGeneSegment();

	if ( tCGSeg == 0 ) {
		AfxMessageBox("GetMSFFile:new Fail 2" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}

	if ( !tCGSeg->Create( 
			LINECOMMENT, 
			"Score" , 
			"Score", 
			0.0,
			hComSeg,
			gMaxStrSize, 
			1, 
			&m_UserVars.m_ForeColor, 
			&m_UserVars.m_BackColor 
	) ) {
		AfxMessageBox("GetMSFFile:Create Fail 0" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}			
	
	pGSFiller->AddData( tCGSeg );
	// Created Comment Row

	// Create Second row .. a Comment Row.
	hComSeg = GlobalAlloc( GMEM_FLAG, gMaxStrSize);
	if ( hComSeg == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalAlloc Fail 2" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	pc = (char *)GlobalLock( hComSeg );
	if ( pc == NULL ) {
		AfxMessageBox("GetMSFFile:GlobalLock Fail 2" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}
	tCnt = gMaxStrSize;
	while ( tCnt-- ) {
		*pc++ = ' ';
	}
	GlobalUnlock ( hComSeg );
	
	tCGSeg = new CGeneSegment();

	if ( tCGSeg == 0 ) {
		AfxMessageBox("GetMSFFile:new Fail 3" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}

	if ( !tCGSeg->Create( LINECOMMENT, "Comment" , "Comment", 0.0, hComSeg, gMaxStrSize, 1, &m_UserVars.m_ForeColor, &m_UserVars.m_BackColor ) ) {
		AfxMessageBox("GetMSFFile:Create Fail 1" );
		delete pGSFiller;
		pGSFiller = NULL;
		return 0;
	}			
	
	pGSFiller->AddData( tCGSeg );
	// Created Comment Row

	return 1;
}


