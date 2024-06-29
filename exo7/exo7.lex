
%{
/*code qui sera rajouté en haut du fichier généré*/
#include<stdio.h>
%}

/* entier*/
entier [0-9]+

/*operateur*/
operateur  \+|\*|\-

%%
{entier}     printf("<int:%s>",yytext);
{operateur}  printf("<operateur:%s>", yytext);
.;
[\n];

%%
/* code ajouté en bas du parseur*/
int main(int argc, char **argv)
{
	printf("\n");
	yylex();
	printf("\n");
	return 0;
}
