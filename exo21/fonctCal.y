%{
#include <stdio.h>
#include "fonctCal.tab.h"  // Assurez-vous que c'est le bon chemin vers votre fichier lex.yy.h
%}

%token NUM
%left '+' '-'
%left '*' '/'

%%

expr: NUM { printf("Résultat : %d\n", $1); }
    | expr '+' NUM { printf("Addition : %d + %d\n", $1, $3); }
    | expr '*' NUM { printf("Multiplication : %d * %d\n", $1, $3); }
    ;

%%

int main() {
    yyparse();
    return 0;
}
