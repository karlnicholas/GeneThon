// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

#define _WIN32_WINNT 0x0502
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions (including VB)

#include <afxrich.h>
#define VIEWBASE CRichEditView

#include <limits.h>



// typedef ...

extern int	NewGap, GapLen;
extern int CurrentZeroDistance;

extern char ProteinLocArray[23];
extern void GetTempFileName (CString& PathName );
extern void DeleteTempFile (CString& PathName );


enum {
	LINESEQUENCE, 
	LINECOMMENT 
};


#include "plex.h"
#include "charmap.h"
#include "dwordmap.h"
// typedef
#include "genestor.h"
#include "segnames.h"
#include "shadeps.h"
// Main doc
#include "dispvars.h"
#include "uservars.h"

// typedef
#include "usermess.h"
#include "drawstc.h"

// Graph View
#include "GraphWindow.h"

#include "genechi.h"

// Main prog
#include "genethon.h"

// PictFile
#include "pictfile.h"
#include "rtffile.h"

// Segements
#include "gsbase.h"
#include "gsegment.h"
#include "gsfiller.h"

// Views
#include "textview.h"

// Main doc
#include "genetdoc.h"

// Utility
#include "gstring.h"
// caret
#include "mycaret.h"
#include "sumcaret.h"

#include "sviewret.h"

//
#include "mainfrm.h"

#include "gvbase.h"

#include "gprowvw.h"
#include "gpsumvw.h"

// View
#include "gvedit.h"
#include "gvsum.h"
#include "gvelead.h"
#include "gvetail.h"
#include "gvefill.h"

// View
#include "genetvw.h"
#include "sumview.h"

//dialog
#include "displayp.h"
#include "prints.h"
#include "propsht.h"
#include "importty.h"
#include "exportdl.h"
#include "selarrse.h"
#include "genbank.h"
#include "GraphSetup.h"

//
#include "seqdetdi.h"
#include "seqdialo.h"

#define GMEM_FLAG GMEM_FIXED

enum {
	pict_init, 
	pict_charout, 
	pict_newline, 
	pict_exit
};
