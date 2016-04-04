%{
#define YYSTYPE void*
#include "calc.tab.h"
#include <stdlib.h>


void *createValue(double);

%}

white [ \t]+
digit [0-9]
integer {digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%%

{white} { }
{real} {
	yylval=createValue(atof(yytext)); 
	return NUMBER;
}

"+" return PLUS;
"-" return MINUS;
"*" return TIMES;
"/" return DIVIDE;
"^" return POWER;
"(" return LPAREN;
")" return RPAREN;
"\n" return END;



