%{
#include<stdio.h>
#include "fonctCal.tab.h"
%}

%option noyywrap

%%

[ \t\n]          ; // Ignorer les espaces, tabulations et sauts de ligne

[0-9]+           { yylval = atoi(yytext); return INTEGER; } // Reconnaître les nombres entiers et retourner le token INTEGER

\+|\*|\=|\;|\=\=|\!\=|\<|\>   { return *yytext; }         // Reconnaître les opérateurs

\(|\)             { return *yytext; }                    // Reconnaître les parenthèses

[a-d]             { return *yytext; }                    // Reconnaître les variables a, b, c, d

.                 { fprintf(stderr, "Caractère inconnu: %s\n", yytext); }

%%

/* Instructions après la définition des règles lexicales */

int yywrap(void) {
    return 1;
}
