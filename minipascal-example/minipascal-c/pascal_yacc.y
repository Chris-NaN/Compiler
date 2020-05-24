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
#include "util.h"

extern int line_number;
extern int error_number;

int yyerror(char*);

#define INT 0
#define REAL 1
#define ARRAY 2
#define BOOL 3

#define WHILE 1
#define FOR 2
#define DO 3
#define REPEAT 4

%}
%start    ProgDef
%union 
{
 int Iv;
 int CH;     // chain header
 int NO;     // num in table
 struct { int TC,FC;} _BExpr;  // bool expr
 struct { int QUAD,CH;} _WBD;   // while boolexpr do
 struct { int type,place;} _Expr; // expr
 char _Rop[5];
 int First;
 char str[20];
 struct node *ast_node;

 struct {
	int CH; 
	struct node *nd;
 } ch_node;
 struct {
	char str[20];
	struct node *nd;
 } str_node;
 struct {
	int type;
	int Iv; 
	int array_no;
	struct node *nd;
 } iv_node;
 struct {
	int First; 
	struct node *nd;
 } first_node;
 struct {
	int CH; 
	int QUAD; 
	struct node *nd;
 } wbd_node;
 struct {
	char _Rop[5]; 
	struct node *nd;
 } rop_node;
 struct {
	int type, place; 
	struct node *nd;
 } exp_node;
	
 struct {
	int NO; 
	struct node *nd;
 } no_node;
 struct {
	int TC, FC, CH; 
	struct node *nd;
 } Bexp_node;
 struct {
	int loop, place, CH; 
	int Break_CH, Continue_CH;
	int type;
	struct node *nd;
 } ForLoop_node;
 struct {
	int Array_type;
	int NO;
	int OFFSET; //
	char str[20];
	struct node* nd;
 }Variable_node;
	
 struct {
	int NO; 	  
	int DIM;      
	int tmp_place; 
	struct node* nd;
 }ExprList_node;
	
 struct {
	int DIM;
	int NO; 
	struct node* nd;
 }TypeFirst_node;

	
 struct {
	int L;
	int U;
	struct node* nd;
 }OneDim_node;
 struct {
	int L_cnt;
	int T;
	int check_id;
	int next_id;
	struct node* nd;
 }case_node;

}

/* 注意内容 */
/* 语言不区分大小写 */

/* 指定终结符的种类，也可不指定，由yacc工具设置 */

/* 定义标识符 */

%token   <str> 	Iden    300
%token   <str> 	IntNo	301
%token	 <str> 	RealNo  302 
%token   <str>	CHAR	303
/* keyword def */
%token	 <str> 	Program 400
%token	 <str> 	Begin	401
%token	 <str> 	End	402
%token	 <str> 	Var	403
%token	 <str> 	Integer 404
%token	 <str> 	Real	405
%token	 <str> 	While	406
%token	 <str> 	Do	407
%token	 <str>	If	408
%token	 <str>	Then	409
%token	 <str>	Else	410
%token	 <str>	Or			411
%token	 <str>	And			412
%token	 <str>	Not			413
%token	 <str>	For			414
%token	 <str>	To			415
%token	 <str>	Repeat		416
%token	 <str>	Until		417
%token	 <str>	Of			418
%token	 <str>	Array		419
%token	 <str>	OneDimString	420
%token	 <str>	Goto	    421
%token	 <str>	Case	    422
%token	 <str>	Break	    423
%token	 <str>	Continue	424
%token	 <str>	Boolean 	425

/*Define double_character terminates:   */
%token			LE			500
%token			GE			501
%token			NE			502
%token			ASSIGNOP		503


/* 其它错误符号，如中文符号 */
%token	ERRORCHAR 	600  /* 错误符号 */

%left		And
%left 		Or
%nonassoc  	Not
%nonassoc '<' '>' '=' LE GE NE
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS


/* 文法符号的属性请根据自己的实现进行调整，这个只是简单的标记，可能存在错误，需自行调整 */

%type <ast_node> ProgDef
%type <ast_node> SubProg
%type <ch_node> VarDef
%type <ch_node> VarDefList
%type <iv_node> Type
%type <ch_node> VarDefState
%type <first_node> VarList
%type <ch_node> Statement
%type <ch_node> StateList
%type <ch_node> S_L

%type <ch_node> CompState
%type <ch_node> AsignState
%type <ch_node> ISE
%type <ch_node> IBT


%type <rop_node> RelationOp
%type <exp_node> Expr

%type <Variable_node> Variable 

%type <exp_node> Const 
%type <Bexp_node>BoolExpr
%type <Bexp_node>BoolExpr_and 
%type <Bexp_node>BoolExpr_or 
%type <ForLoop_node> Wh
%type <ForLoop_node> WBD




%%
ProgDef: Program Iden ';' SubProg '.'
          {
			// 文法符号Program对应关键字"program"，程序
			set_node_val_str(&ast_root,$2);
			struct node *tmpnode=NULL;
			$$=&ast_root;
			struct node *node1,*node2, *node3,*node4; 

			complete_init_node(&node1, "Program");
			int re = add_son_node(&ast_root, node1);

			complete_init_node(&node2, $2);
			re = add_brother_node(node1, node2);

			complete_init_node(&node3, ";");
			re = add_brother_node(node2,node3); 

			set_node_val_str($4, "SubProg");
			add_brother_node(node3, $4);

			complete_init_node(&node4, ".");
			add_brother_node($4, node4);
          }
	;
SubProg: VarDef CompState
		{
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$ = cur;
			set_node_val_str($1.nd,"VarDef");
			set_node_val_str($2.nd,"CompState");
			// add VarDef node into cur node;
			add_son_node($$, $1.nd);
			add_brother_node($1.nd, $2.nd);
		}
	;
VarDef:	Var VarDefList ';'
        {
			// 变量声明
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			struct node *node1, *node2;
			complete_init_node(&node1, "Var");
			complete_init_node(&node2, ";");
			set_node_val_str($2.nd,"VarDefList");
			// add son node and brother node
			add_son_node($$.nd ,node1);
			add_brother_node(node1,$2.nd); 
			add_brother_node($2.nd,node2);  
		}
	;
VarDefList:	VarDefList ';' VarDefState
        {
			// 不同类型的多个变量声明
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			struct node *node1;
			complete_init_node(&node1, ";");
			set_node_val_str($1.nd,"VarDefList");
			set_node_val_str($3.nd,"VarDefState");

			add_son_node($$.nd ,$1.nd);
			add_brother_node($1.nd,node1);
			add_brother_node(node1,$3.nd);  
		}
	|	VarDefState
	    {
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			set_node_val_str($1.nd,"VarDefState");
			add_son_node($$.nd ,$1.nd);
        }
	;
VarDefState: VarList ':' Type
		{
			// VarList记录的多个变量指定类型
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			if ($3.type == INT || $3.type == REAL) {
				VarBackPatch($1.First, $3.type);
			}else{
				VarBackArrayPatch($1.First, $3.type, $3.Iv, $3.array_no);
			}
			struct node *node1;
			complete_init_node(&node1, ":");
			set_node_val_str($1.nd,"VarList");
			set_node_val_str($3.nd,"Type");

			add_son_node($$.nd ,$1.nd);
			add_brother_node($1.nd,node1); 
			add_brother_node(node1,$3.nd);  
		}
	;
Type: Integer
		{
			// 整数类型
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.type = INT;
			$$.Iv = 0;	

			struct node *node1;
			complete_init_node(&node1, "Integer");

			add_son_node($$.nd, node1);
		}
	|	Real
		{
			// 实数类型
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.type = REAL;
			$$.Iv = 0;
			struct node *node1;
			complete_init_node(&node1, "Real");

			add_son_node($$.nd, node1);
		}
	;
VarList:	VarList ',' Variable
		{
			// 同一类型的多个变量通过逗号分割
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			struct node*node1;
			complete_init_node(&node1, ",");

			set_node_val_str($1.nd, "VarList");
			set_node_val_str($3.nd, "Variable");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, node1);
			add_brother_node(node1, $3.nd);

			// Var a, b, c : interger
			// keep the list head, $1.First.addr = $3.NO
			$$.First = Merge_var($3.NO, $1.First);
		}
	|	Variable
		{
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			
			$$.First = $1.NO;

			set_node_val_str($1.nd, "Variable");

			add_son_node($$.nd, $1.nd);
		}
	;
StateList:	S_L Statement
		{
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = $2.CH;
			set_node_val_str($1.nd, "S_L");
			set_node_val_str($2.nd, "Statement");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, $2.nd);

		}
	|	Statement
		{
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = $1.CH;

			set_node_val_str($1.nd, "Statement");
			add_son_node($$.nd, $1.nd);
		}
	;
S_L:	StateList ';'
		{
			// 多个语句之间通过分号分割
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			BackPatch($1.CH, NXQ);

			struct node *node1;
			complete_init_node(&node1, ";");
			set_node_val_str($1.nd, "StateList");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, node1);
		}
	;
Statement:	AsignState
		{
			// 赋值语句是句子的一种
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = 0;
			set_node_val_str($1.nd, "AsignState");
			add_son_node($$.nd, $1.nd);
		}
	|	ISE Statement
		{
			// If Else语句是句子的一种
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = Merge($1.CH, $2.CH);

			set_node_val_str($1.nd, "ISE");
			set_node_val_str($2.nd, "Statement");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, $2.nd);
		}
	|	IBT Statement
		{
			// If then语句是句子的一种
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = Merge($1.CH, $2.CH);
			set_node_val_str($1.nd, "IBT");
			set_node_val_str($2.nd, "Statement");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, $2.nd);
		}

	|	WBD Statement
		{
			// While语句是句子的一种
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			BackPatch($2.CH, $1.loop);
			GEN("j", 0, 0, $1.loop);
			$$.CH = $1.CH;
			// TODO
		}
	|	CompState
	    {
			// Begin End语句块
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = $1.CH;

			set_node_val_str($1.nd, "CompState");

			add_son_node($$.nd, $1.nd);
		}
	|	{
	    }
	;
CompState:	Begin StateList End
		{
			// Begin End语句块，Begin类似于C语言的{，End类似于C语言的}
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = $2.CH;

			struct node*node1,*node2;
			complete_init_node(&node1, "Begin");
			complete_init_node(&node2, "End");

			set_node_val_str($2.nd, "StateList");

			add_son_node($$.nd, node1);
			add_brother_node(node1, $2.nd);
			add_brother_node($2.nd, node2);
		}
	;
AsignState:	Variable ASSIGNOP  Expr
		{
			// 赋值语句
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			if ($1.OFFSET == 0) {
				GEN(":=", $3.place, 0, $1.NO);
			}else{
				GEN("[]=", $3.place, $1.NO, $1.OFFSET);
			}

			struct node*node1;
			complete_init_node(&node1, ":=");

			set_node_val_str($1.nd, "Variable");
			set_node_val_str($3.nd, "Expr");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, node1);
			add_brother_node(node1, $3.nd);
		}
	;
ISE:	IBT Statement Else
		{
			// If Else语句
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			int q = NXQ;

			GEN("j",0,0,0);
			BackPatch($1.CH, NXQ);
			$$.CH = Merge($2.CH, q);

			set_node_val_str($1.nd, "IBT");
			set_node_val_str($2.nd, "Statement");
			struct node * node1;
			complete_init_node(&node1, "Else");

			add_son_node($$.nd, $1.nd);
			add_brother_node($1.nd, $2.nd);
			add_brother_node($2.nd, node1);
		}
	;
IBT:	If BoolExpr Then
		{
			// If Then 语句
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			BackPatch($2.TC, NXQ);

			$$.CH = $2.FC;

			set_node_val_str($2.nd, "BoolExpr");
			struct node * node1, *node2;
			complete_init_node(&node1, "IF");
			complete_init_node(&node2, "Then");

			add_son_node($$.nd, node1);
			add_brother_node(node1, $2.nd);
			add_brother_node($2.nd, node2);
		}

	;
WBD: Wh BoolExpr Do
		{
			// while循环
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			BackPatch($2.TC, NXQ);
			$$.CH = $2.FC;
			$$.loop = $1.CH;

			// TODO
		}
	;

Wh:	 While
        {
			// 文法符号While对应关键字"while"
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			$$.CH = NXQ;
			struct node* node1;
			complete_init_node(&node1, "While");

			add_son_node($$.nd, node1);
        }
	;

BoolExpr:	Expr RelationOp Expr
		{
		
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.TC = NXQ;
		$$.FC = NXQ+1;
		
		GEN($2._Rop ,$1.place, $3.place,0);
		GEN("j",0,0,0);


		set_node_val_str($1.nd, "Expr");
		set_node_val_str($2.nd, $2._Rop);
		set_node_val_str($3.nd, "Expr");


		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		add_brother_node($2.nd, $3.nd);

		}
	|	BoolExpr_and BoolExpr
	    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		$$.FC = Merge($1.FC, $2.FC);
		$$.TC = $2.TC;


		set_node_val_str($1.nd, "BoolExpr_and");
		set_node_val_str($2.nd, "BoolExpr");
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}
	|	BoolExpr_or BoolExpr
	    {
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.TC = Merge($1.TC, $2.TC);
		$$.FC = $2.FC;

		
		set_node_val_str($1.nd, "BoolExpr_or");
		set_node_val_str($2.nd, "BoolExpr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, $2.nd);
		}	
	|	Not BoolExpr
	    {
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.TC = $2.FC;
		$$.FC = $2.TC;

		
		struct node*node1;
		complete_init_node(&node1, "Not");
		
		set_node_val_str($2.nd, "BoolExpr");
		
		
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		
		}
	|	'(' BoolExpr ')'
	    {
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.TC = $2.TC;
		$$.FC = $2.FC;

		
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		set_node_val_str($2.nd, "BoolExpr");
		
		
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);
		}
	;

BoolExpr_or: BoolExpr Or
{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		BackPatch($1.FC, NXQ);
		$$.TC = $1.TC; 


		
		struct node*node1;
		complete_init_node(&node1, "Or");

		set_node_val_str($1.nd, "BoolExpr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		
}
;

BoolExpr_and: BoolExpr And
{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		BackPatch($1.TC, NXQ);

		$$.FC = $1.FC; 

		struct node*node1;
		complete_init_node(&node1, "And");

		set_node_val_str($1.nd, "BoolExpr");
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);

}
;

Expr:		Expr'+'Expr
		{
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		int T = NewTemp();
		
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("+");
		}
		if ($1.type == INT && $3.type == INT)
		{
			GEN("+", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("+r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("+r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("+r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		
		struct node*node1;
		complete_init_node(&node1, "+");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);


		}
	|	Expr'-'Expr
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("-");
		}
		int T = NewTemp();
		
		if ($1.type == INT && $3.type == INT)
		{
			GEN("-", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("-r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("-r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("-r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		
		struct node*node1;
		complete_init_node(&node1, "-");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}

	|	Expr'*'Expr
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("*");
		}
		int T = NewTemp();
		
		if ($1.type == INT && $3.type == INT)
		{
			GEN("*", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("*r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("*r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("*r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		
		struct node*node1;
		complete_init_node(&node1, "*");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);




		}
	|	Expr'/'Expr
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		if ($1.type == BOOL || $3.type == BOOL) {
		    error_number = BOOL_OP_ERROR;
			yyerror("/");
		}
		int T = NewTemp();
		
		if ($1.type == INT && $3.type == INT)
		{
			GEN("/", $1.place, $3.place, T);
			$$.type = INT;
		}else if ($1.type == REAL && $3.type == REAL)
		{
			GEN("/r", $1.place, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == INT)
		{
			int U = NewTemp();
			GEN("itr", $1.place, 0, U);
			GEN("/r", U, $3.place, T);
			$$.type = REAL;
		}else if ($1.type == REAL)
		{
			int U = NewTemp();
			GEN("itr", $3.place, 0, U);
			GEN("/r", $1.place, U, T);
			$$.type = REAL;
		}
		$$.place = T;
	
		
		struct node*node1;
		complete_init_node(&node1, "/");

		set_node_val_str($1.nd, "Expr");
		set_node_val_str($3.nd, "Expr");
		
		
		add_son_node($$.nd, $1.nd);
		add_brother_node($1.nd, node1);
		add_brother_node(node1, $3.nd);

		}
	|	'('Expr')'
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;

		$$.type = $2.type;
		$$.place = $2.place;
		
		struct node*node1,*node2;
		complete_init_node(&node1, "(");
		complete_init_node(&node2, ")");

		
		set_node_val_str($2.nd, "Expr");
		
		
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);
		add_brother_node($2.nd, node2);


		}
	|	'-' Expr %prec UMINUS
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		GEN("-", $2.place, 0, $2.place);
		$$.type = $2.type;
		$$.place = $2.place;

		
		struct node*node1;
		complete_init_node(&node1, "-");
		
		set_node_val_str($2.nd, "Expr");
		
		add_son_node($$.nd, node1);
		add_brother_node(node1, $2.nd);

		}
	|	Variable
		{

		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		if (!$1.OFFSET) {
			$$.place = $1.NO;
			$$.type = VarList[$1.NO].type;
			set_node_val_str($1.nd, "Variable");
		}
		else {
			int T = NewTemp();
			GEN("=[]", $1.NO, $1.OFFSET, T);
			$$.place = T;
			$$.type = $1.Array_type;
			set_node_val_str($1.nd, "VariaArray");
		}

		
		add_son_node($$.nd, $1.nd);

		}

	|	Const
		{
		
		struct node* cur;
		complete_init_node(&cur, "NULL");
		$$.nd = cur;
		
		$$.type = $1.type;

		set_node_val_str($1.nd, "Const");
		
		add_son_node($$.nd, $1.nd);
		$$ = $1;

		}
	;


Variable: Iden
		{
			// 文法符号Iden对应标识符，以字母或下划线开头后面是字母、数字或下划线组成的符号串
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			$$.NO = Entry($1);
			
			$$.OFFSET = 0;

			
			struct node *node1;
			complete_init_node(&node1, $1);
			
			add_son_node($$.nd, node1);
		}
	;



Const:	IntNo
		{
			// 常数，无符号整数
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			
			$$.type = INT;
			$$.place = Entry($1); 
			
			VarList[VarCount].type = INT;
			
			struct node *node1;
			complete_init_node(&node1, $1);
			
			add_son_node($$.nd, node1);
		}
	|	RealNo
		{
			// 常数，无符号实数
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;
			
			$$.type = REAL;
			$$.place = Entry($1); 
			
			
			VarList[VarCount].type = REAL;
			
			struct node *node1;
			complete_init_node(&node1, $1);
			
			add_son_node($$.nd, node1);
		}
	;

RelationOp:	'<'
		{
			// 小于
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j<", sizeof("j<"));
			struct node *node1;
			complete_init_node(&node1, "<");

			add_son_node($$.nd, node1);
		}
	|	'>'
		{
			// 大于
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j>", sizeof("j>"));
			
			struct node *node1;
			complete_init_node(&node1, ">");
			
			add_son_node($$.nd, node1);
		}	
	|	'='
		{
			// 等于
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j=", sizeof("j="));
			
			struct node *node1;
			complete_init_node(&node1, "=");
			
			add_son_node($$.nd, node1);
		}
	|	GE
		{
			// 文法符号GE对应大于等于，符号串为">=
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j>=", sizeof("j>="));
			
			struct node *node1;
			complete_init_node(&node1, ">=");
			
			add_son_node($$.nd, node1);
		}
	|	NE 
		{
			// 文法符号NE对应不等于，符号串为"<>""
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j<>", sizeof("j<>"));
			
			struct node *node1;
			complete_init_node(&node1, "<>");
			
			add_son_node($$.nd, node1);
		}
	|	LE
		{
			// 文法符号LE对应小于等于，符号串为"<=""
			struct node* cur;
			complete_init_node(&cur, "NULL");
			$$.nd = cur;

			memcpy($$._Rop, "j<=", sizeof("j<="));
			
			struct node *node1;
			complete_init_node(&node1, "<=");
			
			add_son_node($$.nd, node1);
		}
	;
%%

int yyerror(char *errstr)
{
	printf("\n\n Error: ");
	printf("Line: %d Reason: ", line_number);
	switch(error_number) {
		case REDEFINE_ARRAY :{
			printf("Array %s is redefined!\n", errstr);
			break;
		}
		case REDEFINE_SIM_VAR :{
			printf("Simple Var %s is redefined!\n", errstr);
			break;
		}
		case UNDEFINE_VAR :{
		    printf("Var %s is not defined!\n", errstr);
			break;
		}
		case ILLEGALIDEN :{
		    printf("%s is illegal Identifier!\n", errstr);
			break;
		}
		case UNRE_COG_SYMBOL :{
		    printf("%s can not be recognized!\n", errstr);
			break;
		}
		case BOOL_OP_ERROR :{
		    printf("Bool VAR cannot be %s\n", errstr);
			break;
		}
		case LABEL_REDEF :{
		    printf("%s\n", errstr);
			break;
		}
		case INNER_ERROR :{
		    printf("%s\n", errstr);
			break;
		}
		default :{
			printf("%s\n", errstr);
			break;
		}	
	}
	exit(-1);
	return 0;
}
