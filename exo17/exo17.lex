%{
#include "exo17.h"
extern int lineNumber;
%}

%%

"start"      { return START; }
"end"        { return END; }
"="          { return ASSIGN; }
"+"          { return PLUS; }
"*"          { return MULT; }
"print"          { return PRINT; }
";"          { return SEMICOLON; }
[a-d]  { yylval.sval = yytext; return IDENT; }
[0-9]+"."[0-9]* { yylval.rval = atof(yytext); return REAL; }
[0-9]+      { yylval.ival = atoi(yytext); return INTEGER; }
[ \t\n]     { /* Ignorer les espaces blancs */ }
.           { fprintf(stderr, "Unexpected character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}
