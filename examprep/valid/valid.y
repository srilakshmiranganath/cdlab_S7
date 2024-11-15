%{
    #include<stdio.h>
    int valid=1;
    int yyerror();    
%}

%token letter digit

%%
    start : letter s
    s : letter s
        | digit s
        |
        ;
%%

int yyerror(){
    printf("Not an Identifier\n");
    valid = 0;
    return 0;
}

int main(){
    printf("Enter name to test : ");
    yyparse();
    if(valid){
        printf("Valid Identifier\n");
    }
}