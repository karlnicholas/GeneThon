
typedef struct {
	CString Name;
	CString Descr;
	DWORD  Len;
	DWORD  Start;
	DWORD  UseLen;
	int Check;
	HGLOBAL hText;
	char *tpc;
	char *pText;
} SeqNameStruct;

