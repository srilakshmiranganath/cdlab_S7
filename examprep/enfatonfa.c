#include<stdio.h>
#include<stdlib.h>

struct node{
    int st;
    struct node *link;
};

static int nostate, noalpha, nofinal, notransitions, finalstates[20], set[20], buffer[20], r, s, start, c;
char alphabet[20];
static int e_closure[20][20] = {0};
struct node *transition[20][20] = {NULL};

int findclosure(int x, int sta){
    int i;
    struct node *temp;

    if(buffer[x]){
        return;
    }

    e_closure[sta][c++] = x;
    buffer[x] = 1;

    if(alphabet[noalpha-1] == 'e' && transition[x][noalpha-1] != NULL){
        temp = transition[x][noalpha - 1];
        while(temp!=NULL){
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

int findalpha(char c){
    int j;
    for(j=0; j<noalpha; j++){
        if(alphabet[j] == c) { 
            return j;
        }
    }
    return (999);
}

int insert_trantbl(int r, char c, int s){
    int j;
    struct node *temp;

    j = findalpha(c);
    if(j == 999){
        printf("error\n");
        exit(0);
    }

    temp = (struct node*)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

void unionclosure(int i){
    int j=0, k;
    while(e_closure[i][j] != 0){
        k = e_closure[i][j];
        set[k] = 1;
        j++;
    }
}

void print_e_closure(int i){
    int j=0;
    printf("{");
    if(e_closure[i][j] != 0){
        printf("q%d,", e_closure[i][0]);
    }
    printf("}\t");
}

void findfinalstate(){
    int i, j, k;
    for(i=0; i<nofinal; i++){
        for(j=1; j<=nostate; j++){
            for(k=0; e_closure[j][k] != 0; k++){
                if(e_closure[j][k] == finalstates[i]){
                    print_e_closure(j);
                }
            }
        }
    }
}

void main(){
    int i, j, k, m, t, n;
    struct node *temp;
    printf("Enter number of alphabets : ");
    scanf("%d", &noalpha);
    getchar();
    printf("Enter all alphabets, if epsilon present, add it as 'e' at the end.\n");
    printf("Enter the alphabets : \n");
    for(i=0; i<noalpha; i++){
        alphabet[i] = getchar();
        getchar();
    }
    printf("Enter number of states : ");
    scanf("%d", &nostate);

    printf("Enter start state : ");
    scanf("%d", &start);

    printf("Enter number of final states : ");
    scanf("%d", &nofinal);

    printf("Enter final states : \n");
    for(i=0; i<nofinal; i++){
        scanf("%d", &finalstates[i]);
    }

    printf("Enter number of transitions : ");
    scanf("%d", &notransitions);

    printf("Transitions should be entered in the format state symbol state, separated by space.");
    printf("Enter transitions : \n");
    for(i=0; i<notransitions; i++){
        scanf("%d %c %d", &r, &c, &s);
        insert_trantbl(r, c, s);
    }

    for(i=1; i<=nostate; i++){
        c = 0;
        for(j=0; j<20; j++){
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
    }

    printf("Equivalent NFA without epsilon states : \n");
    printf("--------------------------------------------\n");

    printf("Start state : ");
    print_e_closure(start);
    printf("Alphabets : ");
    for(i=0; i<noalpha; i++){
        printf("%c, ", alphabet[i]);
    }
    printf("\n");

    printf("States : ");
    for(i=1; i<=nostate; i++){
        print_e_closure(i);
    }
    printf("\n");

    printf("Transitions : \n");
    for(i=1; i<=nostate; i++){
        for(j=0; j<noalpha-1; j++){
            for(m=1; m<=nostate; m++){
                set[m] = 0;
            }
            for(k=0; e_closure[i][k] != 0; k++){
                t = e_closure[i][k];
                temp = transition[t][j];
                while(temp != NULL){
                    unionclosure(temp->st);
                    temp = temp->link;
                }
            }
            printf("\n");
            print_e_closure(i);
            printf("%c\t", alphabet[j]);
            printf("{");
            for(n=1; n<=nostate; n++){
                if(set[n] != 0){
                    printf("q%d, ", n);
                }
            }
            printf("}");
        }
    }
    printf("\nFinal states : ");
    findfinalstate();
}