%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*类型 标识符 整型 实型*/
#define    	Iden    	300
#define    	IntNo		301
#define	  	RealNo  	302
/*关键字*/
#define	  	Program 	400
#define	  	Begin	401
#define	  	End	402
#define	  	Var	403
#define	  	Integer 	404
#define	  	Real	405
#define	  	While	406
#define		If	407
#define		Else	408
#define		For 409
#define 	To 410

/*双目运算符*/
#define		LE	500
#define		GE	501
#define		NE	502
#define		ERRORCHAR	600

#define MAXSTR 20

/* 这个数组用来确认标识符是否为关键字 */

char str1[20]; /* 此数组用于存储标识符或的字符串

整数或实数。当其中一个出现在yytext中，

复制到str1。str1将在YACC源文件中使用

(filename.y YSP文件) */
int id_or_keyword(char *name);/*检查名称是否为关键字*/
%}
letter      [A-Za-z]
alnum		[A-Za-z0-9]
d			[0-9]
white		[\t\n\040]
%start		COMMENT
%%
	/* 下面的规则用于识别注释行*/
\{			{ECHO;BEGIN COMMENT;} /*ECHO:存入yyout*/
<COMMENT>\}		{ECHO;BEGIN 0;}
<COMMENT>\n		{ECHO;}
<COMMENT>[^\}]+ 	{ECHO;} /*去注释*/
	/* 为所有Vt符号定义其他识别规则

并写出相应的语义动作

例如:	*/
[Bb][eE][Gg][iI][Nn]	{ECHO;return Begin;}
[eE][Nn][Dd]		{ECHO;return End;}
[Pp][Rr][oO][Gg][Rr][Aa][Mm]	{ECHO;return Program;}
[Vv][Aa][Rr]		{ECHO;return Var;}
[Ii][nN][Tt][eE][Gg][eE][Rr]	{ECHO;return Integer;}
[Rr][eE][Aa][lL]	{ECHO;return Real;}
[Ww][Hh][Ii][Ll][Ee]	{ECHO;return While;}
[iI][Ff]		{ECHO;return If;}
[Ee][Ll][Ss][Ee]	{ECHO;return Else;}
[Ff][Oo][Rr]	{ECHO;return For;}
[Tt][Oo]	{ECHO;return To;}

({d}+(\.{d}*)?[Ee]([+-])?{d}+)|({d}*\.{d}+[Ee]([+-])?{d}+)	{ECHO;strcpy(str1,yytext);return RealNo;}
{d}+\.{d}*|{d}*\.{d}+		{ECHO;strcpy(str1,yytext);return RealNo;}
{d}+			{ECHO;strcpy(str1,yytext);return IntNo;}

"("			{ECHO;return '(';}
")"			{ECHO;return ')';}
"["			{ECHO;return '[';}
"]"			{ECHO;return ']';}
">"			{ECHO;return '>';}
"<"			{ECHO;return '<';}
"="			{ECHO;return '=';}
"<="		{ECHO;return LE;}
">="		{ECHO;return GE;}
"!="		{ECHO;return NE;}
":"			{ECHO;return ':';}
";"			{ECHO;return ';';}
"\."		{ECHO;return '.';}
"*"			{ECHO;return '*';}
"+"			{ECHO;return '+';}
"-"			{ECHO;return '-';}
"/"			{ECHO;return '/';}
"%"			{ECHO;return '%';}
","			{ECHO;return ',';} 
"&"         {ECHO;return '&';}
"|"         {ECHO;return '|';}
"!"         {ECHO;return '!';}   

{letter}{alnum}*	{ ECHO;strcpy(str1,yytext);return Iden;} /*标识符*/
{white}+		{ECHO;}
.			{printf("Invalid char %s\n",yytext);
			 return ERRORCHAR;
			}
%%


#ifndef yywrap
 int yywrap(){return 1;}
#endif
