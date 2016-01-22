class CGeneString: public CObject {

private:
	int	m_Selected;
	int m_enum;

	GeneStor *m_GString;
	CGeneSegment *pGeneSegment;
	DWORD m_SegStartPos;
	int m_SegSize;

	COLORREF *m_TextColor; 
	COLORREF *m_BackColor;

public:

	// Constructors
	CGeneString();
	DECLARE_DYNCREATE(CGeneString)

	virtual ~CGeneString();

	int SetString( 
		GeneStor  *pnString, 
		int nSize, 
		DWORD nStartPos, 
		CGeneSegment *pParent, 
		unsigned int eval
	);
	int SetNewString( GeneStor *pnString, int nSize );
	void SetShade( int Position, COLORREF TextColor, COLORREF BackColor );
	void SetComment( int Position, char nChar );
	void SetResidue( int Position, char nChar );
	void GetShade(int Position, COLORREF *TextColor, COLORREF *BackColor);
	void Select();
	void DeSelect();
	int IsSelected();
	
	int GetLength() { return m_SegSize; }
	int GetEnum() { return m_enum; }
	DWORD GetStartPos() { return m_SegStartPos; }
	CGeneSegment *GetGeneSegment() { return pGeneSegment; }
	operator const GeneStor *  () const { return m_GString; }
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	

};

