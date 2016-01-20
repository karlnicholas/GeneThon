
class CPictFile: public CObject {
private:

// Work Globals

	int m_fontdescent;
	
	int m_xpos;
	int m_ypos;
	
	FILE* m_OutFile;

	void MakeInt( int val );
	void MakePoint( int xpoint, int ypoint);
	void PutColor( COLORREF BackGround );

//
public:

	// Constructors
	CPictFile();
	DECLARE_DYNCREATE(CPictFile)

	int m_dev_xsize;
	int m_dev_ysize;
	
	int PictInit( 
		int pictwidth, 
		int pictheight, 
		int fontpoints, 
		int fontxsize, 
		int fontysize, 
		int fontdescent, 
		int fontbold, 
		char *fontname, 
		const char *outname,
		int addwidth, 
		int addheight, 
		int addascent 
	);

	int SumPictInit( 
		int pictwidth, 
		int pictheight, 
		int numchars, 
		int numcols, 
		int colsinch, 
		int fontpoints, 
		int fontxsize, 
		int fontysize, 
		int fontdescent, 
		int fontbold, 
		char *fontname, 
		const char *outname,
		int addwidth, 
		int addheight, 
		int addascent 
	);

	void CharOut( char c, COLORREF ForeGround, COLORREF BackGround );

	void SumFillRect( CRect& rect, COLORREF *pColor );
	void SumChar(int SumWidth);

	void NewLine();
	void Exit();

	void LineMiddle();
	void LineBottom();
	void LineLeft();
	void LineRight();


	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	

};

