%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "simple.h"

    // Déclaration de la variable `yyin`
    extern FILE *yyin;
%}

%token INTEGER OPPLUS OPMULT OPMINUS // Les lexemes que doit retourner yylex

%start S // L'axiome de notre programme

%%
S: E {printf("\n reduce S -> E, Accept !! \n");}

E: E OPPLUS T { printf("\n reduce E -> E + T \t --------- \t $1=%d, $2=%d, $3=%d, $$=%d", $1,$2,$3,$$);}
 | T { printf("\n reduce E -> T \t ---------  \t $1=%d, $$=%d", $1, $$);}

T: T OPMULT F {printf("\n reduce T -> T * F \t ---------  \t $1=%d, $2=%d, $3=%d, $$=%d", $1, $2, $3, $$);}
 | F { printf("\n reduce T -> F \t --------- \t $1=%d, $$=%d", $1, $$); }

F: INTEGER { printf("\n reduce F -> int \t --------- \t $1=%d, $$=%d", $1, $$); }
%%

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: ./exo15 %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        exit(1);
    }

    // Redirige l'entrée du lexer vers le fichier
    yyin = file;

    // Lance l'analyse
    yyparse();

    fclose(file);
    return 0;
}

int yyerror(char *msg)
{
    printf("erro parsing %s \n", msg);
    return 0;
}
