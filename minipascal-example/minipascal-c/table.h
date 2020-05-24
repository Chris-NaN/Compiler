#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 20
#define TABLE_MAX_VAR_NUM 200
#define TABLE_MAX_ARRAY_NUM 200

typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // 变量名
	int type; // 类型
	int addr; // 地址
	int Iv;
	int array_no;
} table_variable;

typedef struct array_variable__ {
	int n;
	int C;
	int a;
	int L[TABLE_MAX_ARRAY_NUM];
	int U[TABLE_MAX_ARRAY_NUM];
	int D[TABLE_MAX_ARRAY_NUM];
}array_variable;

typedef struct label_variable__ {
	int DEF;
	int ADDR;
	char name[TABLE_MAX_IDENT_NAME_LEN];
}label_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];
extern array_variable TypeList[TABLE_MAX_VAR_NUM];
extern label_variable LabelList[TABLE_MAX_VAR_NUM];

extern int VarFlag;

void OutputVarList(void);
void OutputTypeList();
int id_or_keyword(char *);

// find the position of var_name in the table
int LookUp(char *Name);
// write var into table directly
int Enter(char *Name);
// write var into table if the var not exist.
int Entry(char *Name);

// tmp var init
int NewTemp();

extern int VarCount;
// merge the decoration of var
int Merge_var(int p1, int p2);
// patch the var
void VarBackPatch(int p, int t);
// patch the array var
void VarBackArrayPatch(int p, int type, int Iv, int array_no);

// create a new array type
int New_Array_Type();

void Update_D(int no, int dim, int L, int R);

void Update_C(int no, int dim, int L, int R);

// access C in addr field by number
int Access_C(int no);

int Access_a(int no);

int Access_d(int no, int k);

// get L and U of str
void Get_L_and_U(char *str, int *L, int *U);

// put var into table
int EnterLabel(char *Name);

int LookUpLabel(char *Name);


void BackLabelPatch(int p, int t);

// get the L's header tag
int GetLLabel();
// get next label
int GetNextLabel();

int GetCheckLabel();
#endif
