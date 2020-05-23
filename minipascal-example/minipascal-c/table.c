#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "table.h"
#include "pascal_yacc.h"

/*
 * 请在本文件中编写有关词法与语法分析中所需要用到有关符号表相关的函数
 */

table_variable VarList[TABLE_MAX_VAR_NUM];

int VarCount = 0;

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
		} else {
			printf(" INTEGER\n");
		}
	}

	return;
}
