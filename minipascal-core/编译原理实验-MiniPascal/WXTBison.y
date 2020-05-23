%{
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define MAXSTR 20
#define MAXMEMBER 100

#define INTTYPE  0
#define REALTYPE 1

extern int yylex();
extern FILE* yyin;
extern char str1[20];

int FillType(int first,int type);
int Merge(int,int);
void BackPatch(int,int);
int GEN(char*,int,int,int);
void OutputQ(void);
int yyparse();
void OutputIList(void);
int yyerror(char*);
int Entry(char*);
int VarCount=0;//变量个数
FILE* fp;
int NXQ=0;  /* used to indicate the number of next Quater*/



struct QUATERLIST{char op[6];int arg1,arg2,result;} QuaterList[MAXMEMBER];//四元式
struct VARLIST{char name[20];int type;int addr;} VarList[MAXMEMBER];//符号表

%}
%start    ProgDef
%union {
 int Iv;
 int CH;
 int NO;
 struct { int TC,FC;} _BExpr;
 struct { int AC,BC,CC,CH;} _FExpr; //For的属性：AC传递TC，BC传递1，CC传递变量i，CH传递退出链FC
 struct { int QUAD,CH;} _WBD; //while
 struct { int QUAD,CH,D,N;} _FD; //For
 struct { int type,place;/*union{int Iv;float Rv;} Value;*/} _Expr;
 char _Rop[5];
 int First;
 char str[20];
}

%token    	Iden    300
%token    	IntNo	301
%token	  	RealNo  302 //定义终结符：常量符号

%token	  	Program 400
%token	  	Begin	401
%token	  	End	402
%token	  	Var	403
%token	  	Integer 404
%token	  	Real	405
%token	  	While	406
%token		If	407
%token		Else	408
%token		For	409
%token 		To  410 //定义终结符：关键字

%token		LE	500
%token		GE	501
%token		NE	502	//双目运算符终结符

%left  '|'
%left  '&'
%right '!'
%nonassoc '<' '>' '=' LE GE NE
%left '+' '-'
%left '*' '/' '%'
%nonassoc UMINUS  //左右结合

%type <CH> ProgDef
%type <CH> SubProg
%type <CH> VarDef
%type <CH> VarDefList
%type <Iv> Type
%type <First> VarList
%type <CH> Statement
%type <CH> StateList
%type <CH> StateLists
%type <CH> ComplexState
%type <CH> AsignState
%type <CH> I_T_E
%type <CH> I_T
%type <_WBD> Wd
%type <_FD> Fd
%type <_Rop> RelationOp
%type <_Expr> Expr 
%type <CH> W
%type <NO> Varable 
%type <NO> Asign_Varable
%type <_Expr> Const 
%type <_BExpr>	BoolExpr
%type <_FExpr> FExpr
%type <CH> Asignment

%%
ProgDef	:	Program Iden ';' SubProg
			{$$=0;printf("\nCompile successfully!\n");} //若规约到该步则表示LR分析成功
	;

SubProg:   VarDef ';' Begin StateList End
		{BackPatch($4,NXQ);
		 GEN("Stop",0,0,0);
	    }
	|	Begin StateList End
		{BackPatch($2,NXQ);
		 GEN("Stop",0,0,0);
	    }
	;

VarDef	:Var VarDefList 
	     {$$=0;}
	;
VarDefList:	VarDefList VarList{$$=0;}
	|	VarList{$$=0;}
	;
Type	:	Integer{$$=INTTYPE;}
	|	Real{$$=REALTYPE;}
	;
VarList	:  VarList ',' Asignment{FillType($3,$1);}//修改 Varable
	|  VarList ',' Varable{FillType($3,$1);}
	|  Type Asignment{$$=$1 ;FillType($2,$$);}//修改
	|  Type Varable{$$=$1 ;FillType($2,$$);}
	;
Asignment	:	Varable':''='Expr  
            {
			   GEN(":=",$4.place,0,$1);}
	;
StateLists: StateList';'
	{BackPatch($1,NXQ);$$=0;}
	;
StateList:Statement {$$=$1;}
	|StateLists Statement
	        {$$=$2;}
	;
Statement:	AsignState{$$=0;}
	|	I_T_E Statement{$$=Merge($1,$2);}
	|	I_T   Statement{$$=Merge($1,$2);}
	|	Wd Statement   { GEN("j",0,0,$1.QUAD);
		  BackPatch($2,$1.QUAD);
		  $$=$1.CH;}
	|	Fd Statement
		{
		GEN("I+",$1.D,$1.N,$1.D);
		GEN("j",0,0,$1.QUAD);
		$$=$1.CH;}
	|	ComplexState{$$=$1;}
	|	VarDef{$$=0;}
	;
AsignState:	Asign_Varable':''='Expr  

            {
			 if(VarList[$1].type==$4.type)
			   GEN(":=",$4.place,0,$1);
			 else if($4.type==INTTYPE)
			 {
			   int T=NewTemp();
			   GEN("I->R",$4.place,0,T);
			   GEN(":=",T,0,$1);
			 }
			else
			{
			 int T=NewTemp();
			 GEN("R->I",$4.place,0,T);
			 GEN(":=",T,0,$1);
			}
			$$=$1;
	      }
	; 
Asign_Varable:  Varable {$$=$1;}
	;
I_T_E	:	I_T Statement Else{int q=NXQ;GEN("j",0,0,0);BackPatch($1,NXQ);$$=Merge($2,q);}
	;
I_T	:	If '(' BoolExpr ')'{BackPatch($3.TC,NXQ);$$=$3.FC;}
	;
Wd	:	W '(' BoolExpr ')' {BackPatch($3.TC,NXQ);$$.QUAD=$1;$$.CH=$3.FC;}
	;
W	:	While{$$=NXQ;}//将Expr第一四元式序号记录下来，以便在翻译完statement后产生一个跳转到此处的四元式。
	;	//翻译BoolExpr后使用当前NXQ（Statement的第一四元式序号）回填TC链，将FC属性传递给CH属性，方便后续合并和回填。
Fd	:	For '(' FExpr ')'{BackPatch($3.AC,NXQ);$$.QUAD=$3.AC;$$.CH=$3.CH;$$.D=$3.CC;$$.N=$3.BC;}
	;
FExpr	:	AsignState ',' BoolExpr ',' Expr '+' Const{
			$$.AC=$3.TC;$$.CH=$3.FC;$$.CC=$1;$$.BC=$7.place;
			}
	;		
ComplexState:	Begin StateList End
		{
                  $$=$2;
 		}
	;
Expr	:	Expr'+'Expr
		{
		 int T=NewTemp();
		 if($1.type== INTTYPE && $3.type==INTTYPE)
		 {
		  GEN("I+",$1.place,$3.place,T);
		  VarList[T].type=$$.type=INTTYPE;
		 }
		 else if($1.type== REALTYPE && $3.type==REALTYPE)
		 {
		  GEN("R+",$1.place,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else if($1.type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",$1.place,0,U);
		  GEN("R+",U,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",$3.place,0,U);
		  GEN("R+",$3.place,U,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 $$.place=T;
		}
	|	Expr'-'Expr
                {
		 int T=NewTemp();
		 if($1.type== INTTYPE && $3.type==INTTYPE)
		 {
		  GEN("I-",$1.place,$3.place,T);
		  VarList[T].type=$$.type=INTTYPE;
		 }
		 else if($1.type== REALTYPE && $3.type==REALTYPE)
		 {
		  GEN("R-",$1.place,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else if($1.type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",$1.place,0,U);
		  GEN("R-",U,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",$3.place,0,U);
		  GEN("R-",$3.place,U,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 $$.place=T;
		}

	|	Expr'*'Expr
                 {
		 int T=NewTemp();
		 if($1.type== INTTYPE && $3.type==INTTYPE)
		 {
		  GEN("I*",$1.place,$3.place,T);
		  VarList[T].type=$$.type=INTTYPE;
		 }
		 else if($1.type== REALTYPE && $3.type==REALTYPE)
		 {
		  GEN("R*",$1.place,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else if($1.type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",$1.place,0,U);
		  GEN("R*",U,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",$3.place,0,U);
		  GEN("R*",$3.place,U,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 $$.place=T;
		}
	|	Expr'/'Expr
               {
		 int T=NewTemp();
		 if($1.type== INTTYPE && $3.type==INTTYPE)
		 {
		  GEN("I/",$1.place,$3.place,T);
		  VarList[T].type=$$.type=INTTYPE;
		 }
		 else if($1.type== REALTYPE && $3.type==REALTYPE)
		 {
		  GEN("R/",$1.place,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else if($1.type== INTTYPE)
		 {
		  int U=NewTemp();
		  GEN("I->R",$1.place,0,U);
		  GEN("R/",U,$3.place,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 else
		 {
		  int U=NewTemp();
		  GEN("I->R",$3.place,0,U);
		  GEN("R/",$3.place,U,T);
		  VarList[T].type=$$.type=REALTYPE;
		 }
		 $$.place=T;
		}
	|	Expr'%'Expr
                {
		 int T=NewTemp();
		 if($1.type== INTTYPE && $3.type==INTTYPE)
		 {
		  GEN("I%",$1.place,$3.place,T);
		  VarList[T].type=$$.type=INTTYPE;
		  $$.place=T;
                 }
		
		}
	|	'('Expr')'
                {
		 $$=$2;
		}
	|	'-' Expr %prec UMINUS  
                {
		 int T=NewTemp();
		 $$=$2;
		 GEN("Minus",$2.place,0,T);
		 $$.place=T;VarList[T].type=VarList[$2.place].type;
		}
	|	Varable
                {
		 $$.place=$1;
		 $$.type=VarList[$1].type;
		}
	|	Const
                { $$=$1;}
	;
BoolExpr	:	Expr RelationOp Expr
                {
		 $$.TC=NXQ;$$.FC=NXQ+1;
		 GEN($2,$1.place,$3.place,0);
		 GEN("j",0,0,0);
		}
	|	BoolExpr '&' 
                {BackPatch($1.TC,NXQ);}
        BoolExpr{$$.TC=$4.TC;$$.FC=Merge($1.FC,$4.FC);}
	|	BoolExpr '|' {BackPatch($1.FC,NXQ);}
                BoolExpr{$$.FC=$4.FC;$$.TC=Merge($1.TC,$4.TC);}	
	|	'!' BoolExpr
                 {$$.TC=$2.FC;$$.FC=$2.TC;}
	|	'(' BoolExpr ')'{$$=$2;}
	;
Varable	: Iden
          { 
		    $$=Entry(str1);
	    	}
	;
Const	:	IntNo
		{ int i=Entry(str1);
		  $$.type=VarList[i].type=INTTYPE;
		  $$.place=i;
		}
	|	RealNo
		{ int i=Entry(str1);
		  $$.type=VarList[i].type=REALTYPE;
		  $$.place=i;
		}
	;
RelationOp:	'<'{strcpy($$,"j<");}
	|	'>'{strcpy($$,"j>");}
	|	'='{strcpy($$,"j=");}
	|	GE  {strcpy($$,"j>=");}
	|	NE  {strcpy($$,"j!=");}
	|	LE  {strcpy($$,"j<=");}
	;


%%
/*int yylex(void)
{ 
}
*/
void OutputQ(void) //输出四元式
{int i;
 for(i=0;i<NXQ;i++)
 {
  printf("(%3d) ( %5s, ",i,QuaterList[i].op);
  if(QuaterList[i].arg1)
	printf("%6s, ",VarList[QuaterList[i].arg1].name);
	else printf("      , ");
  if(QuaterList[i].arg2)
	printf("%6s, ",VarList[QuaterList[i].arg2].name);
	else printf("      , ");
  if((QuaterList[i].op[0]=='j')||(QuaterList[i].op[0]=='S')) 
		printf("%6d )\n",QuaterList[i].result);
   else if(QuaterList[i].result)
	printf("%6s )\n",VarList[QuaterList[i].result].name);
	else printf("-\t )\n");
 }
 return;
}



int yyerror(char *errstr)  
{
          printf(" %s\n",errstr);
          return 0;
}

int Entry(char *name) //将变量名填入符号表
{int i;
 for(i=1;i<=VarCount;i++) if(!strcmp(name,VarList[i].name)) return i;
 if(++VarCount>MAXMEMBER) {printf("Too many Variables!\n");exit(-1);}
 strcpy(VarList[VarCount].name,name);
 return VarCount;
}

int FillType(int first,int type)
{ int i;
  for(i=first;i<=VarCount;i++)
    VarList[i].type=type;
  return i-1;
}
int Merge(int p,int q)
{
 int r;
 if(!q) return p;
  else
  {
   r=q;
   while(QuaterList[r].result)
    r=QuaterList[r].result;
   QuaterList[r].result=p;
  }
 return q;
}
void BackPatch(int p,int t)
{
 int q=p;
 while(q)
 { int q1=QuaterList[q].result;
   QuaterList[q].result=t;
   q=q1;
 } 
 return;
}
int GEN(char* op,int a1,int a2,int re)
{
 strcpy(QuaterList[NXQ].op,op);
 QuaterList[NXQ].arg1=a1;
 QuaterList[NXQ].arg2=a2;
 QuaterList[NXQ].result=re;
 NXQ++;
 return NXQ;
}

int NewTemp()
{
 static int no=0;
 char Tname[10];
 sprintf(Tname,"_T%o",no++);
 return Entry(Tname);
}

void OutputIList(void)
{
 int i;
 printf(" No.\t name \t\t   type\n");
 for(i=1;i<=VarCount;i++)
  {
   printf("%4d\t%6s\t\t",i,VarList[i].name);
   if(VarList[i].type) printf(" REAL  \n");else printf(" INTEGER\n"); 
  }
 return;
}

int main(int argc, char *argv[])
{
 yyin=NULL;
 if(argc>1)
 {
  if((yyin=fopen(argv[1],"r"))==NULL)
  {printf("Can't open file %s\n",argv[1]);exit(0);}
  }
  yyin=fopen("Mini.txt","r");
	if(yyin==NULL){
	    printf("Can't open file Mini.txt\n");
		return -1;
	}
 yyparse();
 printf("\n");
 OutputQ();
 OutputIList();
 getchar();
 return;
}