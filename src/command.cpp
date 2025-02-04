#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "command.h"
#include "waittime.h"

using namespace std;
const int screenWidth = 1200;
const int screenHeight = 800;

vector<string> commands = {"Up", "Down", "Left", "Right"};
string currentCommand;
bool gameOver = false;
bool correct = false;
int score = 0;
float timer = 3.0f;

void WaitTime(float seconds) {
    float startTime = GetTime(); // raylib: GetTime() คืนค่าเวลาปัจจุบัน
    while (GetTime() - startTime < seconds); // รอจนกว่าจะถึงเวลาที่กำหนด
}

void generateCommand() {
    currentCommand = commands[rand() % commands.size()];
    correct = false;
    timer = 3.0f;
}

void checkInput() {
    if (currentCommand == "Up" && IsKeyPressed(KEY_UP)) correct = true;
    if (currentCommand == "Down" && IsKeyPressed(KEY_DOWN)) correct = true;
    if (currentCommand == "Left" && IsKeyPressed(KEY_LEFT)) correct = true;
    if (currentCommand == "Right" && IsKeyPressed(KEY_RIGHT)) correct = true;
}

void playcommand(){
    InitWindow(screenWidth, screenHeight, "Command master");
    SetTargetFPS(60);
    srand(time(NULL));
    generateCommand();

    while (!WindowShouldClose()) {
        if (!gameOver) {
            timer -= GetFrameTime();
            checkInput();
            
            if (correct) {
                score++;
                generateCommand();
            } else if (timer <= 0) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameOver) {
            DrawText("Game Over! Press R to Restart", 200, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                score = 0;
                gameOver = false;
                generateCommand();
            }
        } else {
            DrawText(TextFormat("Command: %s", currentCommand.c_str()), 300, 200, 30, BLACK);
            DrawText(TextFormat("Time: %.1f", timer), 350, 300, 30, DARKGRAY);
            DrawText(TextFormat("Score: %d", score), 350, 400, 30, BLUE);
        }
        
        EndDrawing();
    }

    CloseWindow();
}
