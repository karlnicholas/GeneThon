/////////////////////////////////////////////////////////////////////////////

typedef struct {
	COLORREF	rgbText;
	COLORREF	rgbBack;
} CPAIR;

class CMapDWORDToCPAIR : public CObject
{

	DECLARE_DYNAMIC(CMapDWORDToCPAIR)
protected:
	// Association
	struct CAssoc
	{
		CAssoc* pNext;
		UINT nHashValue;  // needed for efficient iteration
		DWORD key;
		CPAIR value;
	};
public:

// Construction
	CMapDWORDToCPAIR(int nBlockSize=10);

// Attributes
	// number of elements
//	int GetCount() const;
//	BOOL IsEmpty() const;

	// Lookup
	BOOL Lookup(DWORD key, CPAIR& rValue) const;

// Operations
	// Lookup and add if not there
	CPAIR& operator[](DWORD key);

	// add a new (key, value) pair
//	void SetAt(DWORD key, void* newValue);

	// removing existing (key, ?) pair
	BOOL RemoveKey(DWORD key);
	void RemoveAll();

	// iterating all (key, value) pairs
//	POSITION GetStartPosition() const;
	void GetNextAssoc(POSITION& rNextPosition, DWORD& rKey, CPAIR& rValue) const;

	// advanced features for derived classes
//	UINT GetHashTableSize() const;
	void InitHashTable(UINT hashSize);

// Overridables: special non-virtual (see map implementation for details)
	// Routine used to user-provided hash keys
	UINT HashKey(DWORD key) const;



inline int GetCount() const 
	{ return m_nCount; }

inline BOOL IsEmpty() const 

	{ return m_nCount == 0; }

inline void SetAt(DWORD key, CPAIR newValue) 
	{ (*this)[key] = newValue; }

inline POSITION GetStartPosition() const 
	{ return (m_nCount == 0) ? NULL : (POSITION)-1L; }

inline UINT GetHashTableSize() const
	{ return m_nHashTableSize; }


// Implementation
protected:
	CAssoc** m_pHashTable;
	UINT m_nHashTableSize;
	int m_nCount;
	CAssoc* m_pFreeList;
	struct CMyPlex* m_pBlocks;
	int m_nBlockSize;

	CAssoc* NewAssoc();
	void FreeAssoc(CAssoc*);
	CAssoc* GetAssocAt(DWORD, UINT&) const;

public:
	~CMapDWORDToCPAIR();
#ifdef _DEBUG
	void Dump(CDumpContext&) const;
	void AssertValid() const;
#endif
};

