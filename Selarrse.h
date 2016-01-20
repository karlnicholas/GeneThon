// selarrse.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelArrSeq dialog

class CSelArrSeq : public CDialog
{
// Construction
public:
	CSelArrSeq(CWnd* pParent = NULL);	// standard constructor

	CGenethonDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CSelArrSeq)
	enum { IDD = IDD_SELARRSEQ };
	CListBox	m_SeqList;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CSelArrSeq)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDesel();
	afx_msg void OnComplement();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
