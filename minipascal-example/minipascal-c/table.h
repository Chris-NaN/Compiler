#ifndef __TABLE_H__
#define __TABLE_H__

#define TABLE_MAX_IDENT_NAME_LEN 40
#define TABLE_MAX_VAR_NUM 200

typedef struct table_variable__ {
	char name[TABLE_MAX_IDENT_NAME_LEN]; // 变量名
	int type; // 类型
	int addr; // 地址
	int Iv;
} table_variable;

typedef struct label_variable__ {
	int DEF;
	int ADDR;
	char name[TABLE_MAX_IDENT_NAME_LEN];
}label_variable;

extern table_variable VarList[TABLE_MAX_VAR_NUM];
extern label_variable LabelList[TABLE_MAX_VAR_NUM];

extern int VarFlag;

void OutputVarList(void);

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



#endif
