// groupsel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGroupSelect dialog

class CGroupSelect : public CDialog
{
// Construction
public:
	CGroupSelect(CWnd* pParent = NULL);	// standard constructor

	CGenethonDoc *pDoc;
	int GroupNum1;
	CString GroupName1;

	int GroupNum2;
	CString GroupName2;

	int GroupSeq;

// Dialog Data
	//{{AFX_DATA(CGroupSelect)
	enum { IDD = IDD_GROUPSELECT };
	CListBox	m_OtherList;
	CListBox	m_GroupList;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(CGroupSelect)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
