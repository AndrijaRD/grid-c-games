#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
#define cross "+"
#define hLine "-"
#define vLine "|"
#define left "←"
#define right "→"
#define up "↑"
#define down "↓"
#define enemyChar "x"
#define done "✔"
#define WIDTH 10
#define HEIGHT 10
#define white "\x1B[0m"
#define blue "\x1B[34m"
#define red "\x1B[31m"
#define green "\x1B[32m"
#define yellow "\x1B[33m"

struct object {
    int x;
    int y;
    int r;
};
struct object player = {0, 0, 0};
struct object enemy = {4, 4, 0};

void solve();
void rotateTo(int);
void move(int);
void display();

int main() {
    display();
    solve();
    return 0;
}

void solve() {
    if(player.x!=enemy.x) rotateTo(3);
    move(player.x-enemy.x);
    if(player.y!=enemy.y) rotateTo(2);
    move(player.y-enemy.y);
    rotateTo(enemy.r);
}

void rotateTo(int d) { player.r = d; display(); }

void move(int action) {
    if(action==0) return;
    if(action==1||action==-1){
        switch(player.r){
            case 0: player.y+=action; break;
            case 1: player.x+=action; break;
            case 2: player.y-=action; break;
            case 3: player.x-=action; break;
        }
        display();
        return;
    }
    for(int i=0; i<abs(action); i++) move(action/abs(action));
}

const int maxRows = HEIGHT*2+2;
void display(){
    system(CLEAR);
    for(int row=0;row<maxRows; row++){
        printf(" row%-3d | ", row);
        for(int column=0;column<WIDTH; column++){
            char midChar[4] = " ";
            char color[8] = white;
            if(player.x == column && player.y == (maxRows-row-2)/2){
                if(enemy.x==column && enemy.y == (maxRows-row-2)/2) {
                    strcpy(midChar, done);
                    strcpy(color, green);
                } else{
                    switch(player.r){
                        case 0: strcpy(midChar, up); break;
                        case 1: strcpy(midChar, right); break;
                        case 2: strcpy(midChar, down); break;
                        case 3: strcpy(midChar, left); break;
                    }
                    strcpy(color, blue);
                }
            } else if(enemy.x==column && enemy.y == (maxRows-row-2)/2){
                strcpy(midChar, enemyChar);
                strcpy(color, red);
            }
            if(row+1==maxRows){
                if(column==0){
                    printf("    %d ", column);
                    continue;
                }
                printf("  %d ", column);
                continue;
            }
            if((row%2)){
                if(column==0){
                    printf("%2d| " "%s" "%s" white " |", HEIGHT-(row/2+1), color, midChar);
                    continue;
                }
                printf(" %s" "%s" white " |", color, midChar);
            } else{
                if(column==0){
                    printf("  +---+");
                    continue;
                }
                printf("---+");
            }
        }
        printf("\n");
    }
    sleep(1);
}
