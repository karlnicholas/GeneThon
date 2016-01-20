// motseqdl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMotSeqDlg dialog

class CMotSeqDlg : public CDialog
{
// Construction
public:
	CMotSeqDlg(CWnd* pParent = NULL);	// standard constructor
	CGenethonDoc *pDoc;

// Dialog Data
	//{{AFX_DATA(CMotSeqDlg)
	enum { IDD = IDD_MOTSEQ };
	CListBox	m_listMotif;
	CListBox	m_listSequence;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CMotSeqDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
