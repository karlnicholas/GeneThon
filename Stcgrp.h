
#ifndef STCGRP_H_INCLUDED
#define STCGRP_H_INCLUDED

typedef struct sStcDataValues {		// Group Level
	CMapWordToPtr *pColorMap;
	// CString Values;
	HGLOBAL	Values;
	DWORD	ValuesSize;
} StcDataValues;


class CStcGroup : public CObject {
public:


private:

	CStringList m_FileNames;							// Data Types FileName .. Save

	CString m_Name;								// Data Types Name
	CString m_Description;						// Data Type Description

	// CString m_Residues;							// DataType Residues ..
	HGLOBAL	m_Residues;
	DWORD	m_ResiduesSize;

	CString m_MasterSeq;						// Master Seq .. Save ..
	
	CMapStringToPtr m_StcDataValuesMap;			// Need to save a filename ..

	StcDataValues *m_pCurrentDataValues;

	// StcDataType *m_pCurrentDataType;

	CString m_CurrentDataTypeString;			// Currently Selected Data Type String Save..
	
	void CopyResidues( HGLOBAL nResidues, DWORD nResiduesSize );
	void CopyDataValues( StcDataValues *pDV, HGLOBAL nValues, DWORD nValuesSize );


public:

	CStcGroup();
	DECLARE_DYNCREATE(CStcGroup)

	void ClearAllData();
        
	virtual ~CStcGroup();

	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void CopyVars( const CStcGroup& fStcGroup );

	void SetNameDescription( const CString& nName, const CString& nDescription );
	void GetNameDescription( CString& Name, CString& Description ) const;

	void AddFileName( const CString& nName );		// This will compare for duplicates too.
	const CStringList& GetFileNames() const { return m_FileNames; }

	const CString& GetName() const { return m_Name; }
	
	void SetDataTypeValues( const CString& DataType, CMapWordToPtr *pCM, HGLOBAL Values, DWORD ValuesSize );
	
	void SetMasterSeq( const CString& MasterSeq ) { m_MasterSeq = MasterSeq; }
	const CString& GetMasterSeq() const { return m_MasterSeq; }

	void SetResidues( HGLOBAL nResidues, DWORD nResiduesSize ) 
	{ 
		m_Residues = nResidues;
		m_ResiduesSize = nResiduesSize;
	}

	HGLOBAL GetResidues() const { return m_Residues; }
	DWORD GetResiduesSize() const { return m_ResiduesSize; }

	void SetCurrentDataType ( const CString& DataType, int Force = 0 );
	const CString& GetCurrentDataType() const { return m_CurrentDataTypeString; }
	
	void GetCurrentData ( DWORD Index, COLORREF *TextColor, COLORREF *BackColor );

	const CMapStringToPtr& GetDataValuesMap() const { return m_StcDataValuesMap; }
	
	BOOL LookupDataValues( const CString& DataType, StcDataValues** DataValues ) const 
		{ 
			void *pv;
			BOOL rv =  m_StcDataValuesMap.Lookup( DataType, pv );
			*DataValues = (StcDataValues*)pv;
			return rv;
		}


};

#endif
