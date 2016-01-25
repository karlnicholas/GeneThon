
typedef struct {


	int m_PrintFileName;	//T/F
	int m_PrintDate;	//T/F
	
	int m_SumDefDis;
	int m_SumColInch;
	int m_Sum2Wid;
	int m_SumTextBlack;

	// Start User Variables ....
	int m_PrintShading;

	CString m_strLead;
	CString m_strTail;
	int m_MaxNameLength;

	// New vars ..
	CDisplayVars	m_Vars;		// Only Display Variables for non groups...
	
	CPtrList	m_DisplayVars;		// This holds CDisplayVars for groups 
	
	// 
	COLORREF	m_ForeColor;
	COLORREF	m_BackColor;


	int m_FontWeight;
	int m_FontSize;

	int			m_WidthMode;
	int			m_FixedXSize;


	CPtrArray	m_ShadePairArray;		// Holding a list of ShadePairStruct's
	
	double m_LeftBorder;
	double m_RightBorder;
	double m_TopBorder;
	double m_BottomBorder;

	CString m_PrintString;  // A header or footer string for printouts
	int m_PrintStringFlag;	//  = no, 1 = upper center, 2 = lower center.
	int m_PrintPageNumber;	// 0 = no, 1 = Upper Center, 2 = Upper Right, 3 = Lower Center, 4 = Lower Right.
	int m_PrintPageOffset;	// Offset to Page numbers while printing.
	int m_PrintFontWeight;
	int m_PrintFontSize;
	CString m_PrintFontName;
	int m_PrintGeneBlock;

	int m_ConsensusLine;			// 0 = upper
	
	int m_ShowTail;			// 1 = Show Gap Location Indicator

	int	m_Orientation;		// 0 = Portrait

	int m_ProjectType;		// 0 = protein, 1 = mixed, 2 = dna, 3 = rna

	int m_PictWidth;
	int m_PictHeight;
	int m_PictAscent;

	BOOL	m_MakeBackups;
	BOOL	m_LocAfterName;
	BOOL	m_LocAfterSeq;

} UserVars;
