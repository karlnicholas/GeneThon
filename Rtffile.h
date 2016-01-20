
class CRTFFile: public CObject {
private:

// Work Globals

	
	CStdioFile* m_OutFile;
	int m_fontxsize;
	int m_fontysize;
	int m_bold;
	int m_size;
	int m_modeflag;
	int m_fullweb;

	COLORREF m_bgcolor;
	COLORREF m_fcolor;
	CPtrList* m_pColorList;

//
public:

	// Constructors
	CRTFFile();
	DECLARE_DYNCREATE(CRTFFile)

	int RTFInit( int pictwidth, 
		int pictheight, 
		int fontpoints, 
		int fontxsize, 
		int fontysize, 
		int fontdescent, 
		int fontbold, 
		const char *outname, 
		COLORREF bgcolor, 
		COLORREF fcolor, 
		int modeflag, 
		CPtrList* pColorList
	);
	void CharOut( char c, COLORREF ForeGround, COLORREF BackGround );
	void StartBlock();
	void EndBlock();
	void StartLine();
	void EndLine();
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

