%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "pascal_yacc.h"
#include "table.h"

/* 行号 */
int line_no = 1;

%}

/* 语言不区分大小写 */
A [aA]
B [bB]
C [cC]
D [dD]
E [eE]
F [fF]
G [gG]
H [hH]
I [iI]
J [jJ]
K [kK]
L [lL]
M [mM]
N [nN]
O [oO]
P [pP]
Q [qQ]
R [rR]
S [sS]
T [tT]
U [uU]
V [vV]
W [wW]
X [xX]
Y [yY]
Z [zZ]
NQUOTE [^']

%%

{A}{N}{D}  { return(And); }

":="   { return(ASSIGNOP); }

"."    { return('.'); }

[0-9]+  { return(IntNo); }

\n    { line_no++; }

[ \t\f]  { ; }

.	{printf("Invalid char %s\n",yytext);return ERRORCHAR; }

%%

#ifndef yywrap
int yywrap()
{
	return 1;
}
#endif
