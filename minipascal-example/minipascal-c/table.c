#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"
#include "pascal_yacc.h"
#include "util.h"

#define INT 0
#define REAL 1

/*
 * 请在本文件中编写有关词法与语法分析中所需要用到有关符号表相关的函数
 */

table_variable VarList[TABLE_MAX_VAR_NUM];
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

void OutputVarList(void)
{
	int i = 0;

	printf(" No.\t name \t\t   type\n");

	if (i >= VarCount) {
		printf("Symbol Table is NULL!\n");
		return;
	}

	for (i = 1; i <= VarCount; i++) {
		printf("%4d\t%6s\t\t", i, VarList[i].name);
		if (VarList[i].type) {
			printf(" REAL  \n");
		} else if (VarList[i].type == INT) {
			printf(" INTEGER\n");
		}
	}

	return;
}

// lookup the index of item in VarList
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






