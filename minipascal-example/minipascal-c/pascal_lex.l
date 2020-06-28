%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "pascal_yacc.h"
#include "util.h"
#include "table.h"


extern int yyerror(char *errstr);



%}

letter		[A-Za-z_]
alnum		[A-Za-z0-9_]
d			[0-9]
white		[\t\n\040]
%start		COMMENT

%%

\{				{ECHO;BEGIN COMMENT;}
<COMMENT>\}		{ECHO;BEGIN(INITIAL);}
<COMMENT>\n		{ECHO;++line_number;}
<COMMENT>[^}]+ 	{ECHO;}


[Bb][Ee][Gg][Ii][Nn]					{ECHO;VarFlag = 1; return Begin;}
[Ee][Nn][Dd]							{ECHO;return End;}
[Pp][Rr][Oo][Gg][Rr][Aa][Mm]			{ECHO;return Program;}
[Vv][Aa][Rr]							{ECHO;return Var;}
[Ii][nN][Tt][eE][Gg][eE][Rr]			{ECHO;return Integer;}
[Rr][eE][Aa][Ll]						{ECHO;return Real;}
[Ww][Hh][Ii][Ll][Ee]					{ECHO;return While;}
[Dd][Oo]								{ECHO;return Do;}
[Ii][Ff]								{ECHO;return If;}
[Tt][Hh][Ee][Nn]						{ECHO;return Then;}
[Ee][Ll][Ss][Ee]						{ECHO;return Else;}
[Aa][Nn][Dd]							{ECHO;return And;}
[Oo][Rr]								{ECHO;return Or;}
[Nn][Oo][Tt]							{ECHO;return Not;}

\'.\'	 													{ECHO;strcpy(yylval.str,yytext);return CHAR;}
({d}+(\.{d}*)?[Ee]([+-])?{d}+)|({d}*\.{d}+[Ee]([+-])?{d}+)	{ECHO;strcpy(yylval.str,yytext);return RealNo;}
{d}+\.{d}*|{d}*\.{d}+										{ECHO;strcpy(yylval.str,yytext);return RealNo;}
{d}+														{ECHO;strcpy(yylval.str,yytext);return IntNo;}
{d}+[" "\t]*\.\.[" "\t]*{d}+     


"("			{ECHO;return '(';}
")"			{ECHO;return ')';}
"["			{ECHO;return '[';}
"]"			{ECHO;return ']';}
">"			{ECHO;return '>';}
"<"			{ECHO;return '<';}
"="			{ECHO;return '=';}
"<="		{ECHO;return LE;}
">="		{ECHO;return GE;}
"<>"		{ECHO;return NE;}
":="		{ECHO;return ASSIGNOP;}
":"			{ECHO;return ':';}
";"			{ECHO;return ';';}
"\."		{ECHO;return '.';}
"*"			{ECHO;return '*';}
"+"			{ECHO;return '+';}
"-"			{ECHO;return '-';}
"/"			{ECHO;return '/';}
"%"			{ECHO;return '%';}
","			{ECHO;return ',';}
"\n"            {ECHO;++line_number;}
{letter}{alnum}*	{ ECHO;strcpy(yylval.str,yytext); return Iden;}
{white}+			{ECHO;}
{d}+{letter}+[alnum]*   {error_number = ILLEGALIDEN ;yyerror(yytext); return ERRORCHAR; }


%%

#ifndef yywrap
int yywrap()
{
	return 1;
}
#endif
