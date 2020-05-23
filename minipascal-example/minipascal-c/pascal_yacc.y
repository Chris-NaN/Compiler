%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "ast.h"
#include "ir.h"
#include "table.h"
#include "pascal_lex.h"

int yyerror(char*);

%}
%start    ProgDef
%union 
{
 int Iv;
 int CH;
 int NO;
 struct { int TC,FC;} _BExpr;
 struct { int QUAD,CH;} _WBD;
 struct { int type,place;} _Expr;
 char _Rop[5];
 int First;
 char str[20];
 struct node *ast_node;
}

/* 注意内容 */
/* 语言不区分大小写 */

/* 指定终结符的种类，也可不指定，由yacc工具设置 */

/* 定义标识符 */
%token <str> Iden    300 /* 标识符，如变量名、程序名等 */

/* 定义常量 */
%token <str> IntNo	 301 /* 非负整数 */
%token <str> RealNo  302 /* 非负实数，小数 */

/* 定义关键字 */
%token	Program 	400 /* 关键字 program */
%token	Begin		401 /* 关键字 begin */
%token	End			402 /* 关键字 end */
%token	Var			403 /* 关键字 var */
%token	Integer 	404 /* 关键字 integer */
%token	Real		405 /* 关键字 real */
%token	While		406 /* 关键字 while */
%token	Do			407 /* 关键字 do */
%token	If			408 /* 关键字 if */
%token	Then		409 /* 关键字 then */
%token	Else		410 /* 关键字 else */
%token	Or			411 /* 关键字 or */
%token	And			412 /* 关键字 and */
%token	Not			413 /* 关键字 not */

/* 定义两个字符以上的分隔符或算符等 */
%token	LE			500  /* <= */
%token	GE			501  /* >= */
%token	NE			502  /* <> */
%token  ASSIGNOP    503  /* := */
%token  DOTDOT	    504  /* .. */
%token  STARSTAR    505  /* ** */ 
%token	PTRARROW	506  /* -> */ 

/* 其它错误符号，如中文符号 */
%token	ERRORCHAR 	600  /* 错误符号 */

%left 	Or
%left	And
%nonassoc  	Not
%nonassoc '<' '>' '=' LE GE NE
%left '+' '-'
%left '*' '/'
%left UMINUS

/* 文法符号的属性请根据自己的实现进行调整，这个只是简单的标记，可能存在错误，需自行调整 */
%type <ast_node> ProgDef
%type <ast_node> SubProg
%type <CH> VarDef
%type <CH> VarDefList
%type <Iv> Type
%type <CH> VarDefState
%type <First> VarList
%type <CH> Statement
%type <CH> StateList
%type <CH> S_L
%type <CH> CompState
%type <CH> AsignState
%type <CH> ISE
%type <CH> IBT
%type <_WBD> WBD
%type <_Rop> RelationOp
%type <_Expr> Expr
%type <CH> Wh
%type <NO> Variable 
%type <_Expr> UnsignedConst 
%type <_BExpr> BoolExpr

%%
ProgDef: Program Iden {} ';' SubProg '.'
          {
			  // 文法符号Program对应关键字"program"，程序
          }
	;
SubProg: VarDef CompState
		{
		}
	;
VarDef:	Var VarDefList ';'
        {
			// 变量声明
		}
	;
VarDefList:	VarDefList ';' VarDefState
        {
			// 不同类型的多个变量声明
		}
	|	VarDefState
	    {
        }
	;
VarDefState: VarList ':' Type
		{
			// VarList记录的多个变量指定类型
		}
	;
Type: Integer
		{
			// 整数类型
		}
	|	Real
		{
			// 实数类型
		}
	;
VarList:	VarList ',' Variable
		{
			// 同一类型的多个变量通过逗号分割
		}
	|	Variable
		{
		}
	;
StateList:	S_L Statement
		{
		}
	|	Statement
		{
		}
	;
S_L:	StateList ';'
		{

			// 多个语句之间通过分号分割
		}
	;
Statement:	AsignState
		{
			// 赋值语句是句子的一种
		}
	|	ISE Statement
		{
			// If Else语句是句子的一种
		}
	|	IBT Statement
		{
			// If then语句是句子的一种
		}

	|	WBD Statement
		{
			// While语句是句子的一种
		}
	|	CompState
	    {
			// Begin End语句块
		}
	|	{
	    }
	;
CompState:	Begin StateList End
		{
			// Begin End语句块，Begin类似于C语言的{，End类似于C语言的}
		}
	;
AsignState:	Variable ASSIGNOP  Expr
		{
			// 赋值语句
		}
	;
ISE:	IBT Statement Else
		{
			// If Else语句
		}
	;
IBT:	If BoolExpr Then
		{
			// If Then 语句
		}

	;
WBD: Wh BoolExpr Do
		{
			// while循环
		}
	;

Wh:	 While
        {
			// 文法符号While对应关键字"while"
        }
	;

BoolExpr: Expr
		{
			// 布尔表达式
		}
	;

Expr: SimpleExpression
		{

		}
 	| SimpleExpression RelationOp SimpleExpression
	 	{
			 // 关系运算

		}
 	;

SimpleExpression: Term 
		{

		}
 	| SimpleExpression '+' Term
	 	{
			 // 加法运算

		}
 	| SimpleExpression '-' Term
	 	{
			 // 减法运算

		}
 	| SimpleExpression Or Term
		{
			// 逻辑或运算

		}
 	;

Term: Factor 
		{

		}
 	| Term '*' Factor
	 	{
			 // 算术乘运算

		}
 	| Term '/' Factor
	 	{
			 // 算术除运算

		}
 	| Term And Factor
	 	{
			 // 逻辑与运算

		}
 	;

Factor: Sign Factor
		{
			// 正或负运算

		}
 	| Exponentiation
		{
			// 指数

		}
 	;

Exponentiation: Primary
		{

		}
 	| Primary STARSTAR Exponentiation
	 	{
			 // 乘方运算，Primary的Exponentiation次方

		}
 	;

Primary: Variable
		{
			// 变量

		}
	| UnsignedConst
		{
			// 无符号整数

		}
	| '(' Expr ')'
		{
			// 括号运算

		}
 	| Not Primary
	 	{
			 // 逻辑非运算

		}
 	;

Sign: '+' 
		{
			// 正号，表示正数
		}
	| '-'
		{
			// 负号，取负

		}
	;

Variable: Iden
		{
			// 文法符号Iden对应标识符，以字母或下划线开头后面是字母、数字或下划线组成的符号串
		}
	;

UnsignedConst:	IntNo
		{
			// 常数，无符号整数
		}
	|	RealNo
		{
			// 常数，无符号实数
		}
	;

RelationOp:	'<'
		{
			// 小于
		}
	|	'>'
		{
			// 大于
		}	
	|	'='
		{
			// 等于
		}
	|	GE
		{
			// 文法符号GE对应大于等于，符号串为">=
		}
	|	NE 
		{
			// 文法符号NE对应不等于，符号串为"<>""
		}
	|	LE
		{
			// 文法符号LE对应小于等于，符号串为"<=""
		}
	;
%%

int yyerror(char *errstr)
{
	printf("Reason:%s\n", errstr);
	return 0;
}
