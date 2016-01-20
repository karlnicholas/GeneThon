
typedef struct {
	const char *Name;
	void (*TableFunction)(int Sim[26][26], int *NewGap, int *GapLength, int *CurrentZeroDistance );
	const char *DefStrings;
	const char *TableDefs;
	int ScoreType;
} ScoreTableStruct;

