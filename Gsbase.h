class CGeneSegBase: public CObject
{
protected:
//	int m_Selected;
public:

	CGeneSegBase*	pGeneSegParent;
	CPtrList		SegHeaderList;
	CPtrList		SegDataList;
//
	CGeneSegBase() { /* m_Selected = 0;*/  pGeneSegParent = NULL; }
	virtual ~CGeneSegBase() {}
//
//	virtual int	IsSelected() { return m_Selected; }
//	virtual void DeSelect() { m_Selected = 0; }
//	virtual void Select() { m_Selected = 1; }
//
};

