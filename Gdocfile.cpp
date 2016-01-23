
#include "stdafx.h"
#include <ctype.h>


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
int i;

int   
CGenethonDoc::ReadGenbankFile( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.
	CString LOCUS;
	CString DEFINITION;
	CString ACCESSION;
	CString NID;
	CString PID;
	CString Trans;
	CString Origin;

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	
	int EOFFLAG = 0;
	int gettingorigin = 0;
	int gettingtrans = 0;
	int Loc;

	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( !tString.GetLength() ) continue;

		if ( gettingtrans == 1 ) {
			Trans += tString;
			if ( Trans.Find( "\"" ) != -1 ) {
				gettingtrans = 0;
			}
		} else if ( gettingorigin == 1 ) {
			if ( Trans.Find( "//" ) != -1 ) {
				gettingorigin = 0;
			} else {
				Origin += tString;
			}
		}

		if ( tString.Find("LOCUS") != -1 ) {
			char *pc = LOCUS.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			LOCUS.ReleaseBuffer();
		} else if ( tString.Find("DEFINITION") != -1 ) {
			DEFINITION = tString.Mid( 12 );
		} else if ( tString.Find("ACCESSION") != -1 ) {
			char *pc = ACCESSION.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			ACCESSION.ReleaseBuffer();
		} else if ( tString.Find("NID") != -1 ) {
			char *pc = NID.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			NID.ReleaseBuffer();
		} else if ( tString.Find("PID") != -1 ) {
			char *pc = PID.GetBuffer(128);
			sscanf( (const char *)tString.Mid( 12 ), "%s", pc );
			PID.ReleaseBuffer();
		} else if ( (Loc = tString.Find("/translation=")) != -1 ) {
			Trans = tString.Mid( Loc + 14 );
			if ( Trans.Find( "\"" ) == -1 ) {
				gettingtrans = 1;
			}
		} else if ( (Loc = tString.Find("ORIGIN")) != -1 ) {
			gettingorigin = 1;
		}




	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	rFile.Close();

	gMaxStrSize = 0;

	CGenbank Dlg;
	Dlg.LOCUS = LOCUS;
	Dlg.ACCESSION = ACCESSION;
	Dlg.NID = NID;
	Dlg.PID = PID;
	if ( Dlg.DoModal() != IDOK ) return 0;

	tSNS = new SeqNameStruct;

	switch (Dlg.m_Locus) {
		case 0:
		tSNS->Name = LOCUS;
		break;
	case 1:
		tSNS->Name = ACCESSION;
		break;
	case 2:
		tSNS->Name = NID;
		break;
	case 3:
		tSNS->Name = PID;
		break;
	}

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( CString(tSNS1->Name) == tSNS->Name ) {
			char ErrBuff[256];
			sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)tSNS->Name );
			delete tSNS;
			AfxMessageBox( ErrBuff );
			return 0;
		}
	}

	tSNS->Descr = DEFINITION;
	tSNS->Len = 0;
	tSNS->Start = 1;
	tSNS->Check = 1234;

	CString *data;
	switch ( Dlg.m_Trans ) {
	case 0:
		data = &Trans;
		break;
	case 1:
		data = &Origin;
		break;
	}
	CString dString;
	i = 0;
	int End = data->GetLength();
	while ( i < End ) {
		char tChar = toupper((*data)[i]);
		if ( tChar >= 'A' && tChar <= 'Z' ) dString += (*data)[i];
		i++;
	}
	if ( dString.GetLength() ) {
		tSNS->Len = dString.GetLength();
		tSNS->hText = GlobalAlloc( GMEM_FLAG, tSNS->Len);
		char *pRes = (char *)GlobalLock(tSNS->hText);
		char *pnRes = dString.GetBuffer(tSNS->Len);
		int MoveCount = tSNS->Len;
		while (MoveCount--) {
			*pRes++ = *pnRes++;
		}
		GlobalUnlock(tSNS->hText);
		dString.ReleaseBuffer();
	}

	gMaxStrSize = tSNS->Len;

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("TEXT Data not Found");
		return 0;
	}

	SequenceList->AddTail( tSNS );

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}



int   
CGenethonDoc::ReadFasNTFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	int NoRead = 0;

	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			if ( !NoRead ) {
				tString.Empty();
				char *tStr = tString.GetBuffer(1024);
				if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
					// Done .. break out
					EOFFLAG = 1;
					break;
				}
				tString.ReleaseBuffer();
				tString = tString.SpanExcluding("\n\r");
			} else {
				NoRead = 0;
			}

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();

		// Skip initial spaces ..
		for ( i=1; i<End; ++i ) {
			if ( tString[i] != ' ' ) break;
		}
		
		// Skip Now get names ..
		CString strName;
		CString strDescr;
		for ( ; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}
		if ( strName.GetLength() > 50 ) strName = strName.Left(50);
		strDescr = tString.Mid( strName.GetLength() + 1 );

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Descr = strDescr;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );

		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			if ( tString[0] == '>' ) {
				NoRead = 1;
				EOFDATA = 1;
				break;
			}
			if ( tString[0] == ';' ) continue;

			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

//		if ( EOFFLAG ) {
//			delete (SeqNameStruct*)SequenceList->RemoveTail();
//			break;
//		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("FASTA Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenethonDoc::WriteFasNTFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, ">%s %s\n;\n;\n", (const char *)(pWS[i]).pCGSeg->GetTitle(), (const char *)(pWS[i]).pCGSeg->GetDescr());
			
		wFile.WriteString( BuildBuff );
	
		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				DataBlock[j] = tgs->CharGene;
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			DataBlock[j] = tgs->CharGene;
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int   
CGenethonDoc::ReadTextFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName, 
	const CString& SeqName, DWORD TextStart, const CString& Descr, int IUPAC )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	
	int EOFFLAG = 0;
	int NoRead = 0;

	tSNS = new SeqNameStruct;
	tSNS->Name = SeqName;
	tSNS->Descr = Descr;
	tSNS->Len = 0;
	tSNS->Start = TextStart;
	tSNS->Check = 1234;
	tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
	// Abort if alloc fails
	if ( tSNS->hText == NULL ) {
		AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
		rFile.Abort();
		return 0;
	}

	SequenceList->AddTail( tSNS );

	int EOFDATA = 0;
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
			break;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( !tString.GetLength() ) continue;

		int End = tString.GetLength();
		CString dString;
		i = 0;
		while ( i < End ) {
			if ( IUPAC ) {
				char tChar = toupper(tString[i]);
				if ( tChar >= 'A' && tChar <= 'Z' ) dString += tString[i];
			} else {
				if ( isgraph(tString[i]) ) dString += tString[i];
			}
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();
		}

	// Loop until end of file now.
	} while ( EOFDATA == 0 );

	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("TEXT Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}

int 
CGenethonDoc::WriteTextFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		wFile.WriteString( "\n" );

		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				DataBlock[j] = tgs->CharGene;
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			DataBlock[j] = tgs->CharGene;
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int 
CGenethonDoc::WriteTNoGapFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		wFile.WriteString( "\n" );

		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {

			DWORD DCount = 0;
			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				char tChar = toupper(tgs->CharGene);
				if ( tChar >= 'A' && tChar <= 'Z' ) {
					DataBlock[DCount++] = tgs->CharGene;
				}
				tgs++;
			}
			DataBlock[DCount] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

//			CurPos += DCount;
			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		
		DWORD DCount = 0;
		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( DWORD j = 0; j < Len; ++j ) {
			char tChar = toupper(tgs->CharGene);
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				DataBlock[DCount++] = tgs->CharGene;
			}
			tgs++;
		}
		DataBlock[DCount] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );

		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int   
CGenethonDoc::ReadPhylipIFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;
	int SeqCount;
	DWORD ResCount;
	int OptCount = 0;
	CString OptString;

	CStdioFile rFile(PathName, CFile::modeRead );


	tString.Empty();
	char *tStr = tString.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// Done .. break out
		rFile.Abort();
		AfxMessageBox(" Unexpected End Of File!" );
		return 0;
	}
	tString.ReleaseBuffer();

	// CopyMemory
	// Skip OPtions ..
	if ( sscanf( (const char *)tString, "%ld%ld", &SeqCount, &ResCount ) != 2 ) {
		rFile.Abort();
		AfxMessageBox("First Line bad!" );
		return 0;
	}


	for ( i=0; i < tString.GetLength(); ++i ) {
		if ( isalpha(tString.GetAt(i) ) ) {
			if ( tString.GetAt(i) != 'U' && tString.GetAt(i) != 'u' ) {
				OptCount++;
				OptString += "" + toupper(tString.GetAt(i));
			}
		}
	}

	for ( i=0; i < OptCount; ++i ) {
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			rFile.Abort();
			AfxMessageBox(" Unexpected End Of File!" );
			return 0;
		}
		tString.ReleaseBuffer();

		if ( OptString.Find ( toupper(tString.GetAt(0)) ) == - 1 ) {
			rFile.Abort();
			AfxMessageBox("Error Parsing Input Options!" );
			return 0;
		}
	}

	int EOFFLAG = 0;
	
	// Now we are looking for data
	for ( int SeqLoop=0; SeqLoop < SeqCount; ++SeqLoop ) {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		if ( EOFFLAG ) {
			rFile.Abort();
			AfxMessageBox("Error Parsing First Set of Sequences!" );
			return 0;
		}

		// Check Again Blank Line
		int End = tString.GetLength();
		for ( i=0; i < End; ++i ) {
			if ( tString[i] != ' ' && tString[i] != '\n' ) break;
		}

		// if blank line, then skip it
		if ( i == tString.GetLength() ) {
			--SeqLoop;
			continue;
		}

		CString strName;
		for ( i=0; i<tString.GetLength(); ++i ) {
			if ( tString[i] == ' ' ) break;
			if ( i == 10 ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				tSNS = tSNS1;
			}
		}

		if ( tSNS != NULL ) {
			rFile.Abort();
			char ErrBuff[256];
			sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", tSNS->Name );
			AfxMessageBox( ErrBuff );
			return 0;
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadPhylipFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}
		SequenceList->AddTail( tSNS );

		// Skip Whates left of name
		for ( ; i<tString.GetLength(); ++i ) {
			if ( tString[i] != ' ' ) break;
			if ( i == 10 ) break;
		}

		CString dString;
		while ( i < End ) {
			if ( isgraph(tString[i]) ) dString += tString[i];
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();

		}

		// Loop until end of file now.
	}

	do {


		POSITION SeqPOS = SequenceList->GetHeadPosition();

		for (int SeqLoop = 0; SeqLoop < SeqCount; ++SeqLoop ) {

			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( EOFFLAG ) {
				rFile.Abort();
				AfxMessageBox("Unexpected EOF Parsing Sequences!" );
				return 0;
			}

			// Check Again Blank Line
			int End = tString.GetLength();
			for ( i=0; i < End; ++i ) {
				if ( tString[i] != ' ' && tString[i] != '\n' ) break;
			}

			// if blank line, then skip it
			if ( i == tString.GetLength() ) {
				--SeqLoop;
				continue;
			}


			tSNS = (SeqNameStruct*)SequenceList->GetNext(SeqPOS);

			CString dString;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();

			}
		}

		// Loop until end of file now.

	} while ( tSNS->Len != ResCount );

	tSNS = (SeqNameStruct*)SequenceList->GetHead();

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len != tSNS->Len ) {
			AfxMessageBox("Sequence Length Problems!");
			return 0;
		}
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}

int 
CGenethonDoc::WritePhylipFile( const CString& PathName, int Selected )
{

	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
		CString *Title;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];


	for ( i=0; i < Count; ++i ) {
		(pWS[i]).Title = new CString;
	}

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	
	// Put a title Line
	sprintf ( BuildBuff, "%3d %5ld\n", Count, (const char *)(pWS[0]).pCGSeg->GetTextLength() );

	// Three blank lines.
	wFile.WriteString ( BuildBuff );

	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, "%-10s", (const char *)(pWS[i]).pCGSeg->GetTitle() );
		BuildBuff[10] = 0;
		*(pWS[i]).Title = BuildBuff;
	}
			
	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = (pWS[0]).pCGSeg->GetTextLength();
	int LineNum;
	int FirstThrough = 1;

	while ( (CurPos + 50L) < Len ) {

		LineNum = 0;

		while ( LineNum < Count ) {

			// clear out temp string.
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

			// Build data blocks
			GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
			for ( int j = 0; j < 50; ++j ) {
				DataBlock[j] = tgs->CharGene;
				tgs++;
			}
			DataBlock[50] = 0;

			if ( FirstThrough ) {
				sprintf ( BuildBuff, "%s%s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
			} else {
				sprintf ( BuildBuff, "%s\n", DataBlock );
			}
			wFile.WriteString( BuildBuff );
			
			LineNum++;
		}

		FirstThrough = 0;
		wFile.WriteString( "\n" );
	
		CurPos += 50L;

	};
	
	// Do Last set of lines 

	Len = (pWS[0]).pCGSeg->GetTextLength() - CurPos;
	
	LineNum = 0;

	while ( LineNum < Count ) {
	
			// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// Build data blocks
		GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			DataBlock[j] = tgs->CharGene;
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
	
		LineNum++;
	}
	
	
	wFile.WriteString( "\n" );

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	for ( i=0; i < Count; ++i ) {
		delete (pWS[i]).Title;
	}

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}



int   
CGenethonDoc::ReadPIRFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	
	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();
		CString strName;
		for ( i=4; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadPIRFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );


		// Skip over comment line
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			tString.ReleaseBuffer();
			rFile.Abort();
			AfxMessageBox("UnExpected End Of File" );
			return 0;
		}
		tString.ReleaseBuffer();


		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( tString[i] == '*' ) {
					EOFDATA = 1;
					break;
				}
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

		if ( EOFFLAG ) {
			delete (SeqNameStruct*)SequenceList->RemoveTail();
			break;
		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("PIR Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenethonDoc::WritePIRFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();

	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	Count = i;
	
	
	// Build Names and Len ...
	for ( int Line = 0; Line < Count; ++Line ) {
		
		sprintf( BuildBuff, ">P1;%s\n", (const char *)(pWS[Line]).pCGSeg->GetTitle() );
		wFile.WriteString( BuildBuff );
	
		sprintf( BuildBuff, "    Length = %ld\n", (const char *)(pWS[Line]).pCGSeg->GetTextLength() );
		wFile.WriteString( BuildBuff );

		DWORD CurPos = 0;

		char DataBlock[6][11];
		DWORD Len = (pWS[Line]).pCGSeg->GetTextLength();

		while ( (CurPos + 59L) < Len ) {
			int j;
			// Build data blocks
			for ( i=0; i < 6; ++i ) {
				GeneStor *tgs = ((pWS[Line]).pText) + CurPos + (i * 10 );
				for ( j = 0; j < 10; ++j ) {
					DataBlock[i][j] = tgs->CharGene;
					tgs++;
				}
				DataBlock[i][j] = 0;
			}

			sprintf ( BuildBuff, 
				"%s %s %s %s %s %s\n", 
				DataBlock[0], 
				DataBlock[1], 
				DataBlock[2], 
				DataBlock[3], 
				DataBlock[4],
				DataBlock[5]
			);
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[Line]).pCGSeg->GetTextLength() - CurPos;

		
		int tCount10 = (int)Len / 10;
		int tCountr = (int)Len % 10;
		int j;
		for ( i=0; i < 6; ++i ) {
			if ( i < tCount10 ) {
				GeneStor *tgs = (GeneStor *)((pWS[Line]).pText) + CurPos + (i * 10);
				for ( int j = 0; j < 10; ++j ) {
					DataBlock[i][j] = tgs->CharGene;
					tgs++;
				}
				DataBlock[i][j] = 0;
			} else if ( i == tCount10 ) {

				GeneStor *tgs = (GeneStor *)((pWS[Line]).pText) + CurPos + (i * 10);
				for ( int j = 0; j < tCountr; ++j ) {
					DataBlock[i][j] = tgs->CharGene;
					tgs++;
				}
				DataBlock[i][j] = '*';
				j++;
				DataBlock[i][j] = 0;
			} else {
				DataBlock[i][0] = 0;
			}

		}
			
		sprintf ( BuildBuff, 
			"%s %s %s %s %s %s\n", 
			DataBlock[0], 
			DataBlock[1], 
			DataBlock[2], 
			DataBlock[3], 
			DataBlock[4], 
			DataBlock[5]
		);
		wFile.WriteString( BuildBuff );

	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int   
CGenethonDoc::ReadFastaFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName )
{
	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );

	int EOFFLAG = 0;
	int NoRead = 0;

	do {
		// Now we are looking for Start Of Name
		do {
			// clear out temp string.
			if ( !NoRead ) {
				tString.Empty();
				char *tStr = tString.GetBuffer(1024);
				if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
					// Done .. break out
					EOFFLAG = 1;
					break;
				}
				tString.ReleaseBuffer();
				tString = tString.SpanExcluding("\n\r");
			} else {
				NoRead = 0;
			}

			if ( !tString.GetLength() ) continue;

			// Check For Start Char
			if (tString[0] == '>' ) break;

		// Loop until end of file now.
		} while ( EOFFLAG == 0 );

		// Normal End of File ...
		if ( EOFFLAG ) {
			break;
		}

		int End = tString.GetLength();

		// Skip initial spaces ..
		for ( i=1; i<End; ++i ) {
			if ( tString[i] != ' ' ) break;
		}
		
		// Skip Now get names ..
		CString strName;
		CString strDescr;
		for ( ; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}
		if ( strName.GetLength() > 50 ) strName = strName.Left(50);
		strDescr = tString.Mid( strName.GetLength() + 1 );

		// Skip initial spaces ..
		for ( i=0; i<strDescr.GetLength(); ++i ) {
			if ( strDescr[i] != ' ' ) break;
		}
		strDescr = strDescr.Mid( i );

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				char ErrBuff[256];
				sprintf ( ErrBuff, "Sequence Name Duplicate Found!: %s", (const char *)strName );
				AfxMessageBox( ErrBuff );
				rFile.Abort();
				return 0;
			}
		}

		tSNS = new SeqNameStruct;
		tSNS->Name = strName;
		tSNS->Descr = strDescr;
		tSNS->Len = 0;
		tSNS->Start = 1;
		tSNS->Check = 1234;
		tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
		// Abort if alloc fails
		if ( tSNS->hText == NULL ) {
			AfxMessageBox("ReadFastaFile:GlobalAlloc:Fail 1");
			rFile.Abort();
			return 0;
		}

		SequenceList->AddTail( tSNS );

		int EOFDATA = 0;
		// Now we are looking for data
		do {
			// clear out temp string.
			tString.Empty();
			char *tStr = tString.GetBuffer(1024);
			if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
				// Done .. break out
				EOFFLAG = 1;
				break;
			}
			tString.ReleaseBuffer();
			tString = tString.SpanExcluding("\n\r");

			if ( !tString.GetLength() ) continue;

			if ( tString[0] == '>' ) {
				NoRead = 1;
				EOFDATA = 1;
				break;
			}
			End = tString.GetLength();
			CString dString;
			i = 0;
			while ( i < End ) {
				if ( isgraph(tString[i]) ) dString += tString[i];
				i++;
			}
			
			if ( dString.GetLength() ) {
				int MoveCount = dString.GetLength();
				tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
				char *pRes = (char *)GlobalLock(tSNS->hText);
				pRes += tSNS->Len;
				tSNS->Len += MoveCount;
				char *pnRes = dString.GetBuffer(MoveCount);
				while (MoveCount--) {
					*pRes++ = *pnRes++;
				}
				GlobalUnlock(tSNS->hText);
				dString.ReleaseBuffer();
			}

		// Loop until end of file now.
		} while ( EOFDATA == 0 );

//		if ( EOFFLAG ) {
//			delete (SeqNameStruct*)SequenceList->RemoveTail();
//			break;
//		}
	} while(1);
	//     fclose(fd);
	rFile.Close();

	gMaxStrSize = 0;

	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len > gMaxStrSize ) {
			gMaxStrSize = tSNS1->Len;
		}
	}

	if ( gMaxStrSize == 0 ) {
		AfxMessageBox("FASTA Data not Found");
		return 0;
	}

} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;

}


int 
CGenethonDoc::WriteFastaFile( const CString& PathName, int Selected )
{
	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, ">%s %s.\n", (const char *)(pWS[i]).pCGSeg->GetTitle(), (const char *)(pWS[i]).pCGSeg->GetDescr() );
			
		wFile.WriteString( BuildBuff );
	
		DWORD CurPos = 0;

		char DataBlock[61];
		DWORD Len = (pWS[i]).pCGSeg->GetTextLength();

		while ( (CurPos + 60L) < Len ) {


			// Build data blocks
			GeneStor *tgs = ((pWS[i]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				DataBlock[j] = tgs->CharGene;
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s\n", DataBlock );
			wFile.WriteString( BuildBuff );

			CurPos += 60L;

		};
		
		// Do Last set of lines 

		Len = (pWS[i]).pCGSeg->GetTextLength() - CurPos;
		

		// Build data blocks
		GeneStor *tgs = ((pWS[i]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			DataBlock[j] = tgs->CharGene;
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s\n", DataBlock );
		wFile.WriteString( BuildBuff );
		
	}
	
	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	Count = pGSFiller->SegDataList.GetCount();

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}


int 
CGenethonDoc::WriteALNFile( const CString& PathName, int Selected )
{

	int i, rc = 1;

TRY {

	char BuildBuff[1024];
	
	struct WorkStruct {
		CGeneSegment * pCGSeg;
		GeneStor *pText;
		CString *Title;
	} *pWS;

	POSITION tPos;

	CStdioFile wFile( PathName, CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		i++;
	}
	int Count = i;
	pWS = new WorkStruct[Count];


	for ( i=0; i < Count; ++i ) {
		(pWS[i]).Title = new CString;
	}

	// Allocate memory for subsequent sequence data
	tPos = pGSFiller->SegDataList.GetHeadPosition();
	
	i = 0;
	while ( tPos != NULL ) {
		CGeneSegment * tCGSeg = (CGeneSegment *)pGSFiller->SegDataList.GetNext(tPos);
		if ( tCGSeg->GetStyle() != LINESEQUENCE ) {
			continue;
		}
		if ( Selected && !tCGSeg->GetExportFlag()  ) {
			continue;
		}
		(pWS[i]).pCGSeg = tCGSeg;
		(pWS[i]).pText = (GeneStor *)GlobalLock( tCGSeg->GetTextHandle() );

		if( (pWS[i]).pText == NULL) {
			AfxMessageBox ( "ReadMsfFile:GlobalLock:Fail 2");
			return 0;
		}
		i++;
	}
	
	
	// Put a title Line
	wFile.WriteString ( "CLUSTAL W(1.60) multiple sequence alignment\n" );

	// Three blank lines.
	wFile.WriteString ( "\n" );
	wFile.WriteString ( "\n" );
	wFile.WriteString ( "\n" );

	// Build Names and Len ...
	for ( i = 0; i < Count; ++i ) {
		
		sprintf( BuildBuff, "%-15s", (const char *)(pWS[i]).pCGSeg->GetTitle() );
		*(pWS[i]).Title = BuildBuff;
	}
			
	
	DWORD CurPos = 0;

	char DataBlock[61];
	DWORD Len = (pWS[0]).pCGSeg->GetTextLength();
	int LineNum;

	while ( (CurPos + 60L) < Len ) {

		LineNum = 0;

		while ( LineNum < Count ) {

			// clear out temp string.
			memset ( BuildBuff, ' ', sizeof(BuildBuff));

			// Build data blocks
			GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
			for ( int j = 0; j < 60; ++j ) {
				DataBlock[j] = tgs->CharGene;
				tgs++;
			}
			DataBlock[60] = 0;

			sprintf ( BuildBuff, "%s %s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
			wFile.WriteString( BuildBuff );
			
			LineNum++;
		}

		wFile.WriteString( "\n" );
	
		wFile.WriteString( "\n" );

		CurPos += 60L;

	};
	
	// Do Last set of lines 

	Len = (pWS[0]).pCGSeg->GetTextLength() - CurPos;
	
	LineNum = 0;

	while ( LineNum < Count ) {
	
			// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// clear out temp string.
		memset ( BuildBuff, ' ', sizeof(BuildBuff));

		// Build data blocks
		GeneStor *tgs = ((pWS[LineNum]).pText) + CurPos;
		for ( unsigned int j = 0; j < Len; ++j ) {
			DataBlock[j] = tgs->CharGene;
			tgs++;
		}
		DataBlock[Len] = 0;

		sprintf ( BuildBuff, "%s %s\n", (const char *)*(pWS[LineNum]).Title, DataBlock );
		wFile.WriteString( BuildBuff );
	
		LineNum++;
	}
	
	
	wFile.WriteString( "\n" );

	wFile.WriteString( "\n" );

	for ( i = 0; i < Count; ++i ) {
		GlobalUnlock ( (pWS[i]).pCGSeg->GetTextHandle() );
	}

	wFile.Close();
	
	for ( i=0; i < Count; ++i ) {
		delete (pWS[i]).Title;
	}

	// End routine Checks.
	delete pWS;

	// Return success
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

	return rc;
}

int 
CGenethonDoc::ReadALNFile( CPtrList* CommentList, CPtrList* SequenceList, CString& PathName )
{

	// Determine File Type.

TRY {

	CString tString;
	SeqNameStruct *tSNS;
	int i;

	CStdioFile rFile(PathName, CFile::modeRead );


	tString.Empty();
	char *tStr = tString.GetBuffer(1024);
	if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
		// Done .. break out
		AfxMessageBox(" Unexpected End Of File!" );
		return 0;
	}
	tString.ReleaseBuffer();

	// CopyMemory

	int EOFFLAG = 0;
	
	// Now we are looking for data
	do {
		// clear out temp string.
		tString.Empty();
		char *tStr = tString.GetBuffer(1024);
		if ( rFile.ReadString( tStr, 1024 ) == NULL ) {
			// Done .. break out
			EOFFLAG = 1;
		}
		tString.ReleaseBuffer();
		tString = tString.SpanExcluding("\n\r");

		// Check Blank Line
		if (tString.GetLength() < 3 ) continue;

		if ( tString.GetAt(0) == ' ' ) continue;

		// Check Again Blank Line
		int End = tString.GetLength();
		for ( i=0; i < End; ++i ) {
			char tchar = toupper(tString[i]);
			if ( tchar != ' ' ) break;
		}
		if ( i == End ) continue;

		CString strName;
		for ( i=0; i<End; ++i ) {
			if ( tString[i] == ' ' ) break;
			strName += tString[i];
		}

		tSNS = NULL;
		// Lets check if name exists ..
		POSITION tPos = SequenceList->GetHeadPosition();
		while ( tPos != NULL ) {
			SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
			if ( CString(tSNS1->Name) == strName ) {
				tSNS = tSNS1;
			}
		}

		if ( tSNS == NULL ) {
			tSNS = new SeqNameStruct;
			tSNS->Name = strName;
			tSNS->Len = 0;
			tSNS->Start = 1;
			tSNS->Check = 1234;
			tSNS->hText = GlobalAlloc ( GMEM_FLAG, 0 );
			// Abort if alloc fails
			if ( tSNS->hText == NULL ) {
				AfxMessageBox("ReadALNFile:GlobalAlloc:Fail 1");
				rFile.Abort();
				return 0;
			}

			SequenceList->AddTail( tSNS );
		}
		while ( i < End ) {
			if ( tString[i] != ' ' ) break;
			i++;
		}

		CString dString;
		while ( i < End ) {
			if ( tString[i] == ' ' ) break;
			if ( isgraph(tString[i]) ) dString += tString[i];
			i++;
		}
		
		if ( dString.GetLength() ) {
			int MoveCount = dString.GetLength();
			tSNS->hText = GlobalReAlloc( tSNS->hText, tSNS->Len + MoveCount, GMEM_MOVEABLE);
			char *pRes = (char *)GlobalLock(tSNS->hText);
			pRes += tSNS->Len;
			tSNS->Len += MoveCount;
			char *pnRes = dString.GetBuffer(MoveCount);
			while (MoveCount--) {
				*pRes++ = *pnRes++;
			}
			GlobalUnlock(tSNS->hText);
			dString.ReleaseBuffer();
		}

	// Loop until end of file now.
	} while ( EOFFLAG == 0 );

	tSNS = (SeqNameStruct*)SequenceList->GetHead();
	// Lets check if name exists ..
	POSITION tPos = SequenceList->GetHeadPosition();
	while ( tPos != NULL ) {
		SeqNameStruct* tSNS1 = (SeqNameStruct*)SequenceList->GetNext(tPos);
		if ( tSNS1->Len != tSNS->Len ) {
			AfxMessageBox("Sequence Length Problems: Duplicate Sequence Names?");
			return 0;
		}
	}

	//     fclose(fd);
	rFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return 0;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return 0;
}
END_CATCH

    return 1;
}


/*
"COLORMAP,PREDSS,\"sheet\",E,255,255,0,0",
"COLORMAP,PREDSS,\"no pred\", ,255,255,255,0",
"COLORMAP,PREDSS,\"helix\",H,0,0,255,1",
*/



DWORD  
MakeLoc( const CPtrList& listChain, char cChain, const CString& strLoc )
{
	typedef struct {
		char chain;
		DWORD count;
	} stcChain;

	DWORD offset = 0;

	POSITION tPos = listChain.GetHeadPosition();
	while ( tPos ) {
		stcChain *pCH = (stcChain *)listChain.GetNext(tPos);
		if ( cChain == pCH->chain ) break;
		offset += pCH->count;
	}

	return offset + atol( (const char *)strLoc );
	
}

char
GetRes( const CString& ResStr )
{

	static char *aatrans[] = {
		"Ala", "", "Cys", "Asp", "Glu", "Phe", "Gly", "His", "Ile", "", "Lys",
		"Leu", "Met", "Asn", "", "Pro", "Gln", "Arg", "Ser", "Thr", "", "Val",
		"Trp", "Xxx", "Tyr", "Glx" 
	};

	int r;
	// CString
	for ( r = 0; r < 26; ++r ) {
		if ( ResStr.CompareNoCase( aatrans[r]) == 0  ) break;
	}

	if ( r == 26 ) return 0;

	return 'A' + r;

}

