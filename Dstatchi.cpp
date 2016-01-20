
#include "stdafx.h"

IMPLEMENT_DYNCREATE(CDStatMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CDStatMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CDStatMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// toolbar buttons - IDs are command buttons
static UINT BASED_CODE dstatbut[] =
{
	// same order as in the bitmap 'toolbar.bmp'
	IDM_DSTATCOPY, 
		ID_SEPARATOR,
	IDM_DSTATGRAPHSETUP, 
		ID_SEPARATOR, 
	IDM_DSTATWRITESCORE, 
	IDM_DSTATWRITEDATA
};

int CDStatMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	lpCreateStruct->style |= WS_MAXIMIZE;
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	// CToolBar
	if (!m_DStatBar.Create(this) ||
		!m_DStatBar.LoadBitmap ( IDB_DSTATBAR ) ||
		!m_DStatBar.SetButtons( dstatbut, sizeof(dstatbut)/sizeof(UINT) )
	) {
		TRACE("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	return 0;
}
 
