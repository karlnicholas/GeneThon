
class CGVEditTail: public CGeneViewBase 
{
private:

    // CPoint m_DataStartPoint;                // Set by OnDraw Function
    DWORD	m_lastval;

public:
    CGVEditTail();
    DECLARE_DYNCREATE(CGVEditTail)
     ~CGVEditTail();
     
//	#define GVETAIL_LENGTH 8

    void AddData( CString* nString );

    void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    void AssertValid() const;
    void Dump(CDumpContext& dc) const;
#endif
//
    void OnDraw( DrawStruct *DrawStc );
    void CalcDrawSize(CDC* pDC, UINT *XSize, DWORD *YSize, int GVETailLength);
    
	void UpdateGeneRange(CGVEdit *tEdit, int eval, CView *pWnd);

	void CountCopyText(DWORD *dwCount );
	void CopyText(char *tString, DWORD *dwCount, UINT RowNumber );
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteRTF( CRTFFile* pRTFFile, UINT RowNumber, CGenethonDoc* pDoc );

};

