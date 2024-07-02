%{
    #include<stdio.h>
    #include "simple.h"
%}

integer [0-9]+
operator \+|\*|\-

%%
{integer} {yylval=atoi(yytext); return INTEGER;}
"+" {return OPPLUS;}
"*" {return OPMULT;}
"-" {return OPMINUS;}
. { printf("Unknow %s \n",yytext); }
%%

