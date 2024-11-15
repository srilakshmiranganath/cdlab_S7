%{
#include <stdio.h>
#include <stdlib.h>
%}

%%

"sril"         { 
    printf("Forbidden substring 'sril' found!\n");
    exit(1);  
}

.              { 
    putchar(yytext[0]);  
}

\n             { 
    putchar('\n');  
}

%% 

int main(int argc, char **argv) {
    printf("Enter strings (Ctrl+D to end):\n");
    yylex();  
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}