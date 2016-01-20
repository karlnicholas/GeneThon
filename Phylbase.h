
class CPhyloGenBase: public CObject
{
protected:
	
public:

	CPhyloGenBase*	m_pPGParent;
	int m_Depth;
	int m_DrawType;	// What was this node last draw as?
	CRect m_ClientRect;
	int m_Selected;
	int m_FirstSelection;
	int m_Number;

	char m_cAncestry;
	char m_pPrevResidue;
	unsigned m_AverageCost;

	CString m_Weight;


	void *m_pTSW;

//
	CPhyloGenBase() { 
		m_pPGParent = NULL;
	}

	virtual ~CPhyloGenBase() {}
//

	virtual void WriteString( CString& ParseString ) = 0;
	virtual int CheckCounts(int ErrMsg) = 0;
	virtual void SetDepth(int Depth) = 0;
	virtual int DetermineDraw( CPhyloGenBase * pPSBLast ) = 0;
	
	enum {
		DLABEL, 
		DNODESU, 
		DNODESL, 
		DNODEM, 
		DNODEEU, 
		DNODEEL, 
		DNOTHING, 
		DNODET, 
		DEXTEND,
		DNODER
	};

	virtual void CallFromSeq( CView* pView ) = 0;
	virtual void CallDocFromSeq( CDocument *pDoc ) = 0;
	virtual void CallDocFromDepth( CDocument *pDoc, int Depth ) = 0;
	virtual void CallSDFromNamedSeq( CDialog *pDlg, const CString& Name ) = 0;
	
};

