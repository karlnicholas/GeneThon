
class CGSFiller: public CGeneSegBase 
{
public:
        CGSFiller();
        DECLARE_DYNCREATE(CGSFiller)
        
        virtual ~CGSFiller();

        virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif
//
        void AddHeader( CString* nString );
        void AddData( CGeneSegment* nSeg );
//
};

