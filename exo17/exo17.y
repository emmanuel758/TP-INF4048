%{
/*-------- prog.y --------*/
#include <stdio.h>
#include <stdlib.h>

int yylex(void); // defini dans progL.c, utilise par yyparse()
void yyerror(const char * msg); // defini plus loin, utilise par yyparse()
int lineNumber; // notre compteur de lignes
int var[4];
extern FILE * yyin; // defini dans progL.c, utilise par main()
%}

%union {
    int ival;
    double rval;
    char *sval;
}

%token <ival> INTEGER
%token <rval> REAL
%token <sval> IDENT
%token START END // les lexemes que doit fournir yylex()
%token ASSIGN SEMICOLON PRINT PLUS MULT

%type <ival> E T F


%start program // l’axiome de notre grammaire
%%

program : instList { printf("program\n"); }
;

instList : instList inst
         | inst
         ;

inst : IDENT ASSIGN E SEMICOLON { printf("assign %s with %d \n",$1,$3); }
     | PRINT F SEMICOLON {printf("print \n");}
     ;

/*expr : INTEGER { printf("integer expr $$ i:%d \n", $1); }
     | REAL { printf("real expr $$ r:%g \n", $1); }
     | IDENT { printf("ident expr $$ s:%s \n", $1); }
     ;*/

E: E PLUS T { $$=$1+$3; printf("\n reduce E -> E + T , %d + %d = %d \n", $1,$3,$$); }
 | T { printf("\n reduce E -> T \n");}

T: T MULT F {$$=$1*$3; printf("\n reduce T -> T * F , %d * %d = %d \n", $1,$3,$$);}
 | F { printf("\n reduce T -> F \n"); }

F: INTEGER {$$=$1; printf("integer expr $$ i:%d \n", $1); } | IDENT {printf("\n reduce F ----> var %s \n", $1); }
%%

void yyerror(const char * msg)
{
    printf("line %d: %s\n", lineNumber, msg);
}

int main(int argc, char ** argv)
{
    if (argc > 1) yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror(argv[1]);
        return 1;
    }
    lineNumber = 1;
    if (!yyparse()) printf("Success\n");
    return 0;
}
