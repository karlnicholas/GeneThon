
#ifndef PROPERTY_H_INCLUDED
#define PROPERTY_H_INCLUDED


#define MAXPROPERTYGROUP 20


typedef struct {
	int RowNum;
	char Group[MAXPROPERTYGROUP + 1];
	COLORREF TextColor;
	COLORREF BkColor;
} PropertyStruct;

void SetPropertyArray(CPtrArray *fPropertyArray, CPtrArray *tPropertyArray );
void SetPropertyDefault(CPtrArray *PropertyArray, int PropertyLevel, int ProjectType );


class CProperty: public CObject {

private:


	CPtrArray	m_PropertyArray[3];		// Holding the Level 1, 2, and 3 PropertyStructs

public:

	CProperty();

	~CProperty();
	void ClearArray();

	DECLARE_DYNCREATE(CProperty)

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
//

	void CopyVars( CProperty& nProperty );
	CPtrArray* GetArray(int p) { ASSERT(p<4);return &m_PropertyArray[p]; }
	
	PropertyStruct *GetPropertyStruct(int p, int i)
	{
		ASSERT(p<4);
		return (PropertyStruct *)m_PropertyArray[p][i]; 
	}


};

#endif
