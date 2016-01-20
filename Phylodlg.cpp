// phylodlg.cpp : implementation file
//

#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog dialog


CPhyloGenDialog::CPhyloGenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPhyloGenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPhyloGenDialog)
	m_ParseString = "";
	//}}AFX_DATA_INIT
}

void CPhyloGenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPhyloGenDialog)
	DDX_Control(pDX, IDC_PHYLOEDIT, m_PhyloEdit);
	DDX_Text(pDX, IDC_PHYLOEDIT, m_ParseString);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPhyloGenDialog, CDialog)
	//{{AFX_MSG_MAP(CPhyloGenDialog)
	ON_BN_CLICKED(IDC_PHYLOEXPORT, OnPhyloexport)
	ON_BN_CLICKED(IDC_PHYLOIMPORT, OnPhyloimport)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_PHYLOCOPY, OnPhylocopy)
	ON_BN_CLICKED(IDC_PHYLOPASTE, OnPhylopaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPhyloGenDialog message handlers

void CPhyloGenDialog::OnPhyloexport()
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "Phylogen Files (*.ph|*.ph|All Files (*.*)|*.*||";

	CFileDialog tDlg( FALSE, NULL, NULL, 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		Filter, NULL
	);
	
	if ( tDlg.DoModal() != IDOK ) {
		return;
	}
	
	// Start, Open the file
	// CFile
TRY {

	CStdioFile wFile ( tDlg.GetPathName(), CFile::modeWrite | CFile::typeText | CFile::modeCreate );

	wFile.WriteString( m_ParseString );
	
	wFile.Close();
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH

}

void CPhyloGenDialog::GetParseFile( const CString& FileName )
{
	// TODO: Add your control notification handler code here
TRY {
	CString tString;
	CString BuildString;
	// Start, Open the file
	CStdioFile iFile ( FileName, CFile::modeRead | CFile::typeText );
	
	while (1) {
		// clear out temp string.
		tString.Empty();
		if ( !iFile.ReadString( tString ) ) {
			break;		
		}
//		tString.SetAt(tString.GetLength() - 1, '\r');
		tString += '\r';
		tString += '\n';
		BuildString += tString;

//		if ( tString.Find(";") != -1 ) {
//			break;
//		}
	}

	iFile.Close();
	
	m_ParseString = BuildString;
	
} 
CATCH (CFileException, e ) {
    if( e->m_cause == CFileException::fileNotFound )
		AfxMessageBox( "File Not Found Error" );
	else
		AfxMessageBox( "File Error" );

	return;
}
AND_CATCH (CMemoryException, e ) {
	AfxMessageBox( "Memory Exception" );
	return;
}
END_CATCH
}

void CPhyloGenDialog::OnPhyloimport()
{
	// TODO: Add your control notification handler code here
	static char Filter[] = "Tree Files (*.ph)|*.ph|All Files (*.*)|*.*||";


	CFileDialog tDlg( TRUE, NULL, NULL, 
		OFN_HIDEREADONLY, 
		Filter, NULL
	);

	if ( tDlg.DoModal() != IDOK ) {
		return;
	}

	GetParseFile ( tDlg.GetPathName() );

	UpdateData(FALSE);

}



int CPhyloGenDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CenterWindow();
	
	return 0;
}

void CPhyloGenDialog::OnPhylocopy()
{
	// TODO: Add your control notification handler code here
	m_PhyloEdit.Copy();
	
}

void CPhyloGenDialog::OnPhylopaste()
{
	// TODO: Add your control notification handler code here
	m_PhyloEdit.Paste();
	
}
