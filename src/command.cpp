#include <iostream>
#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "command.h"
#include "waittime.h"
#include "countdown.h"

using namespace std;
const int screenWidth = 1200;
const int screenHeight = 800;

vector<string> commands = {"Up", "Down", "Left", "Right"};
vector<string> oppositeCommands = {"Down", "Up", "Right", "Left"};
string currentCommand;
bool gameOver = false;
bool gamestart = false;
bool p1Pressed = false;
bool p2Pressed = false;
bool waitfornextcommand = false;
bool isOppositeCommand = false;
int scorep1 = 0;
int scorep2 = 0;
int stage = 1;
float stagetime = 30.0f;
float txttime = 0.0f;
float waitTime = 0.0f;
Countdown countdown(3.0f);

void positioncenter(string, int, Color);

void generateCommand();

void checkInput();

void playcommand() {
    InitWindow(screenWidth, screenHeight, "Command master");
    SetTargetFPS(60);
    srand(time(NULL));

    while (!WindowShouldClose()) {
        if(!gamestart){
            countdown.update(GetFrameTime());
            if(countdown.isFinished()){
                WaitTimer(1.5f);
                gamestart = true;
                generateCommand();
            }
        }else if (!gameOver) {
            stagetime -= GetFrameTime();
            txttime -= GetFrameTime();

            if(stagetime <= 0){
                stage++;
                if(stage > 3){
                    gameOver = true;
                }else{
                    stagetime = 30.0f;
                    generateCommand();
                }

            }
            if (!waitfornextcommand) {
                checkInput();
                if ((p1Pressed && p2Pressed) || txttime <= 0) {
                    waitfornextcommand = true;
                    waitTime = 3.0f;
                }
            } else {
                waitTime -= GetFrameTime(); // นับเวลาถอยหลังสำหรับรอ 3 วินาที
                if (waitTime <= 0) {
                    generateCommand(); // สุ่มคำสั่งใหม่
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        if(!gamestart){
            string displaytext = countdown.getDisplayText();
            positioncenter(displaytext,100 ,RED);
        }else if (gameOver) {
            if(scorep1 > scorep2){
                positioncenter("Palyer 1 win",100 ,BLACK);
            }else if(scorep2 > scorep1){
                positioncenter("Palyer 2 win",100 ,BLACK);
            }else if(scorep1 == scorep2){
                positioncenter("Draw",100 ,BLACK);
            }    
        } else {
            if (waitfornextcommand) {
                DrawText("Waiting for next command...", 300, 200, 30, BLACK);
            } else {
                if (isOppositeCommand) {
                DrawText(TextFormat("Command: %s", currentCommand.c_str()), 300, 200, 30, RED);
                }else{
                DrawText(TextFormat("Command: %s", currentCommand.c_str()), 300, 200, 30, BLUE); 
                }
            }
            DrawText(TextFormat("Time: %.1f", txttime), 350, 300, 30, BLACK);
            DrawText(TextFormat("Score P1: %d", scorep1), 400, 400, 30, BLUE);
            DrawText(TextFormat("Score P2: %d", scorep2), 200, 400, 30, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
}

void positioncenter(string txt, int fontsize ,Color colortxt){
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth)/2;
    int txtY = (screenHeight - fontsize)/2;
    DrawText(txt.c_str(),txtX,txtY,fontsize,colortxt);
}

void generateCommand() {
    txttime = 5.0f; 
    if(stage == 1){
        isOppositeCommand = false;
        currentCommand = commands[rand() % commands.size()];
    }else if(stage == 2){
        isOppositeCommand = true;
        int index = rand() % commands.size();
        currentCommand = oppositeCommands[index];
    }else{
        isOppositeCommand = (rand()%2 == 0);
        if(isOppositeCommand){
            int index = rand() % commands.size();
            currentCommand = oppositeCommands[index];
        }else{
            currentCommand = commands[rand() % commands.size()];
        }
    }
    p1Pressed = false;
    p2Pressed = false;
    waitfornextcommand = false;
}

void checkInput() {
    if (!p1Pressed) {
        if (isOppositeCommand) {
            if (currentCommand == "Down" && IsKeyPressed(KEY_UP)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Up" && IsKeyPressed(KEY_DOWN)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Right" && IsKeyPressed(KEY_LEFT)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Left" && IsKeyPressed(KEY_RIGHT)) {
                p1Pressed = true;
                scorep1++; 
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                p1Pressed = true; 
            }
        } else {
            
            if (currentCommand == "Up" && IsKeyPressed(KEY_UP)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Down" && IsKeyPressed(KEY_DOWN)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Left" && IsKeyPressed(KEY_LEFT)) {
                p1Pressed = true;
                scorep1++; 
            } else if (currentCommand == "Right" && IsKeyPressed(KEY_RIGHT)) {
                p1Pressed = true;
                scorep1++;
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                p1Pressed = true; 
            }
        }
    }
    if (!p2Pressed) {
        if (isOppositeCommand) {
            if (currentCommand == "Down" && IsKeyPressed(KEY_W)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Up" && IsKeyPressed(KEY_S)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Right" && IsKeyPressed(KEY_A)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Left" && IsKeyPressed(KEY_D)) {
                p2Pressed = true;
                scorep2++; 
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                p2Pressed = true;
            }
        } else {
            
            if (currentCommand == "Up" && IsKeyPressed(KEY_W)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Down" && IsKeyPressed(KEY_S)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Left" && IsKeyPressed(KEY_A)) {
                p2Pressed = true;
                scorep2++; 
            } else if (currentCommand == "Right" && IsKeyPressed(KEY_D)) {
                p2Pressed = true;
                scorep2++; 
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                p2Pressed = true;
            }
        }
    }
}