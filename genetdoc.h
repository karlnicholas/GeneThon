// geneddoc.h : interface of the CGenethonDoc class
//
/////////////////////////////////////////////////////////////////////////////

typedef struct {
	CGeneSegment *pCGSeg;
	GeneStor	*pGeneStor;
} ShadeSegStc;

class CGenethonDoc : public CDocument
{
protected: // create from serialization only
	CGenethonDoc();
	DECLARE_DYNCREATE(CGenethonDoc)

	void DoMarkerLine();

	// PCR Contrast ..
	void PCRMatchArr( int MatchArr[2][26], ShadePairStruct* rSPS, int *Count );
	int m_UsePCRSim;

// Pathname ..
	CString m_PathName;
	void SetFilePath(const char *pszPathName);

	
	void SortMatchArr( CDisplayVars *DisplayVars, int MatchArr[2][26], ShadePairStruct* rSPS, int *Count, int Depth );

	CByteArray Member[26];
	CByteArray Chosen;
	CByteArray Max;
	CByteArray Min;	 

	int BuildMatrix( const char *motif );
	int MotifLength( const char *motif );
	
	enum {
		ACTPAGENONE, 
		ACTPAGEHIGHLIGHTING, 
		ACTPAGESEARCH, 
		ACTPAGEREPORTS, 
	};
	void ClearShade();
	
int SequenceExport(int Selected = 0);
	int GetMSFFile( CString PathName, int Append = 0 );
	int GetFastaFile( CString PathName, int Append = 0 );
	int GetFasNTFile( CString PathName, int Append = 0 );
	int GetALNFile( CString PathName, int Append = 0);
	int GetPIRFile( CString PathName, int Append );
	int GetPhylipFile( CString PathName, int Append );
	int GetTextFile( CString PathName, int Append, 
		const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC );
	int GetGenbankFile( CString PathName, int Append = 0 );

	CTextView *m_pTextView;
	CView *m_pGeneView;
	CView *m_pSummaryView;

	CString ConvertPathname( const char *nExt );

	// Fasta read work vars ...
	BOOL bCR, bEOF;

	#define  BSIZE  64
	
	#define S_NULL      0
	#define S_PRENAME   1
	#define S_NAME      2
	#define S_PRETITLE  3
	#define S_TITLE     4
	#define S_NOTEORSEQ 5
	#define S_NOTES     6
	#define S_SEQ       7

	typedef int (*GetCharProc) (void);
	//typedef short ClassId;
	unsigned I, B;
	char     pLocal[BSIZE];
	HANDLE   hGlobal;
	int nErrno;
	#define ERR_FIL_OPEN 1
	DWORD	gMaxStrSize;

	BOOL ReadTextFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName, 
		const CString& SeqName, double SeqWeight, DWORD TextStart, const CString& Descr, int IUPAC );
	int WriteTextFile( const CString& PathName, int Selected = 0 );
	int WriteTNoGapFile( const CString& PathName, int Selected = 0 );

	BOOL ReadFasNTFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WriteFasNTFile( const CString& PathName, int Selected = 0 );
	BOOL ReadFastaFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WriteFastaFile( const CString& PathName, int Selected = 0 );
	BOOL ReadGenbankFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
//	void NEAR  Fastahopen();
//	BOOL NEAR  Fastahputc (char c);
//	HANDLE NEAR  Fastahclose();
//	int Fastagetchar1 (CFile& rFile);
//	int ParseFASTA ( CPtrList *SequenceList, CFile& rFile);
//	int Seq_New(HANDLE hTitle,HANDLE hDesc,HANDLE hText,CPtrList *SequenceList);
	//
	int ReadPIRFile ( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );
	int WritePIRFile( const CString& PathName, int Selected = 0 );

	// End of Fasta stuff

	int ReadMSFFile( CPtrList *CommentList, CPtrList *SequenceList, const char *FileName );
	int WriteMSFFile( const char *FileName );
	int ReadALNFile( CPtrList* CommentList, CPtrList* SequenceList, CString& PathName );
	int WriteALNFile( const CString& PathName, int Selected = 0 );
	
	int WritePhylipFile( const CString& PathName, int Selected = 0 );
	int ReadPhylipIFile( CPtrList *CommentList, CPtrList *SequenceList, const char * PathName );


	int ProcessRows( CPtrList& CommentList, CPtrList& SequenceList, int Append );
	int ReSizeRows();
	int AppendDataRows(CPtrList& SequenceList, int Append );
	int CreateBottomRows();
	int CreateTopRows();
	
	void SetUserDefaults();
	void GetNewUserDefaults( );

	void GetIniDefaults();

	void CheckOrientation();
	
	int m_MaxDepth;
	int m_NodeNumber;

	void GetProjectType();

	CGeneSegment* GetSequenceFromName( const CString& Name );

	int m_CallSwitch;
	enum { 
		CALLSETMAX, 
		CALLSETNUMBER,
		CALLSETOBJ, 
		CALLDRAWDEBUG
	};
//	int m_CRDetected;
	
	CPtrList m_SaveBestList;

	FILE * m_DebugFile;
	unsigned long m_DebugScore;
	char m_GapChar;
	unsigned m_CostDiv;
	int m_ScAve;
	int m_CancelFlag;
	int m_ScoreWaitCursor;


// Attributes
public:

	CGSFiller* pGSFiller;

	void CopyGSFiller( CGSFiller *npGSFiller );
	void CopyUserVars( UserVars *nUserVars, UserVars *oUserVars );
	void ClearUserVars( UserVars * dUserVars );

	void GetColors(COLORREF * TextColor, COLORREF *BkColor );

	void GetIniDisplayVars(CDisplayVars *DisplayVars);

	UserVars	m_UserVars;
	int m_SummaryMessaged;

	void DoConfigure(int ActivePage = ACTPAGENONE, int ReDraw = TRUE ); 
	//	int IndexChar( char n );
	
	// End User Variables ....

// Operations
public:

// Implementation
public:
	virtual ~CGenethonDoc();
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnOpenDocument(const char* pszPathName );
	virtual BOOL OnSaveDocument(const char *pszPathName );

// Generated message map functions
protected:
	//{{AFX_MSG(CGenethonDoc)
	afx_msg void OnConfigure();
	afx_msg void OnGeneloadini();
	afx_msg void OnFileSaveAs();
	afx_msg void OnGeneview();
	afx_msg void OnFileexport();
	afx_msg void OnSummaryview();
	afx_msg void OnUpdateSummaryview(CCmdUI* pCmdUI);
	afx_msg void OnFileSave();
	afx_msg void OnGenereportview();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
