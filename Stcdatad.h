// stcdatad.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStcDataDet dialog

class CStcDataDet : public CDialog
{
// Construction
public:
	CStcDataDet(CWnd* pParent = NULL);	// standard constructor

	CMapWordToPtr *m_ColorMap;	// Colormap pointer
// Dialog Data
	//{{AFX_DATA(CStcDataDet)
	enum { IDD = IDD_STCDATADET };
	CListBox	m_DataDetList;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CStcDataDet)
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
