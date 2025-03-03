#include "global.h"

bool GAME_OVER = false;
int PLAY1_SCORE = 0;
int PLAY2_SCORE = 0;
int winsPlayer1[5] = {0, 0, 0, 0, 0};
int winsPlayer2[5] = {0, 0, 0, 0, 0}; 
int gameCount = 0;
int Round = 1;
int p1wi = 0;
int p2wi = 0;
void addscore(int player ,int points){
    if(player == 0){
        return;
    }
    if(player == 1){
        PLAY1_SCORE += points;
 }else if(player == 2){
    PLAY2_SCORE += points;
 }
}