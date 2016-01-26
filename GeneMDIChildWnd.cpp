
#include "stdafx.h"

IMPLEMENT_DYNCREATE(CGeneMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CGeneMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGeneMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// toolbar buttons - IDs are command buttons
static UINT BASED_CODE genebut[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	IDM_SELECT,
	IDM_SELECTCOL,
	IDM_COPYMETACLIP,
};

BOOL 
CGeneMDIChildWnd::PreCreateWindow(CREATESTRUCT& cs )
{

//    cs.style |= WS_MAXIMIZE; 

    // Call the base-class version
    return CMDIChildWnd::PreCreateWindow(cs); 

	
//	cs.style |= WS_MAXIMIZE;	

//	return CMDIChildWnd::PreCreateWindow( cs );
}



int
CGeneMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	// CToolBar
	if (!m_GeneBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS ) ||
		!m_GeneBar.LoadBitmap ( IDB_GENEBAR ) ||
		!m_GeneBar.SetButtons( genebut, sizeof(genebut)/sizeof(UINT) )
	) {
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	return 0;
}
 
