%{
#include<stdio.h>
#include "y.tab.c" 
extern int yyval;   
%}

%%
[0-9]+ {
    yyval=atoi(yytext);
    return NUMBER;
}
[\t] ;
[\n] {return 0;}
. return yytext[0];
%%

int yywrap(){
    return 1;
}