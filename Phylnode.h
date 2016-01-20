
class CPhyloNode: public CPhyloGenBase 
{

	int m_FirstBranch;
	int m_FirstCallBack;

public:
	CPhyloNode();
	DECLARE_DYNCREATE(CPhyloNode)
        
	virtual ~CPhyloNode();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Data
	CPtrList	m_PhyloList;

//	int m_ScoreCarry;
//	int m_ScoreIndex;
//	unsigned long m_SaveScore;
//	int m_AssignedDescent;
	
//	CString m_Ancestry;
	
//	char m_SaveBestResidue;


	
// Methods

	void WriteString( CString& ParseString );
	int CheckCounts(int ErrMsg);
	void SetDepth( int Depth );
	int DetermineDraw( CPhyloGenBase * pPNPLast );
	void CallFromSeq( CView* pView );
	void CallDocFromSeq( CDocument* pDoc );
	void CallDocFromDepth( CDocument* pDoc, int Depth );
	void CallSDFromNamedSeq( CDialog *pDlg, const CString& Name );
//
};

