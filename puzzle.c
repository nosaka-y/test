#include <stdio.h> // printf, scanf
#include <stdlib.h> // system

void numberSet(int, char*);
void printField();

/*
playGame();
typedef struct {
    char* name;
    int score;
} PLAYER;
*/

int main() {
    char* number[9] = {"１","２","３",
                       "４","５","６",
                       "７","８","　"};
    int afterPlayer = 8;
    int beforePlayer = 8;
    int move;
    system("clear");
    printField();
    numberSet(9, "8:↑ 2:↓ 4:← 6:→");
    for (int i = 0; i < 9; i++) {
            numberSet(i, number[i]);
    }
    while (1) {
        numberSet(10, "");
        scanf("%1d", &move);
        switch (move) {
            case 8:
            //afterPlayerが0,1,2のとき一番上の行にいる
                if(afterPlayer > 2) {
                    beforePlayer = afterPlayer;
                    afterPlayer -= 3;
                    number[beforePlayer] = number[afterPlayer];
                    number[afterPlayer] = "　";
                    numberSet(afterPlayer, number[afterPlayer]);
                    numberSet(beforePlayer, number[beforePlayer]);
                }
                break;
            case 2:
            //afterPlayerが6,7,8のとき一番下の行にいる
                if(afterPlayer < 6 ) {
                    beforePlayer = afterPlayer;
                    afterPlayer += 3;
                    number[beforePlayer] = number[afterPlayer];
                    number[afterPlayer] = "　";
                    numberSet(afterPlayer, number[afterPlayer]);
                    numberSet(beforePlayer, number[beforePlayer]);
                }
                break;
            case 4:
            //afterPlayerが0,3,6のとき一番左の列にいる
                if(afterPlayer % 3 != 0) {
                    beforePlayer = afterPlayer;
                    afterPlayer -= 1;
                    number[beforePlayer] = number[afterPlayer];
                    number[afterPlayer] = "　";
                    numberSet(afterPlayer, number[afterPlayer]);
                    numberSet(beforePlayer, number[beforePlayer]);
                }
                break;
            case 6:
            //afterPlayerが2,5,8のとき一番右の列にいる
                if(afterPlayer % 3 != 2) {
                    beforePlayer = afterPlayer;
                    afterPlayer += 1;
                    number[beforePlayer] = number[afterPlayer];
                    number[afterPlayer] = "　";
                    numberSet(afterPlayer, number[afterPlayer]);
                    numberSet(beforePlayer, number[beforePlayer]);
                }
                break;
        }
    }
    return 0;
}

void numberSet(int i, char* number) {
    switch (i) {
        case 0:
            printf("\033[2;3H%s", number);
            break;
        case 1:
            printf("\033[2;7H%s", number);
            break;
        case 2:
            printf("\033[2;11H%s", number);
            break;
        case 3:
            printf("\033[4;3H%s", number);
            break;
        case 4:
            printf("\033[4;7H%s", number);
            break;
        case 5:
            printf("\033[4;11H%s", number);
            break;
        case 6:
            printf("\033[6;3H%s", number);
            break;
        case 7:
            printf("\033[6;7H%s", number);
            break;
        case 8:
            printf("\033[6;11H%s", number);
            break;
        case 9:
            printf("\033[9;0H%s", number);
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
           "＋ー＋ー＋ー＋\n");
}