#include <iostream>
#include <raylib.h>
#include "paint.h"
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

bool gameover = false;
const int screenWidth = 1200;
const int screenHeight = 800;
const int fieldSize = 600; // ขนาดสนามแข่ง
const int gridSize = 20; // ขนาดช่อง
const int cols = fieldSize / gridSize;
const int rows = fieldSize / gridSize;
const int gameTime = 30; // เวลาเล่นเกม
const int moveDelay = 4;
const int captureSize = 2; // ขนาดพื้นที่กินสี
const float endGameDelay = 8.0f;
const float bombDuration = 5.0f;
Texture2D p1, p2, p1s, p2s, bg, score_bg, ground, b1, b2, b3, p1w, p2w, draw;

// ตำแหน่งสนาม
const int fieldX = (screenWidth - fieldSize) / 2;
const int fieldY = (screenHeight - fieldSize) / 2 + 50;

// ผู้เล่น
struct Player {
    int x, y;
    Color color;
    int score;
    int moveCooldown;
    float stunTime;
};

// ระเบิด
struct Bomb {
    int x, y;
};

Bomb bomb; // ตรวจสอบระเบิด
bool bombActive = false;
float bombTimer = 0.0f;
float animationTimer = 0.0f;
bool toggleImage = false;
bool playerHitBomb = false;

void WaitTimer(float seconds) {
    float startTime = GetTime();
    while (GetTime() - startTime < seconds);
}

// ผู้เล่นชนระเบิด
bool p1hitbomb(int px, int py, int bx, int by) {
    return (px >= bx - 1 && px <= bx + 1) && (py >= by - 1 && py <= by + 1);
}
bool p2hitbomb(int px, int py, int bx, int by) {
    return (px >= bx - 1 && px <= bx + 1) && (py >= by - 1 && py <= by + 1);
}

void playpaint() {
    InitWindow(screenWidth, screenHeight, "Paint the Colors");

    p1 = LoadTexture("pic/p1.png");
    p2 = LoadTexture("pic/p2.png");
    p1s = LoadTexture("pic/p1stunned.png");
    p2s = LoadTexture("pic/p2stunned.png");
    bg = LoadTexture("pic/bg.png");
    score_bg = LoadTexture("pic/score5.png");
    ground = LoadTexture("pic/ground.jpg");
    b1 = LoadTexture("pic/banana.png");
    b2 = LoadTexture("pic/banana3.png");
    p1w = LoadTexture("pic/p1win.png");
    p2w = LoadTexture("pic/p2win.png");
    draw = LoadTexture("pic/draw.png");

    SetTargetFPS(60);

    // พื้นที่กินสี
    Player player1 = {0, 0, BLUE, 0, 0};
    Player player2 = {cols - 1, rows - 1, RED, 0, 0};
    
    vector<vector<Color>> grid(rows, vector<Color>(cols, BROWN));
    
    float timer = gameTime;
    bool gameRunning = true;
    
    while (!WindowShouldClose() && gameRunning) {
        if(!gameover){
            float GetTime = GetFrameTime();
            if (timer > 0) timer -= GetTime;
            else {
                gameRunning = false;
                gameover = true;
            }

        // สุ่มเกิดระเบิดถ้าไม่มีระเบิดอยู่
        if (!bombActive) {
            bomb.x = rand() % (cols - 1);
            bomb.y = rand() % (rows - 1);
            bombActive = true;
            bombTimer = 0.0f;
        }
        animationTimer += GetFrameTime();
        if (animationTimer >= 0.5f && bombActive) {
            toggleImage = !toggleImage;
            animationTimer = 0.0f;
        }

        // ตรวจสอบหากไม่มีใครชนภายในระเบิด 5 วินาที จะหายไป
        if (bombActive) {
            bombTimer += GetTime;
            if (bombTimer >= bombDuration) {
                bombActive = false;
            }
        }

        // ตรวจสอบผู้เล่นชนระเบิด
        if (bombActive) {
            if ((p1hitbomb(player1.x, player1.y, bomb.x, bomb.y)) &&
                player1.stunTime <= 0) {
                player1.stunTime = 2.0f;
                bombActive = false;
            }

            if ((p2hitbomb(player2.x, player2.y, bomb.x, bomb.y)) &&
                player2.stunTime <= 0) {
                player2.stunTime = 2.0f;
                bombActive = false;
            }
        }

        // ควบคุมผู้เล่น 1
        if (player1.stunTime > 0)
        player1.stunTime -= GetTime;
        else {
            if (player1.moveCooldown == 0) {
                if (IsKeyDown(KEY_W) && player1.y > 0) player1.y--;
                if (IsKeyDown(KEY_S) && player1.y < rows - 1) player1.y++;
                if (IsKeyDown(KEY_A) && player1.x > 0) player1.x--;
                if (IsKeyDown(KEY_D) && player1.x < cols - 1) player1.x++;
                player1.moveCooldown = moveDelay;
            } else {
                player1.moveCooldown--;
            }
        }

        // ควบคุมผู้เล่น 2
        if (player2.stunTime > 0)
        player2.stunTime -= GetTime;
        else {
            if (player2.moveCooldown == 0) {
                if (IsKeyDown(KEY_UP) && player2.y > 0) player2.y--;
                if (IsKeyDown(KEY_DOWN) && player2.y < rows - 1) player2.y++;
                if (IsKeyDown(KEY_LEFT) && player2.x > 0) player2.x--;
                if (IsKeyDown(KEY_RIGHT) && player2.x < cols - 1) player2.x++;
                player2.moveCooldown = moveDelay;
            } else {
                player2.moveCooldown--;
            }
        }
        
        // เก็บพื้นที่สี
        for (int i = -captureSize / 2 ; i <= captureSize / 2 ; i++) {
            for (int j = -captureSize / 2 ; j <= captureSize / 2 ; j++) {
                int p1_x = player1.x + j, p1_y = player1.y + i;
                int p2_x = player2.x + j, p2_y = player2.y + i;
                if (p1_x >= 0 && p1_x < cols && p1_y >= 0 && p1_y < rows)
                    grid[p1_y][p1_x] = player1.color;
                if (p2_x >= 0 && p2_x < cols && p2_y >= 0 && p2_y < rows)
                    grid[p2_y][p2_x] = player2.color;
            }
        }
        
        // คะแนน
        player1.score = 0;
        player2.score = 0;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c].r == BLUE.r) player1.score++;
                if (grid[r][c].b == RED.b) player2.score++;
            }
        }
    }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        if(!gameover){
        
        DrawTextureEx(bg, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(score_bg, (Vector2){25, 48}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(score_bg, (Vector2){915, 45}, 0.0f, 1.05f, WHITE);

        // ชื่อเกม
        DrawText("Paint the Colors", 388, 30, 50, WHITE);

        // วาดสนามแข่ง
        DrawRectangleLinesEx((Rectangle){fieldX, fieldY, fieldSize, fieldSize}, 2, BLACK);
        // วาดกริดสี
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                DrawRectangle(fieldX + c * gridSize, fieldY + r * gridSize, gridSize, gridSize, grid[r][c]);
            }
        }
                
        // วาดระเบิด
        Texture2D bomb_texture;
        bomb_texture = toggleImage ? b1 : b2;
        DrawTextureEx(bomb_texture, (Vector2){(float)(fieldX + bomb.x * gridSize), (float)(fieldY + bomb.y * gridSize)}, 0.0f, 0.17f, WHITE);
            
        // วาดผู้เล่น
        Texture2D player1_texture = (player1.stunTime > 0) ? p1s : p1;
        Texture2D player2_texture = (player2.stunTime > 0) ? p2s : p2;

        // วาดผู้เล่น
        DrawTextureEx(player1_texture, (Vector2){(float)(fieldX + player1.x * gridSize - 47), (float)(fieldY + player1.y * gridSize - 28)}, 0.0f, 0.4f, WHITE);
        DrawTextureEx(player2_texture, (Vector2){(float)(fieldX + player2.x * gridSize - 55), (float)(fieldY + player2.y * gridSize - 28)}, 0.0f, 0.4f, WHITE);

        // แสดงคะแนนเรียลไทม์
        DrawText(TextFormat("Player 1: %d", player1.score), 60, 90, 30, BLUE);
        DrawText(TextFormat("Player 2: %d", player2.score), 950, 90, 30, RED);
        DrawText(TextFormat("Time: %.1f", timer), 530, 100, 30, WHITE);
        }else{
            UnloadTexture(score_bg);
            UnloadTexture(bg);
            if(player1.score > player2.score){
                DrawText(TextFormat("Player 1 Win!"), 392, 100, 70, BLUE);
                DrawText(TextFormat("Player 1: %d", player1.score), 120, 300, 30, BLUE);
                DrawText(TextFormat("Player 2: %d", player2.score), 850, 300, 30, RED);
            }else if(player2.score > player1.score){
                DrawText(TextFormat("Player 2 Win!"), 392, 100, 70, RED);
                DrawText(TextFormat("Player 1: %d", player1.score), 120, 300, 30, BLUE);
                DrawText(TextFormat("Player 2: %d", player2.score), 850, 300, 30, RED);
            }else if(player1.score == player2.score){
                DrawText(TextFormat("Draw!"), 480, 100, 70, WHITE);
                DrawText(TextFormat("Player 1: %d", player1.score), 120, 300, 30, BLUE);
                DrawText(TextFormat("Player 2: %d", player2.score), 850, 300, 30, RED);
            }  
        }
        
        EndDrawing();
    }
    
    WaitTimer(endGameDelay);

    UnloadTexture(p1);
    UnloadTexture(p1s);
    UnloadTexture(p2);
    UnloadTexture(p2s);
    UnloadTexture(b1);
    UnloadTexture(b2);

    CloseWindow();
}
