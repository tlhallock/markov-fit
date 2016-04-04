%{
#include <cmath>
#include <iostream>
#include <cstdlib>
#include "../expressions.h"

extern "C"
{
        int yyparse(void);
        int yylex(void);  
        int yywrap()
        {
                return 1;
        }
		extern FILE *yyin;
//		YY_FLUSH_BUFFER;
		ExpressionRename *parse_results;
		int yyerror(const char *s);
}


#define YYSTYPE ExpressionRename*
%}

%token NUMBER
%token PLUS MINUS TIMES DIVIDE POWER
%token LPAREN RPAREN
%token END

%left PLUS MINUS
%left TIMES DIVIDE
%left NEG
%right POWER

%start Input
%%

Input:
     END
     | Expression END { parse_results = $1; }
;

Expression:
     NUMBER { $$=$1; }
| Expression PLUS Expression { $$=new ExprAddition{$1,$3}; }
| Expression MINUS Expression { $$=new ExprSubtraction{$1, $3}; }
| Expression TIMES Expression { $$=new ExprMultiply{$1,$3}; }
| Expression DIVIDE Expression { $$=new ExprDivision{$1,$3}; }
| MINUS Expression %prec NEG { $$=new ExprNegation{$2}; }
| Expression POWER Expression { $$=new ExprPower{$1,$3}; }
| LPAREN Expression RPAREN { $$=$2; }
;

%%

int yyerror(const char *s) {
  printf("%s\n", s);
}

// FILE *outFile_p;

ExpressionRename *parse(const char *file)
{

	parse_results = nullptr;
	FILE *fp=fopen(file, "r");
	if(!fp)
	{
		printf("couldn't open file for reading\n");
		return nullptr;
	}
 
//  outFile_p=fopen(argv[2],"w");
//  if(!outFile_p)
//  {
//   printf("couldn't open temp for writting\n");
//   exit(0);
//  }

	yyin=fp;
	yyparse();
	fclose(fp);
 //YY_FLUSH_BUFFER;
 
 //fclose(outFile_p);
 
	return parse_results;
}