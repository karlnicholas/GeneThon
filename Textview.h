// TextView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextView view

class CTextView : public VIEWBASE
{
	DECLARE_DYNCREATE(CTextView)
protected:
	CTextView();			// protected constructor used by dynamic creation
	CFont *m_pFont;


// Attributes
public:
	// Operations
public:

	void LoadFile(CString& PathName);
	void LoadMemfile(CMemFile* writtenMemFile);
	void SaveFile(CString& PathName);

	// Implementation
protected:
	virtual ~CTextView();
//	virtual	void OnDraw(CDC* pDC);		// overridden to draw this view
	virtual	CDocument *GetDocument();
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);


	// Generated message map functions
protected:
	//{{AFX_MSG(CTextView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRepsavefile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
