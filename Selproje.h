/*
    GeneDoc: Multiple Sequence Alignment Editing Utility
    Copyright (C) 2000, Karl Nicholas

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
// selproje.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelProject dialog

class CSelProject : public CDialog
{
// Construction
public:
	CSelProject(CWnd* pParent = NULL);	// standard constructor
	CGenethonDoc *pDoc;
	CGenethonDoc *poDoc;

// Dialog Data
	//{{AFX_DATA(CSelProject)
	enum { IDD = IDD_SELPROJ };
	CListBox	m_listProj;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSelProject)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProjlist();
	afx_msg void OnDblclkProjlist();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
