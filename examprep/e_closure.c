#include<stdio.h>
#include<stdlib.h>

struct node{
    int st;
    struct node *link;
};

static int set[20], noalpha, nostates, s, notransitions, r, buffer[20];
static char c;
char alphabet[20];
static int e_closure[20][20] = {0};
struct node *transitions[20][20] = {NULL};

int findclosure(int x, int sta){
    int i;
    struct node *temp;
    if(buffer[x]){
        return;
    }

    e_closure[sta][c++] = x;
    buffer[x] = 1;

    if(alphabet[noalpha-1] == 'e' && transitions[x][noalpha-1] != NULL){
        temp = transitions[x][noalpha-1];
        while(temp != NULL){
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}


int findalpha(char c)
{
    int i;
    for (i = 0; i < noalpha; i++)
        if (alphabet[i] == c)
            return i;

    return (999);
}

void insert_transition_table(int r, char c, int s){
    int j;
    struct node *temp;
    j = findalpha(c);
    if(j == 999){
        printf("Error\n");
        exit(0);
    }
    temp = (struct node*)malloc(sizeof(struct node));
    temp -> st = s;
    temp -> link = transitions[r][j];
    transitions[r][j] = temp;
}

void print_e_closure(int i){
    int j;
    printf("{");
    for(j=0; e_closure[i][j] != 0; j++){
        printf("q%d, ", e_closure[i][j]);
    }
    printf("}\n");
}

void main(){
    int i, j, k, m, t, n;
    struct node *temp;
    printf("Enter number of alphabets : ");
    scanf("%d", &noalpha);
    getchar();
    printf("Enter all alphabets, if epsilon present, add it as 'e' at the end.\n");
    printf("Enter the alphabets : ");
    for(i=0; i<noalpha; i++){
        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter number of states : ");
    scanf("%d", &nostates);

    printf("Enter number of transitions : ");
    scanf("%d", &notransitions);

    printf("Transitions should be entered in the format state symbol state, separated by space.");
    printf("Enter transitions : \n");
    for(i=0; i<notransitions; i++){
        scanf("%d %c %d", &r, &c, &s);
        insert_transition_table(r, c, s);
    }
    
    printf("Epsilon closure\n");
    printf("-----------------\n");
    printf("\n");

    for(i=1; i<=nostates; i++){
        c = 0;
        for(j=0; j<20; j++){
            e_closure[i][j] = 0;
            buffer[j] = 0;
        }
        findclosure(i, i);
        printf("q%d : ", i);
        print_e_closure(i);
    }
}

// #include <stdio.h>
// #include <stdlib.h>
// struct node
// {
//     int st;
//     struct node *link;
// };

// static int set[20], nostate, noalpha, s, notransition, r, buffer[20];
// static char c;
// char alphabet[20];
// static int e_closure[20][20] = {0};
// struct node *transition[20][20] = {NULL};

// void findclosure(int x, int sta)
// {
//     struct node *temp;
//     int i;
//     if (buffer[x])
//         return;
//     e_closure[sta][c++] = x;
//     buffer[x] = 1;
//     if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL)
//     {
//         temp = transition[x][noalpha - 1];
//         while (temp != NULL)
//         {
//             findclosure(temp->st, sta);
//             temp = temp->link;
//         }
//     }
// }

// int findalpha(char c)
// {
//     int i;
//     for (i = 0; i < noalpha; i++)
//         if (alphabet[i] == c)
//             return i;

//     return (999);
// }

// void insert_trantbl(int r, char c, int s)
// {
//     int j;
//     struct node *temp;
//     j = findalpha(c);
//     if (j == 999)
//     {
//         printf("error\n");
//         exit(0);
//     }
//     temp = (struct node *)malloc(sizeof(struct node));
//     temp->st = s;
//     temp->link = transition[r][j];
//     transition[r][j] = temp;
// }

// void print_e_closure(int i)
// {
//     int j;
//     printf("{");
//     for (j = 0; e_closure[i][j] != 0; j++)
//         printf("q%d,", e_closure[i][j]);
//     printf("}");
// }

// void main()
// {
//     int i, j, k, m, t, n;
//     struct node *temp;
//     printf("Enter the number of alphabets?\n");
//     scanf("%d", &noalpha);
//     getchar();
//     printf("NOTE:- [ use letter e as epsilon]\n");
//     printf("NOTE:- [e must be last character ,if it is present]\n");
//     printf("\nEnter alphabets?\n");
//     for (i = 0; i < noalpha; i++)
//     {
//         alphabet[i] = getchar();
//         getchar();
//     }
//     printf("\nEnter the number of states?\n");
//     scanf("%d", &nostate);
//     printf("\nEnter no of transition?\n");
//     scanf("%d", &notransition);
//     printf("NOTE:- [Transition is in the form-> qno alphabet qno]\n");
//     printf("NOTE:- [States number must be greater than zero]\n");
//     printf("\nEnter transition?\n");
//     for (i = 0; i < notransition; i++)
//     {
//         scanf("%d %c %d", &r, &c, &s);
//         insert_trantbl(r, c, s);
//     }
//     printf("\n");
//     printf("e-closure of states……\n");
//     printf("—————————–\n");
//     for (i = 1; i <= nostate; i++)
//     {
//         c = 0;
//         for (j = 0; j < 20; j++)
//         {
//             buffer[j] = 0;
//             e_closure[i][j] = 0;
//         }
//         findclosure(i, i);
//         printf("\ne-closure(q%d): ", i);
//         print_e_closure(i);
//     }
// }