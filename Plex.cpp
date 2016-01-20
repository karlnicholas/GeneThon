// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1993 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "plex.h"

// Collection support
#ifdef AFX_COLL_SEG
#pragma code_seg(AFX_COLL_SEG)
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

CMyPlex* PASCAL CMyPlex::Create(CMyPlex*& pHead, UINT nMax, UINT cbElement)
{
	ASSERT(nMax > 0 && cbElement > 0);
	CMyPlex* p = (CMyPlex*) new BYTE[sizeof(CMyPlex) + nMax * cbElement];
			// may throw exception
	p->nMax = nMax;
	p->nCur = 0;
	p->pNext = pHead;
	pHead = p;  // change head (adds in reverse order for simplicity)
	return p;
}

void CMyPlex::FreeDataChain()     // free this one and links
{
	CMyPlex* p = this;
	while (p != NULL)
	{
		BYTE* bytes = (BYTE*) p;
		CMyPlex* pNext = p->pNext;
		delete bytes;
		p = pNext;
	}
}
