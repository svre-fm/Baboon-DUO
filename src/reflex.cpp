#include <iostream>
#include <raylib.h>
#include "reflex.h"
#include <vector>
#include <algorithm>

using namespace std;

const int screenWidth = 1200;
const int screenHeight = 800;
const int gridSize = 20;
const int cols = screenWidth / gridSize;
const int rows = screenHeight / gridSize;
const int gameTime = 30;
const int moveDelay = 4; // Delay for movement
const int captureSize = 2; // Size of painted area

struct Player {
    int x, y;
    Color color;
    int score;
    int moveCooldown;
};

void WaitTimer(float seconds) {
    float startTime = GetTime();
    while(GetTime() - startTime < seconds);
}

void playreflex() {
    InitWindow(screenWidth, screenHeight, "Paint the Colors");
    SetTargetFPS(60);

    Player player1 = {0, 0, RED, 0, 0};
    Player player2 = {cols - 1, rows - 1, BLUE, 0, 0};
    
    vector<vector<Color>> grid(rows, vector<Color>(cols, WHITE));
    
    float timer = gameTime;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        timer -= deltaTime;

        // Player 1 movement
        if (player1.moveCooldown == 0) {
            if (IsKeyDown(KEY_W) && player1.y > 0) player1.y--;
            if (IsKeyDown(KEY_S) && player1.y < rows - 1) player1.y++;
            if (IsKeyDown(KEY_A) && player1.x > 0) player1.x--;
            if (IsKeyDown(KEY_D) && player1.x < cols - 1) player1.x++;
            player1.moveCooldown = moveDelay;
        } else {
            player1.moveCooldown--;
        }

        // Player 2 movement
        if (player2.moveCooldown == 0) {
            if (IsKeyDown(KEY_UP) && player2.y > 0) player2.y--;
            if (IsKeyDown(KEY_DOWN) && player2.y < rows - 1) player2.y++;
            if (IsKeyDown(KEY_LEFT) && player2.x > 0) player2.x--;
            if (IsKeyDown(KEY_RIGHT) && player2.x < cols - 1) player2.x++;
            player2.moveCooldown = moveDelay;
        } else {
            player2.moveCooldown--;
        }

        // Color capture area
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
        
        if (timer <= 0) {
            int p1Score = 0, p2Score = 0;
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    if (grid[r][c].r == RED.r) p1Score++;
                    if (grid[r][c].b == BLUE.b) p2Score++;
                }
            }
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(p1Score > p2Score ? "Player 1 Wins!" : (p1Score < p2Score ? "Player 2 Wins!" : "Draw!"), screenWidth / 2 - 175, screenHeight / 2 - 110, 50, BLACK);
            DrawText(TextFormat("Player 1 Score: %d", p1Score), screenWidth / 2 - 200, screenHeight / 2 - 10, 40, RED);
            DrawText(TextFormat("Player 2 Score: %d", p2Score), screenWidth / 2 - 200, screenHeight / 2 + 40, 40, BLUE);
            EndDrawing();
            WaitTimer(5);
            break;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                DrawRectangle(c * gridSize, r * gridSize, gridSize, gridSize, grid[r][c]);
            }
        }
        
        DrawRectangle(player1.x * gridSize, player1.y * gridSize, gridSize, gridSize, Color{200, 0, 0, 255}); // Darker red
        DrawRectangle(player2.x * gridSize, player2.y * gridSize, gridSize, gridSize, Color{0, 0, 200, 255}); // Darker blue
        
        DrawText(TextFormat("Time: %.1f", timer), screenWidth / 2 - 50, 20, 30, BLACK);
        EndDrawing();
    }
    
    CloseWindow();
}
