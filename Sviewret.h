
typedef struct {
	BOOL	Clip;
	// CRect	ClipRect;

	UINT ClipXPosition;
	DWORD ClipYPosition;
	UINT ClipXSize;
	DWORD ClipYSize;

	int		MenuFunc;
	int 	Expanded;
	DWORD 	ColSelStart;
	DWORD 	ColSelEnd;
	int		ColSelBegin;
	int		DDevice;
} VIEWRETSTRUCT;

