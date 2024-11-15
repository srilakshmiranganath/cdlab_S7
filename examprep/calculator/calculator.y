%{
#include<stdio.h>
int flag=0;
void yyerror();
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
ArithmeticExpression: E{
    printf("Result = \n", $$);
    return 0;
    };
E:E '+' E {$$=$1+$3;}
|E '-' E {$$=$1-$3;}
|E '*' E {$$=$1*$3;}
|E '/' E {$$=$1/$3;}
|E '%' E {$$=$1%$3;}
| '(' E ')' {$$=$2;}
|NUMBER {$$=$1;}
;
%%

void main(){
    printf("Enter expression : ");
    yyparse();
    if(flag==0){
        printf("Expression vallid\n");
    }
}

void yyerror(){
    printf("Expression invalid\n");
    flag=1;
}