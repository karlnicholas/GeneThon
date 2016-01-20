
class CGVEditFill: public CGeneViewBase 
{
private:

public:
    CGVEditFill();
    DECLARE_DYNCREATE(CGVEditFill)
    ~CGVEditFill();
    
    void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    void AssertValid() const;
    void Dump(CDumpContext& dc) const;
#endif
//
    void OnDraw( DrawStruct *DrawStc );
	void CalcDrawSize(CDC* pDC, UINT* XSize, DWORD* YSize, int );

	void CountCopyText(DWORD *dwCount);
	void CopyText(char *tString, DWORD *dwCount, UINT RowNumber );
	void WritePict( CPictFile* pPictFile, UINT RowNumber, CGenethonDoc* pDoc );
	void WriteHTML( CHTMLFile* pHTMLFile, UINT RowNumber, CGenethonDoc* pDoc );
};

