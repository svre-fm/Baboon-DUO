#include <iostream>
#include <raylib.h>
#include "reflex.h"
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool gameover = false;
const int screenWidth = 1200;
const int screenHeight = 800;
const int fieldSize = 600; // ขนาดสนามแข่ง
const int gridSize = 20;
const int cols = fieldSize / gridSize;
const int rows = fieldSize / gridSize;
const int gameTime = 30;
const int moveDelay = 4;
const int captureSize = 2;
const float endGameDelay = 8.0f;

// ตำแหน่งสนาม
const int fieldX = (screenWidth - fieldSize) / 2;
const int fieldY = (screenHeight - fieldSize) / 2;

struct Player {
    int x, y;
    Color color;
    int score;
    int moveCooldown;
};

void positioncenter(string txt, int fontsize ,Color colortxt){
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth)/2;
    int txtY = (screenHeight - fontsize)/2;
    DrawText(txt.c_str(),txtX,txtY,fontsize,colortxt);
}

void WaitTimer(float seconds) {
    float startTime = GetTime();
    while (GetTime() - startTime < seconds);
}

void playreflex() {
    InitWindow(screenWidth, screenHeight, "Paint the Colors");
    SetTargetFPS(60);

    Player player1 = {0, 0, RED, 0, 0};
    Player player2 = {cols - 1, rows - 1, BLUE, 0, 0};
    
    vector<vector<Color>> grid(rows, vector<Color>(cols, WHITE));
    
    float timer = gameTime;
    bool gameRunning = true;

    while (!WindowShouldClose() && gameRunning) {
        if(!gameover){
            float deltaTime = GetFrameTime();
            if (timer > 0) timer -= deltaTime;
            else {
                gameRunning = false;
                gameover = true;
            }

            // ควบคุมผู้เล่น 1
            if (player1.moveCooldown == 0) {
                if (IsKeyDown(KEY_W) && player1.y > 0) player1.y--;
                if (IsKeyDown(KEY_S) && player1.y < rows - 1) player1.y++;
                if (IsKeyDown(KEY_A) && player1.x > 0) player1.x--;
                if (IsKeyDown(KEY_D) && player1.x < cols - 1) player1.x++;
                player1.moveCooldown = moveDelay;
            } else {
                player1.moveCooldown--;
            }

            // ควบคุมผู้เล่น 2
            if (player2.moveCooldown == 0) {
                if (IsKeyDown(KEY_UP) && player2.y > 0) player2.y--;
                if (IsKeyDown(KEY_DOWN) && player2.y < rows - 1) player2.y++;
                if (IsKeyDown(KEY_LEFT) && player2.x > 0) player2.x--;
                if (IsKeyDown(KEY_RIGHT) && player2.x < cols - 1) player2.x++;
                player2.moveCooldown = moveDelay;
            } else {
                player2.moveCooldown--;
            }

            // เก็บพื้นที่สี
            for (int i = -captureSize / 2; i <= captureSize / 2; i++) {
                for (int j = -captureSize / 2; j <= captureSize / 2; j++) {
                    int p1_x = player1.x + j, p1_y = player1.y + i;
                    int p2_x = player2.x + j, p2_y = player2.y + i;
                    if (p1_x >= 0 && p1_x < cols && p1_y >= 0 && p1_y < rows)
                        grid[p1_y][p1_x] = player1.color;
                    if (p2_x >= 0 && p2_x < cols && p2_y >= 0 && p2_y < rows)
                        grid[p2_y][p2_x] = player2.color;
                }
            }
        
            // คำนวณคะแนน
            player1.score = 0;
            player2.score = 0;
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    if (grid[r][c].r == RED.r) player1.score++;
                    if (grid[r][c].b == BLUE.b) player2.score++;
                }
            }
        }

        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(!gameover){
        // วาดสนามแข่ง
        DrawRectangleLines(fieldX, fieldY, fieldSize, fieldSize, BLACK);
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                DrawRectangle(fieldX + c * gridSize, fieldY + r * gridSize, gridSize, gridSize, grid[r][c]);
            }
        }
        
        // วาดผู้เล่น
        DrawRectangle(fieldX + player1.x * gridSize, fieldY + player1.y * gridSize, gridSize, gridSize, Color{200, 0, 0, 255});
        DrawRectangle(fieldX + player2.x * gridSize, fieldY + player2.y * gridSize, gridSize, gridSize, Color{0, 0, 200, 255});
        
        // แสดงคะแนนเรียลไทม์
        DrawText(TextFormat("Player 1: %d", player1.score), 50, 20, 30, RED);
        DrawText(TextFormat("Player 2: %d", player2.score), screenWidth - 250, 20, 30, BLUE);
        DrawText(TextFormat("Time: %.1f", timer), screenWidth / 2 - 50, 20, 30, BLACK);
        }else{
            if(player1.score > player2.score){
                positioncenter("Player 1 win",100 ,RED);
            }else if(player2.score > player1.score){
                positioncenter("Player 2 win",100 ,BLUE);
            }else if(player1.score == player2.score){
                positioncenter("Draw",100 ,BLACK);
            }  
        }
        
        EndDrawing();
    }
    
    WaitTimer(endGameDelay);
    CloseWindow();
}
