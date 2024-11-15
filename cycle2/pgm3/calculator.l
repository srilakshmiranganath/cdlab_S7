%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "y.tab.h"
    extern int yyval; 
%}

%%

[0-9]+ {
    yyval = atoi(yytext);
    return NUMBER;
}

[\t]+ ;

\n { return 0; }

. { return yytext[0]; }

%%

int yywrap() {
    return 1;
}