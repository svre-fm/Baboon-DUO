#pragma once

#include <raylib.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "waittime.h"
#include "countdown.h"


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
    int p1CurrentFrame = 4; 
    int p2CurrentFrame = 4; 
    Countdown countdown = Countdown(3.0f);
    Texture2D bg = LoadTexture("pic/bggame.png");
    
};

inline void drawTextBox(const char* text, int posX, int posY, int fontSize, Color textColor, Color boxColor, Color borderColor, int borderSize) {
    
    int textWidth = MeasureText(text, fontSize);
    int boxX = posX - 10; 
    int boxY = posY - 10; 
    int boxWidth = textWidth + 20; 
    int boxHeight = fontSize + 20; 

    DrawRectangle(boxX - borderSize, boxY - borderSize, boxWidth + 2 * borderSize, boxHeight + 2 * borderSize, borderColor);
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);
    DrawText(text, posX, posY, fontSize, textColor);
}

inline void positioncenter(string txt, int fontsize, Color colortxt) {
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth) / 2;
    int txtY = (screenHeight - fontsize) / 2;
    DrawText(txt.c_str(), txtX, txtY, fontsize, colortxt);
}

inline void center(string txt, int fontsize,int txty , Color colortxt) {
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth) / 2;
    DrawText(txt.c_str(), txtX, txty, fontsize, colortxt);
}

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
}

inline void checkInput(GameState& state) {
    if (!state.p1Pressed) {
        if (state.isOppositeCommand) {
            if (state.currentCommand == "Down" && IsKeyPressed(KEY_UP)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 0;
            } else if (state.currentCommand == "Up" && IsKeyPressed(KEY_DOWN)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 1;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_LEFT)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 2;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                if (IsKeyPressed(KEY_UP)) {
                    state.p1CurrentFrame = 0; // ท่าหันขึ้น
                } else if (IsKeyPressed(KEY_DOWN)) {
                    state.p1CurrentFrame = 1; // ท่าหันลง
                } else if (IsKeyPressed(KEY_LEFT)) {
                    state.p1CurrentFrame = 2; // ท่าหันซ้าย
                } else if (IsKeyPressed(KEY_RIGHT)) {
                    state.p1CurrentFrame = 3; // ท่าหันขว
                }

            }
        } else {
            if (state.currentCommand == "Up" && IsKeyPressed(KEY_UP)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 0;
            } else if (state.currentCommand == "Down" && IsKeyPressed(KEY_DOWN)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 1;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_LEFT)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 2;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                state.scorep1++;
                state.p1CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT)) {
                state.p1Pressed = true;
                if (IsKeyPressed(KEY_UP)) {
                    state.p1CurrentFrame = 0; // ท่าหันขึ้น
                } else if (IsKeyPressed(KEY_DOWN)) {
                    state.p1CurrentFrame = 1; // ท่าหันลง
                } else if (IsKeyPressed(KEY_LEFT)) {
                    state.p1CurrentFrame = 2; // ท่าหันซ้าย
                } else if (IsKeyPressed(KEY_RIGHT)) {
                    state.p1CurrentFrame = 3; // ท่าหันขว
                }

            }
        }
    }

    if (!state.p2Pressed) {
        if (state.isOppositeCommand) {
            if (state.currentCommand == "Down" && IsKeyPressed(KEY_W)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 0;
            } else if (state.currentCommand == "Up" && IsKeyPressed(KEY_S)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 1;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_A)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 2;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                if (IsKeyPressed(KEY_W)) {
                    state.p2CurrentFrame = 0; // ท่าหันขึ้น
                } else if (IsKeyPressed(KEY_S)) {
                    state.p2CurrentFrame = 1; // ท่าหันลง
                } else if (IsKeyPressed(KEY_A)) {
                    state.p2CurrentFrame = 2; // ท่าหันซ้าย
                } else if (IsKeyPressed(KEY_D)) {
                    state.p2CurrentFrame = 3; // ท่าหันขวา
                }
            }
        } else {
            if (state.currentCommand == "Up" && IsKeyPressed(KEY_W)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 0;
            } else if (state.currentCommand == "Down" && IsKeyPressed(KEY_S)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 1;
            } else if (state.currentCommand == "Left" && IsKeyPressed(KEY_A)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 2;
            } else if (state.currentCommand == "Right" && IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                state.scorep2++;
                state.p2CurrentFrame = 3;
            } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_D)) {
                state.p2Pressed = true;
                if (IsKeyPressed(KEY_W)) {
                    state.p2CurrentFrame = 0; // ท่าหันขึ้น
                } else if (IsKeyPressed(KEY_S)) {
                    state.p2CurrentFrame = 1; // ท่าหันลง
                } else if (IsKeyPressed(KEY_A)) {
                    state.p2CurrentFrame = 2; // ท่าหันซ้าย
                } else if (IsKeyPressed(KEY_D)) {
                    state.p2CurrentFrame = 3; // ท่าหันขวา
                }
            }
        }
    }
}

void playcommand();