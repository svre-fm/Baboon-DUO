#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "waittime.h"
#include "countdown.h"
#include "object.h"
#include "style.h"

using namespace std;

const int screenWidth = 1200;
const int screenHeight = 800;

struct GameState {
    vector<string> commands = {"Up", "Down", "Left", "Right"};
    string currentCommand;
    bool gameOver = false;
    bool gamestart = false;
    bool p1Pressed = false;
    bool p2Pressed = false;
    bool waitfornextcommand = false;
    bool isOppositeCommand = false;
    bool isGameRunning = false;
    int scorep1 = 0;
    int scorep2 = 0;
    int stage = 1;
    float stagetime = 15.0f;
    float txttime = 0.0f;
    float waitTime = 0.0f;
    float wait = 0.0f;
    int p1CurrentFrame = 4; 
    int p2CurrentFrame = 4; 
    int p1correct = 3;
    int p2correct = 3;
    Countdown countdown = Countdown(3.0f);
    
};

struct Position {
    Vector2 P1 = {645,585};
    Vector2 P2 = {375,590};
    Vector2 checkP1 = {590,545};
    Vector2 checkP2 = {315,550};
    Vector2 C1 = {112,444};
    Vector2 C2 = {910,444};
    Vector2 command = {228,163};
    Vector2 opposite = {580,163};
};

struct texture {
    Texture2D bg = LoadTexture("pic/bggame.png");
    Texture2D Incorrect = LoadTexture("pic/Incorrect.png");
    Texture2D correct = LoadTexture("pic/correct.png");
    Texture2D P1 = LoadTexture("pic/markP1.png");
    Texture2D P2 = LoadTexture("pic/markP2.png");
    Texture2D borad = LoadTexture("pic/borad.png");
};

inline void generateCommand(GameState& state) {
    state.txttime = 3.0f;
    if (state.stage == 1) {
        state.isOppositeCommand = false;
        state.currentCommand = state.commands[rand() % state.commands.size()];
    } else if (state.stage == 2) {
        state.isOppositeCommand = true;
        state.currentCommand = state.commands[rand() % state.commands.size()];
    } else {
        state.isOppositeCommand = (rand() % 2 == 0);
        if (state.isOppositeCommand) {
            state.currentCommand = state.commands[rand() % state.commands.size()];
        } else {
            state.currentCommand = state.commands[rand() % state.commands.size()];
        }
    }
    state.p1Pressed = false;
    state.p2Pressed = false;
    state.waitfornextcommand = false;
    state.p1CurrentFrame = 4;
    state.p2CurrentFrame = 4;
    state.p1correct = 3;
    state.p2correct = 3;
}

inline void checkInput(GameState& state) {
    if (!state.p1Pressed) {
        if (state.isOppositeCommand) {
            if (state.currentCommand == "Down" && IsKeyPressed(KEY_UP)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 0;
            } else if (state.currentCommand == "Up" && IsKeyPressed(KEY_DOWN)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 1;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_LEFT)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 2;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.p1correct = 1;
                if (IsKeyPressed(KEY_UP)) {
                    state.p1CurrentFrame = 0; 
                } else if (IsKeyPressed(KEY_DOWN)) {
                    state.p1CurrentFrame = 1; 
                } else if (IsKeyPressed(KEY_LEFT)) {
                    state.p1CurrentFrame = 2; 
                } else if (IsKeyPressed(KEY_RIGHT)) {
                    state.p1CurrentFrame = 3; 
                }

            }
        } else {
            if (state.currentCommand == "Up" && IsKeyPressed(KEY_UP)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 0;
            } else if (state.currentCommand == "Down" && IsKeyPressed(KEY_DOWN)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 1;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_LEFT)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 2;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.p1correct = 0;
                state.scorep1++;
                state.p1CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.p1correct = 1;
                if (IsKeyPressed(KEY_UP)) {
                    state.p1CurrentFrame = 0;
                } else if (IsKeyPressed(KEY_DOWN)) {
                    state.p1CurrentFrame = 1; 
                } else if (IsKeyPressed(KEY_LEFT)) {
                    state.p1CurrentFrame = 2; 
                } else if (IsKeyPressed(KEY_RIGHT)) {
                    state.p1CurrentFrame = 3; 
                }

            }
        }
    }

    if (!state.p2Pressed) {
        if (state.isOppositeCommand) {
            if (state.currentCommand == "Down" && IsKeyPressed(KEY_W)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 0;
            } else if (state.currentCommand == "Up" && IsKeyPressed(KEY_S)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 1;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_A)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 2;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.p2correct = 1;
                if (IsKeyPressed(KEY_W)) {
                    state.p2CurrentFrame = 0;
                } else if (IsKeyPressed(KEY_S)) {
                    state.p2CurrentFrame = 1;
                } else if (IsKeyPressed(KEY_A)) {
                    state.p2CurrentFrame = 2;
                } else if (IsKeyPressed(KEY_D)) {
                    state.p2CurrentFrame = 3;
                }
            }
        } else {
            if (state.currentCommand == "Up" && IsKeyPressed(KEY_W)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 0;
            } else if (state.currentCommand == "Down" && IsKeyPressed(KEY_S)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 1;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_A)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 2;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.p2correct = 0;
                state.scorep2++;
                state.p2CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.p2correct = 1;
                if (IsKeyPressed(KEY_W)) {
                    state.p2CurrentFrame = 0;
                } else if (IsKeyPressed(KEY_S)) {
                    state.p2CurrentFrame = 1;
                } else if (IsKeyPressed(KEY_A)) {
                    state.p2CurrentFrame = 2;
                } else if (IsKeyPressed(KEY_D)) {
                    state.p2CurrentFrame = 3;
                }
            }
        }
    }
}

void playcommand();