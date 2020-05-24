#include <stdio.h>

#include "ir.h"
#include "table.h"

/*
 * 请在本文件中编写有关四元式创建与维护、打印等相关的函数接口
 */

int NXQ = 1;  /* used to indicate the number of next Quater*/

ir_quarter_expression QuaterList[MAX_IR_EXP_NUM];

void OutputQuaterList(void)
{
	int i = 0;

	if (i >= NXQ) {
		printf("no quater exists!\n");
		return;
	}

	for (i = 1; i <= NXQ; i++) {

		printf("(%3d) ( %5s, ", i, QuaterList[i].op);
		if (QuaterList[i].arg1)
			printf("%6s, ", VarList[QuaterList[i].arg1].name);
		else
			printf("      , ");

		if (QuaterList[i].arg2)
			printf("%6s, ", VarList[QuaterList[i].arg2].name);
		else printf("      , ");

		if ((QuaterList[i].op[0] == 'j') || (QuaterList[i].op[0] == 'S'))
			printf("%6d )\n", QuaterList[i].result);
		else if (QuaterList[i].result)
			printf("%6s )\n", VarList[QuaterList[i].result].name);
		else printf("-\t )\n");

		//printf("%d %d %d\n", QuaterList[i].arg1, QuaterList[i].arg2);
	}

	return;
}


int GEN(char *op, int arg1, int arg2, int result)
{
	if (NXQ >= MAX_IR_EXP_NUM) {
		puts("There is no enough space!");
		return -1;
	}
	
	strcpy(QuaterList[NXQ].op, op);
	QuaterList[NXQ].arg1 = arg1;
	QuaterList[NXQ].arg2 = arg2;
	QuaterList[NXQ].result = result;
	NXQ++;
	return NXQ - 1;
}


int Merge(int p1, int p2)  
{
	int p;

	if (p2 != 0) {

		for (p = p2; QuaterList[p].result != 0;) {
			p = QuaterList[p].result;
		}

		QuaterList[p].result = p1;
		p = p2;
	}
	else {
		p = p1;
	}

	return p;
}

void BackPatch(int p, int t)   
{
	int q = p;
	
	while (q) {
		int q1 = QuaterList[q].result;
		QuaterList[q].result = t;
		q = q1;
	}

	return;
}
