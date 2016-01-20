// seqdialo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSeqDialog dialog

class CSeqDialog : public CDialog
{

private:
	CPhyloSeq *m_pPGSeq;

	int MoveUpFunc();
	int MoveDownFunc();

// Construction
public:
	CSeqDialog(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSeqDialog)
	enum { IDD = IDD_SEQDIALOG };
	CStatic	m_CountSel;
	CStatic	m_strSeqCount;
	CListBox	m_SeqList;
	//}}AFX_DATA

	int m_Modify;
	CGenethonDoc *pDoc;
	void CallSDFromNamedSeq( CObject *p );
// Overrides
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnInitDialog();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSeqDialog)
	afx_msg void OnSeqdelete();
	afx_msg void OnSeqdetails();
	afx_msg void OnSeqimport();
	afx_msg void OnSeqmovedown();
	afx_msg void OnSeqmoveup();
	afx_msg void OnDblclkList1();
	afx_msg void OnMovebott();
	afx_msg void OnMovetop();
	afx_msg void OnCompliment();
	afx_msg void OnReverse();
	afx_msg void OnSeqexport();
	afx_msg void OnDuplicate();
	afx_msg void OnWritescr();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnSortname();
	afx_msg void OnSavesort();
	afx_msg void OnLoadsort();
	afx_msg void OnSortdesc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
