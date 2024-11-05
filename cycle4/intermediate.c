#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0, j = 0, no = 0, tmpch = 't';

char str[100], left[15], right[15];

void findopr();
void explore();
void fleft(int);
void fright(int);

struct exp {
    int pos;
    char op;
} k[15];

void main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");

    printf("Enter the Expression : ");
    scanf("%s", str);

    printf("The intermediate code:\n");

    findopr();
    explore();
}

void findopr() {
    // Process operators with precedence order
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*' || str[i] == '/') {
            k[j].pos = i;
            k[j++].op = str[i];
        }
    }
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+' || str[i] == '-') {
            k[j].pos = i;
            k[j++].op = str[i];
        }
    }
}

void explore() {
    i = 0;

    while (k[i].op != '\0') {
        fleft(k[i].pos);
        fright(k[i].pos);

        str[k[i].pos] = tmpch--;  // Generate a new temporary variable

        printf("\t%c := %s %c %s\n", str[k[i].pos], left, k[i].op, right);
        i++;
    }

    // Handle the final result
    // if (no == 0) {
    //     fright(-1);
    //     printf("\t%s := %s\n", right, left);
    //     exit(0);
    // }

    //printf("\t%s := %c\n", right, str[k[--i].pos]);
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;  // Move to the left of the operator

    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '=' && str[x] != '\0' && str[x] != '-' && str[x] != '/' && str[x] != ':') {
        if (str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';  // Mark it as visited
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;  // Move to the right of the operator

    while (x != -1 && str[x] != '+' && str[x] != '*' && str[x] != '\0' && str[x] != '=' && str[x] != ':' && str[x] != '-' && str[x] != '/') {
        if (str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';  // Mark it as visited
            flag = 1;
        }
        x++;
    }
}


/*
Output
                INTERMEDIATE CODE GENERATION

Enter the Expression : a*b+c/d-e/f+g*h
The intermediate code:
        t := a * b
        s := c / d
        r := e / f
        q := g * h
        p := t + s
        o := p - r
        n := o + q
*/