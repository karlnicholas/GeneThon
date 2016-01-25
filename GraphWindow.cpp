
#include "stdafx.h"

IMPLEMENT_DYNCREATE(CGraphMDIChildWnd, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CGraphMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CGraphMDIChildWnd)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


int CGraphMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	lpCreateStruct->style |= WS_MAXIMIZE;
     if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
          return -1;

	return 0;
}
 
