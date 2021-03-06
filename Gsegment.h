#ifndef GSEGMENT_H_INCLUDED
#define GSEGMENT_H_INCLUDED

class CGeneSegment: public CObject {

private:

	int		m_Style;		// is it a sequence or extra?
	CString	m_Title;
	CString	m_Descr;
	HGLOBAL	m_Text;
	DWORD	m_TextSize;
	DWORD	m_TextStart;
	double  m_Weight;
	DWORD	m_LastResidue;
	int		m_ExportFlag;
	DWORD	m_AlignExtra;

	void InitMembers() {
		m_Text = NULL;
		m_ExportFlag = 0;
	}

	CMapDWORDToCPAIR	m_mapCPAIR;
	CMapDWORDToChar		m_mapChar;

public:

	CGeneSegment() { InitMembers(); }

	DECLARE_DYNCREATE(CGeneSegment)

	virtual ~CGeneSegment() { 
		GlobalFree( m_Text );
	}
	
	GeneStor *m_pMyGeneStor;

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	int Create ( 
		int nStyle, 
		const char *nTitle, 
		const char *nDescr, 
		double nWeight,
		HANDLE	nText,
		DWORD	nTextSize, 
		DWORD	nTextStart, 
		COLORREF *nTextColor, 
		COLORREF *nBackColor 
	);
	
	void CreateCopy ( CGeneSegment *npCGSeg, DWORD nStart, DWORD nLen );

//		int nStyle, 
//		const char *nTitle, 
//		const char *nDescr, 
//		double nWeight,
//		HANDLE	nText, 
//		DWORD	nTextSize, 
//		DWORD	nTextStart, 
//		char	nGapChar, 
//		COLORREF *nTextColor, 
//		COLORREF *nBackColor, 
//		int	nDisplayGroup
//	);

	int GetStyle() const { return m_Style; }
	
	COLORREF *TextColor;
	COLORREF *BackColor;
	
	HANDLE MidText( DWORD first, DWORD count ) const;
	HANDLE MidText( DWORD first ) const;
	HANDLE LeftText( DWORD count ) const;
	HANDLE RightText( DWORD count ) const;

	int AppendFiller(DWORD Length);
	int InsertFillerRange(DWORD StartRange, DWORD EndRange);

	//	DWORD FindText ( const char c ) const;
	void SetShade ( DWORD Position, COLORREF nTextColor, COLORREF nBackColor, BOOL AddRemShade );
	void ResetShades();
	void ClearShades() { m_mapCPAIR.RemoveAll(); }
	const CMapDWORDToCPAIR& GetMapCPAIR() const { return m_mapCPAIR; }

	void SetComment ( DWORD Position, char nChar );
	void ResetComments();
	void ClearComments() { m_mapChar.RemoveAll(); }
	const CMapDWORDToChar& GetMapChar() const { return m_mapChar; }

	void SetResidue ( DWORD Position, char nChar );

	DWORD GetTextLength() { return m_TextSize; }
	DWORD GetLastResidue() { return m_LastResidue; }
	DWORD GetTextStart() { return m_TextStart; }
	void SetTextStart(DWORD nTextStart) { 

		m_TextStart = nTextStart; 
		GeneStor *spc = (GeneStor *)GlobalLock( m_Text );

		DWORD tGeneSeqNumber = m_TextStart;
		for ( DWORD i = 0L; i < m_TextSize; ++i ) {

			char tChar = toupper ( spc->CharGene );
			if ( tChar >= 'A' && tChar <= 'Z' ) {
				spc->GeneSeqNumber = tGeneSeqNumber++;
			} else {
				spc->GeneSeqNumber = 0L;
			}
			
			spc++;
		}

		m_LastResidue = tGeneSeqNumber;
		GlobalUnlock( m_Text );
	}
	
	const CString& GetTitle() { return m_Title; }
	void SetTitle( CString& nTitle ) { m_Title = nTitle; }

	const CString& GetDescr() { return m_Descr; }
	void SetDescr( CString& nDescr ) { m_Descr = nDescr; }

	double GetWeight() { return m_Weight; }
	void SetWeight(double nWeight) { m_Weight = nWeight; }

	DWORD	m_StartRange, m_EndRange;
	int		m_Expanded;
	HANDLE  GetTextHandle() { return m_Text; }

	void SetResidueText( HANDLE hText, DWORD StartPos, DWORD EndPos );
	HANDLE GetResidues() const;

	void SetExportFlag(int Flag) { m_ExportFlag = Flag; }
	int GetExportFlag() { return m_ExportFlag; }

	void LockAndLoad();
	void AlignDone();
	char AlignGet(DWORD Index);

};

#endif
