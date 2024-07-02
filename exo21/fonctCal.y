%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Déclaration de la variable globale pour stocker le résultat
int result;

// Déclaration de la fonction externe pour convertir un entier en ASCII
extern void int_to_ascii(int num, char *buffer);
%}

%union {
    int intval;     // Pour stocker les valeurs entières
    char operator;  // Pour stocker les opérateurs
}

%token <intval> NUM
%token <operator> PLUS MULT


%%
expr: NUM                { $$ = $1; }         // Stocker la valeur NUM dans $$ (équivalent à $$
    | expr PLUS expr     { $$ = $1 + $3;     // Addition
                           printf("    ; Ajouter %d à eax\n", $3);
                           printf("    add eax, %d\n", $3); }
    | expr MULT expr     { $$ = $1 * $3;     // Multiplication
                           printf("    ; Multiplier eax par %d\n", $3);
                           printf("    imul eax, %d\n", $3); }
    ;

%%
int main() {
    printf("Entrez une expression : ");
    yyparse();

    // Conversion du résultat en chaîne de caractères pour affichage
    char buffer[10];
    int_to_ascii(result, buffer);

    // Affichage du résultat
    printf("Resultat : %s\n", buffer);

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Erreur syntaxique : %s\n", s);
}
