#include <stdio.h> // printf, scanf
#include <stdlib.h> // system, srand, rand
#include <string.h> // strcmp;
#include <time.h> // time

typedef struct {
    char number[9];
    int afterPlayer,
        beforePlayer,
        move,
        count;
} FOR_GAME;
/*
typedef struct {
    char* name;
    int score;
} PLAYER;
*/
void randNumSet(FOR_GAME*);
void playGame (FOR_GAME*);
void swapNum (FOR_GAME*);
int clearCheck(char*);
void numberSet(int, char);
void printField();

int main() {
    FOR_GAME g = {"12345678 ", 8, 8, 0, 0};
    
    system("clear");
    printField();
    randNumSet(&g);

    for (int i = 0; i < 9; i++) {
            numberSet(i, g.number[i]);
    }

    while (clearCheck(g.number)) {
        numberSet(-1, ' ');
        scanf("%1d", &g.move);
        playGame(&g);
    }

    numberSet(-1, ' ');

    return 0;
}

void randNumSet(FOR_GAME* g) {
    srand(time(NULL));
    for (int i = 0; i<1000; i++) {
        // 2,4,6,8
        g->move = 2 * ((rand() % 4) + 1);
        playGame(g);
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
            }
            break;
        case 2:
        //g->afterPlayerが6,7,8のとき一番下の行にいる                
            if(g->afterPlayer < 6 ) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer += 3;
                swapNum(g);
            }
            break;
        case 4:
        //g->afterPlayerが0,3,6のとき一番左の列にいる                
            if(g->afterPlayer % 3 != 0) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer -= 1;
                swapNum(g);
            }
            break;
        case 6:
        //g->afterPlayerが2,5,8のとき一番右の列にいる
            if(g->afterPlayer % 3 != 2) {
                g->beforePlayer = g->afterPlayer;
                g->afterPlayer += 1;
                swapNum(g);
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