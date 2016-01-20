
class CPhyloSeq: public CPhyloGenBase 
{

	CGeneSegment *m_pSequence;


public:
        
	CPhyloSeq();
	DECLARE_DYNCREATE(CPhyloSeq)

	virtual ~CPhyloSeq();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void WriteString( CString& ParseString );
	int CheckCounts(int ErrMsg);
	void SetDepth( int Depth );
	int DetermineDraw ( CPhyloGenBase * pPNPLast );
	void CallFromSeq( CView *pView );
	void CallDocFromSeq( CDocument* pDoc );
	void CallDocFromDepth( CDocument* pDoc, int Depth );
	void CallSDFromNamedSeq( CDialog *pDlg, const CString& Name );
//
	void SetSequence( CGeneSegment *pSeq ) { m_pSequence = pSeq; }
	const CString& GetName() { return m_pSequence->GetTitle(); }
	GeneStor* GetGeneStor() { return m_pSequence->m_pMyGeneStor; }
//
};

