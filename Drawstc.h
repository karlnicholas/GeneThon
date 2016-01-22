
typedef struct {
	CDC *pDC;
	CView *pView;

//
	DWORD	ColSelStart;
	DWORD	ColSelEnd;
	int 	MenuFunc;
	int		ColSelBegin;

//	DWORD TopPage;
//	DWORD BottomPage;
	int PrintYOffset;
//
	UINT DisplayXPosition;
	DWORD DisplayYPosition;
	UINT DisplayWidth;
	DWORD DisplayHeight;
	
	UINT ReDrawLeft;
	DWORD ReDrawTop;
	UINT ReDrawRight;
	DWORD ReDrawBottom;
} DrawStruct;
