#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"
#include "pascal_yacc.h"
#include "util.h"

#define INT 0
#define REAL 1
#define ARRAY 2
#define BOOL 3

/*
 * 请在本文件中编写有关词法与语法分析中所需要用到有关符号表相关的函数
 */

table_variable VarList[TABLE_MAX_VAR_NUM];
array_variable TypeList[TABLE_MAX_VAR_NUM];
label_variable LabelList[TABLE_MAX_VAR_NUM];

// error check
extern int yyerror(char *errstr);
extern char errir_info[MAX_INFO_LEN];
extern int error_number;

int VarCount = 0;
int TypeCount = 0;
int LabelCount = 0;
int VarFlag = 0;

int tmp_cnt = 0;

static char KeyWord[][TABLE_MAX_IDENT_NAME_LEN] = {
		"PROGRAM",
		"BEGIN",
		"END",
		"VAR",
		"INTEGER",
		"REAL",
		"WHILE",
		"DO",
		"IF",
		"THEN",
		"ELSE",
		"OR",
		"AND",
		"NOT"
	};

int id_or_keyword(char *str)
{
	unsigned int i, j;
	char *p, buf[TABLE_MAX_IDENT_NAME_LEN];

	for (i = 0; i < sizeof(KeyWord) / sizeof(KeyWord[0]); i++) {
		p = str;

		for (j = 0; j < strlen(str); j++)
			buf[j] = (char)toupper(p[j]);
		
		buf[j] = '\0';

		if (!strcmp(KeyWord[i], buf)) {
			break;
		}
	}

	if (i < sizeof(KeyWord) / sizeof(KeyWord[0]))
		return i + 400;

	return Iden;
}

void OutputVarList(void)
{
	int i = 0;

	printf(" No.\t name \t\t   type\n");

	if (i >= VarCount) {
		printf("Symbol Table is NULL!\n");
		return;
	}

	for (i = 0; i < VarCount; i++) {
		printf("%4d\t%6s\t\t", i, VarList[i].name);
		if (VarList[i].type) {
			printf(" REAL  \n");
		} else if (VarList[i].type == INT) {
			printf(" INTEGER\n");
		} else if (VarList[i].type == BOOL){
			printf(" BOOL  \n");
		} else if (VarList[i].type == ARRAY){
			if (VarList[i].Iv == INT)
				printf("INTEGER ARRAY\n");
			else printf("REAL ARRAY\n");
		}
	}

	return;
}

void OutputTypeList(void)
{
	int i = 0;
	for (i = 1; i <= TypeCount; i++)
	{
		printf("N: %d.\t C: %d\t a: %d\n", TypeList[i].n, TypeList[i].C, TypeList[i].a);
		int j;
		for (j = 1; j <= TypeList[i].n; j++) {
			printf("L: %d.\t U : %d\t D: %d\n", TypeList[i].L[j], TypeList[i].U[j], TypeList[i].D[j]);
		}
	}
}

int LookUp(char *Name)
{
	for (int i = 1; i <= VarCount; i++) {
		if (strcmp(VarList[i].name, Name) == 0) {
			return i;
		}
	}
	
	return 0;
}

int Enter(char *Name)
{
	
	VarCount++;
	if (VarCount > TABLE_MAX_VAR_NUM) {
		printf("There is no enough space!\n");
		return 0;
	}
	strncpy(VarList[VarCount].name, Name, sizeof(Name));
	VarList[VarCount].addr = 0;
	
	return VarCount;
}

int Entry(char *Name)
{
	int i = LookUp(Name);
	
	if (Name[0] < 'a' || Name[0] > 'z') {
		if (i> 0) return i;
		else return Enter(Name);
	}
	
	if (VarFlag == 0) {
		if (i == 0) {
			return Enter(Name);
		}
		else {
			if (VarList[i].type == ARRAY)
				error_number = REDEFINE_ARRAY;
			else 
				error_number = REDEFINE_SIM_VAR;

			sprintf(errir_info, "%s", Name);
			yyerror(Name);
			return 0;
		}
	}
	else{  
		if (i == 0) {
			error_number = UNDEFINE_VAR;
			sprintf(errir_info, "%s", Name);
			yyerror(Name);
		}
		else {
			return i;
		}
	}
	return 0;
}





int NewTemp()
{
	char tmp_name[5]; 
	
	sprintf(tmp_name, "#T%d", tmp_cnt);
	tmp_cnt++;
	return Entry(tmp_name);
}

int Merge_var(int p1, int p2)
{
	VarList[p2].addr = p1;
	return p2;
}


void VarBackPatch(int p, int type)
{
	int q = p;
	while (q) {
		
		int tmp = q;
		q = VarList[q].addr;
		VarList[tmp].type= type;
	}

}


void VarBackArrayPatch(int p, int type, int Iv, int array_no)
{
	int q = p;

	while (q) {
		
		int tmp = q;
		q = VarList[q].addr;
		VarList[tmp].type= type;
		VarList[tmp].Iv = Iv;
		VarList[tmp].array_no = array_no;
	}

}

int New_Array_Type()
{
	TypeCount ++ ;
	TypeList[TypeCount].n = 0;
	TypeList[TypeCount].C = 0;
	
	TypeList[TypeCount].a = 0;
	return TypeCount;
}

void Update_D(int no, int dim, int L, int R)
{
	TypeList[no].n = dim;
	TypeList[no].L[dim] = L;
	TypeList[no].U[dim] = R;
	TypeList[no].D[dim] = R-L+1;
}

void Update_C(int no, int dim, int L, int R)
{
	
	if (dim == 2) TypeList[no].C = 1;

	TypeList[no].C = TypeList[no].C * ((R-L+1) + L);
}



int Access_C(int no)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].C;

}

int Access_a(int no)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].a;
}

int Access_d(int no, int k)
{
	no = VarList[no].array_no;
	if (no == 0) 
		printf("no eixst array!\n");
	return TypeList[no].D[k];
}


void Get_L_and_U(char *str, int *L, int *U)
{
	int len = strlen(str);
	
	int i;
	int ll = 0;
	int rr = 0;
	int flag = 0;
	for (i = 0; i < len; i++) {
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '.') {
			flag = 1;
			continue;
		}
		if (flag == 0) {
			ll = ll * 10 + str[i] - '0';
		}
		else {
			
			rr = rr * 10 + str[i] - '0';
		}
		(*L) = ll;
		(*U) = rr;
	}



}


int EnterLabel(char *Name)
{
	
	LabelCount++;
	if (LabelCount > TABLE_MAX_VAR_NUM) {
		printf("There is no enough space!\n");
		return 0;
	}
	strncpy(LabelList[LabelCount].name, Name, sizeof(Name));
	LabelList[LabelCount].ADDR = 0;

	return LabelCount;
}

int LookUpLabel(char *Name)
{
	
	for (int i = 1; i <= LabelCount; i++) {
		if (strcmp(LabelList[i].name, Name) == 0) {
			return i;
		}
	}

	return 0;

}


int GetCheckLabel()
{
	char name[TABLE_MAX_IDENT_NAME_LEN];
	for (int i = 1; i < TABLE_MAX_VAR_NUM; i++) {
		sprintf(name, "check%d", i);
		if (0 == LookUpLabel(name)) {
			return EnterLabel(name);
		}
	}
	printf("There is no enough space!");
	return 0;
}


int GetNextLabel()
{
	char name[TABLE_MAX_IDENT_NAME_LEN];
	for (int i = 1; i < TABLE_MAX_VAR_NUM; i++) {
		sprintf(name, "next%d", i);
		if (0 == LookUpLabel(name)) {
			return EnterLabel(name);
		}
	}
	printf("There is no enough space!");
	return 0;
}

int GetLLabel()
{
	char name[TABLE_MAX_IDENT_NAME_LEN];
	for (int i = 1; i < TABLE_MAX_VAR_NUM; i++) {
		sprintf(name, "L%d", i);
		if (0 == LookUpLabel(name)) {
			return EnterLabel(name);
		}
	}
	printf("There is no enough space!");
	return 0;
}