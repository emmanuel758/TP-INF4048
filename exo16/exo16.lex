
%{
    #include<stdio.h>
    #include "simple.h"
%}

integer [0-9]+
operator \+|\*|\-

%%
{integer} {yylval=atoi(yytext); return INTEGER;}
"+" {return PLUS;}
"*" {return MULT;}
"-" {return MINUS;}
. { printf("Unknow %s \n",yytext); }
%%
