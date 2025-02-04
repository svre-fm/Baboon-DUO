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
bool p1Pressed = false; 
bool p2Pressed = false; 
bool p1correct = false; 
bool p2correct = false; 
bool waitfornextcommand = false; 
int p1score = 0;
int p2score = 0;
float gametime = 150.0f;
float txttime = 0.0f;
float waitTime = 0.0f; 

void generateCommand() {
    txttime = 5.0f; 
    currentCommand = commands[rand() % commands.size()];
    p1Pressed = false;
    p2Pressed = false;
    p1correct = false;
    p2correct = false;
    waitfornextcommand = false;
}

void checkInput() {
    if (!p1Pressed) {
        if (currentCommand == "Up" && IsKeyPressed(KEY_UP)) {
            p1correct = true;
            p1Pressed = true;
            p1score++;
        }
        if (currentCommand == "Down" && IsKeyPressed(KEY_DOWN)) {
            p1correct = true;
            p1Pressed = true;
            p1score++;
        }
        if (currentCommand == "Left" && IsKeyPressed(KEY_LEFT)) {
            p1correct = true;
            p1Pressed = true;
            p1score++;
        }
        if (currentCommand == "Right" && IsKeyPressed(KEY_RIGHT)) {
            p1correct = true;
            p1Pressed = true;
            p1score++;
        }
        if ((currentCommand != "Up" && IsKeyPressed(KEY_UP)) ||
            (currentCommand != "Down" && IsKeyPressed(KEY_DOWN)) ||
            (currentCommand != "Left" && IsKeyPressed(KEY_LEFT)) ||
            (currentCommand != "Right" && IsKeyPressed(KEY_RIGHT))) {
            p1Pressed = true; 
        }
    }

    if (!p2Pressed) {
        if (currentCommand == "Up" && IsKeyPressed(KEY_W)) {
            p2correct = true;
            p2Pressed = true;
            p2score++; 
        }
        if (currentCommand == "Down" && IsKeyPressed(KEY_S)) {
            p2correct = true;
            p2Pressed = true;
            p2score++; 
        }
        if (currentCommand == "Left" && IsKeyPressed(KEY_A)) {
            p2correct = true;
            p2Pressed = true;
            p2score++; 
        }
        if (currentCommand == "Right" && IsKeyPressed(KEY_D)) {
            p2correct = true;
            p2Pressed = true;
            p2score++; 
        }

        if ((currentCommand != "Up" && IsKeyPressed(KEY_W)) ||
            (currentCommand != "Down" && IsKeyPressed(KEY_S)) ||
            (currentCommand != "Left" && IsKeyPressed(KEY_A)) ||
            (currentCommand != "Right" && IsKeyPressed(KEY_D))) {
            p2Pressed = true; 
        }
    }
}

void playcommand() {
    InitWindow(screenWidth, screenHeight, "Command master");
    SetTargetFPS(60);
    srand(time(NULL));
    generateCommand();

    while (!WindowShouldClose()) {
        if (!gameOver) {
            gametime -= GetFrameTime(); 
            txttime -= GetFrameTime();  

            if (!waitfornextcommand) {
                checkInput();

                
                if ((p1Pressed && p2Pressed) || txttime <= 0) {
                    waitfornextcommand = true;
                    waitTime = 3.0f; 
                }
            } else {
                waitTime -= GetFrameTime(); 
                if (waitTime <= 0) {
                    generateCommand(); 
                }
            }

            if (gametime <= 0) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameOver) {
            DrawText("Game Over! Press R to Restart", 200, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                p1score = 0;
                p2score = 0;
                gametime = 150.0f; 
                gameOver = false;
                generateCommand();
            }
        } else {
            if (waitfornextcommand) {
                DrawText("Waiting for next command...", 300, 200, 30, BLACK);
            } else {
                DrawText(TextFormat("Command: %s", currentCommand.c_str()), 300, 200, 30, BLACK);
            }
            DrawText(TextFormat("Time: %.1f", txttime), 350, 300, 30, BLACK);
            DrawText(TextFormat("Score P1: %d", p1score), 200, 400, 30, BLUE);
            DrawText(TextFormat("Score P2: %d", p2score), 400, 400, 30, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
}