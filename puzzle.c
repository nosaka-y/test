#include <stdio.h> // printf, scanf
#include <stdlib.h> // system, srand, rand
#include <string.h> // strcmp;
#include <time.h> // time
#define BOARD 9
#define SIZE 256

typedef struct {
    char number[BOARD];
    int afterPlayer,
        beforePlayer,
        move,
        count;
} FOR_GAME;

typedef struct {
    char* name;
    int score;
} PLAYER;

void randNumSet(FOR_GAME*);
void inputMove(int*);
void playGame(FOR_GAME*);
void swapNum(FOR_GAME*);
int clearCheck(char*);
void useFile(int*);
void numberSet(int, char);
void printField();

int main() {
    FOR_GAME g = {"12345678 ", 8, 8, 0, 0};
    
    system("clear");
    printField();
    randNumSet(&g);
  
    while (clearCheck(g.number)) {
        printf("\033[8;0Hcount:%d", g.count);
        numberSet(-1, ' ');
        inputMove(&g.move);
        playGame(&g);
    }

    numberSet(-1, ' ');
    useFile(&g.count);
    return 0;
}

void randNumSet(FOR_GAME* g) {
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        // 2,4,6,8
        g->move = 2 * ((rand() % 4) + 1);
        playGame(g);
    }
    for (int i = 0; i < BOARD; i++) {
        numberSet(i, g->number[i]);
    }
    g->count = 0;
    return;
}

void inputMove(int *move) { 
    while (scanf("%1d", move) == 0) {
        getchar();
    }
    return;
}

void playGame(FOR_GAME* g) {
    switch (g->move) {
        case 8:
        //g->afterPlayerが0,1,2のとき一番上の行にいる                
            if(g->afterPlayer > 2) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer -= 3;
                swapNum(g);
                g->count++;
            }
            break;
        case 2:
        //g->afterPlayerが6,7,8のとき一番下の行にいる                
            if(g->afterPlayer < 6 ) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer += 3;
                swapNum(g);
                g->count++;
            }
            break;
        case 4:
        //g->afterPlayerが0,3,6のとき一番左の列にいる                
            if(g->afterPlayer % 3 != 0) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer -= 1;
                swapNum(g);
                g->count++;
            }
            break;
        case 6:
        //g->afterPlayerが2,5,8のとき一番右の列にいる
            if(g->afterPlayer % 3 != 2) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer += 1;
                swapNum(g);
                g->count++;
            }
            break;
    }
}

void swapNum(FOR_GAME* g) {
    g->number[g->beforePlayer] = g->number[g->afterPlayer];
    g->number[g->afterPlayer] = ' ';
    numberSet(g->afterPlayer, g->number[g->afterPlayer]);
    numberSet(g->beforePlayer, g->number[g->beforePlayer]);
    return;
}

int clearCheck(char* number) {
    return strcmp(number, "12345678 ");
}

void useFile(int* count) {
    PLAYER p[5] = {};
    char str[SIZE];
    FILE *fp;

    system("clear");
    system("clear");
    printf("your score:%d\n", *count);
    printf("your name:");

    fp = fopen("database.csv", "r");
    if(fp != NULL) {
        for (int i= 0; i < 3; i++) {
            fscanf(fp, "%s %d", str, &p[i].score);
            p[i].name = (char*)malloc(sizeof(char) * (strlen(str) + 1));
            if(p[i].name == NULL) exit(1);
            strcpy(p[i].name, str);
        }
        fclose(fp);
    }

    scanf("%s", str);
    p[3].name = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    if(p[3].name == NULL) exit(1);
    strcpy(p[3].name, str);
    p[3].score = *count;

    for (int i = 3; i > 0; i--) {
        if (p[i].score <= p[i - 1].score) {
            p[4] = p[i];
            p[i] = p[i - 1];
            p[i - 1] = p[4];
        }
    }

    fp = fopen("database.csv", "w");
    if(fp != NULL) {
        for (int i= 0; i < 3; i++) {
            fprintf(fp, "%s %d\n", p[i].name, p[i].score);
        }
        fclose(fp);
    }
}

void numberSet(int i, char number) {
    switch (i) {
        case 0:
            printf("\033[2;3H%c", number);
            break;
        case 1:
            printf("\033[2;7H%c", number);
            break;
        case 2:
            printf("\033[2;11H%c", number);
            break;
        case 3:
            printf("\033[4;3H%c", number);
            break;
        case 4:
            printf("\033[4;7H%c", number);
            break;
        case 5:
            printf("\033[4;11H%c", number);
            break;
        case 6:
            printf("\033[6;3H%c", number);
            break;
        case 7:
            printf("\033[6;7H%c", number);
            break;
        case 8:
            printf("\033[6;11H%c", number);
            break;
        default:
            printf("\033[10;0H");
    }
}

void printField() {
    printf("＋ー＋ー＋ー＋\n"
           "｜  ｜  ｜  ｜\n"
           "＋ー＋ー＋ー＋\n"
           "｜  ｜  ｜  ｜\n"
           "＋ー＋ー＋ー＋\n"
           "｜  ｜  ｜  ｜\n"
           "＋ー＋ー＋ー＋\n"
           "\n8:↑　2:↓　4:←　6:→");
}