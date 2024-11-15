%{
#include<stdio.h>
#include<stdlib.h>

char name[5];
int ignore_flag = 0;

void update_ignore_flag(char *input){
    if(strstr(input, name) != NULL){
        ignore_flag = 1;
    }
    else{
        ignore_flag = 0;
    }
}
%}

%%
.*\n {
    update_ignore_flag(yytext);
    if(!ignore_flag){
        printf("Valid string : %s", yytext);
    }
    else{
        printf("Invalid string : %s", yytext);
    }
}
%%

int main(){
    printf("Enter string to be ignored : ");
    scanf("%4s", name);

    yylex();

    return 0;
}