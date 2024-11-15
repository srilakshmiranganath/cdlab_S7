%{
    #include <stdio.h>
    #include <stdlib.h>

    void yyerror(const char *s);

    int yylex(void);

    int flag = 0;
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

ArithmeticExpression:
    E {
        printf("\nResult = %d\n", $1);
        return 0;
    }
;

E:
    E '+' E { $$ = $1 + $3; }
    | E '-' E { $$ = $1 - $3; }
    | E '*' E { $$ = $1 * $3; }
    | E'/' E {
        if ($3 == 0) {
            yyerror("Division by zero");
            YYABORT;
        }
        $$ = $1 / $3;
    }
    | E '%' E {
        if ($3 == 0) {
            yyerror("Division by zero");
            YYABORT;
        }
        $$ = $1 % $3;
    }
    | '(' E ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
;

%%

int main() {
    printf("Enter expression : ");
    yyparse();
    if (flag == 0) {
        printf("\n Valid");
    }
    return 0;
}

void yyerror(const char *s) {
    printf("\n Invalid : %s\n", s);
    flag = 1;
}