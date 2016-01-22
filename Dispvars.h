#ifndef DISPVARS_H_INCLUDED
#define DISPVARS_H_INCLUDED

typedef struct {
		
	int m_ResidueMode;		// 0 = Normal, 1 = diff  TODO

	int m_DiffMode;			// 0 old style diff, 1 = Top Seq Diff
	int m_PropStyle;		// 0 = Prop Conserved, 1 = Prop All

	COLORREF	m_TitleTextColor;
	COLORREF	m_TitleBkColor;

	// End Display Vars ....
} DisplayVars;


class CDisplayVars: public CObject {

private:

	DisplayVars	m_DisplayVars;

public:

	CDisplayVars();

	~CDisplayVars();

	DECLARE_DYNCREATE(CDisplayVars)

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void CopyVars( CDisplayVars *nDisplayVars, CDocument *pDoc );
	void CopyDisplayVars( DisplayVars *pDV, CDisplayVars *nDisplayVars, CDocument *pDC );
	void SetDisplayVars( DisplayVars *pDV, CDocument *pDC );
	void ClearVars( DisplayVars *pDV );
	
	int GetDiffMode() const { return m_DisplayVars.m_DiffMode; }
	int GetPropStyle() const {return m_DisplayVars.m_PropStyle; }
	int GetResidueMode() const { return m_DisplayVars.m_ResidueMode; }

	void SetDiffMode( int DiffMode ) { m_DisplayVars.m_DiffMode = DiffMode; }
	void SetPropStyle( int PropStyle ) { m_DisplayVars.m_PropStyle = PropStyle; }
	void SetResidueMode( int ResidueMode ) { m_DisplayVars.m_ResidueMode = ResidueMode; }
	
	void SetTitleColors( const COLORREF nTextColor, const COLORREF nBkColor ) 
		{ m_DisplayVars.m_TitleTextColor = nTextColor; m_DisplayVars.m_TitleBkColor = nBkColor; }
	void GetTitleColors( COLORREF *TextColor, COLORREF *BkColor ) const 
		{ *TextColor = m_DisplayVars.m_TitleTextColor; *BkColor = m_DisplayVars.m_TitleBkColor; }
	
};

#endif
