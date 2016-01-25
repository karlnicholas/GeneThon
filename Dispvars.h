#ifndef DISPVARS_H_INCLUDED
#define DISPVARS_H_INCLUDED

typedef struct {
		
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
	
	void SetTitleColors( const COLORREF nTextColor, const COLORREF nBkColor ) 
		{ m_DisplayVars.m_TitleTextColor = nTextColor; m_DisplayVars.m_TitleBkColor = nBkColor; }
	void GetTitleColors( COLORREF *TextColor, COLORREF *BkColor ) const 
		{ *TextColor = m_DisplayVars.m_TitleTextColor; *BkColor = m_DisplayVars.m_TitleBkColor; }
	
};

#endif
