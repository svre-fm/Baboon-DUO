#include "command.h"
#include "object.h"
#include <iostream>

void playcommand() {
    GameState state;
    generateCommand(state);

    P1 P1;
    P2 P2;
    command command;
    Commander commander;
    oppositecommand opposite;

    Vector2 PositionP1 = {745,626};
    Vector2 PositionP2 = {367,626};
    Vector2 PositionC1 = {184,463};
    Vector2 PositionC2 = {856,463};
    Vector2 Positioncommand = {240,202};
    Vector2 Positionopposite = {600,202};


    P1.setscale(4.0f);
    P2.setscale(4.0f);
    command.setscale(4.0f);
    opposite.setscale(4.0f);
    commander.setscale(4.0f);

    
    while (!WindowShouldClose()) {  
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(state.bg,0,0,WHITE);

        if (!state.gamestart) {
            state.countdown.update(GetFrameTime());
            if (state.countdown.isFinished()) {
                WaitTimer(1.5f);
                state.gamestart = true;
                generateCommand(state);
            }
        } else if (!state.gameOver) {
            state.stagetime -= GetFrameTime();
            state.txttime -= GetFrameTime();

            if (state.stagetime <= 0) {
                state.stage++;
                if(state.stage == 3 ){
                    WaitTimer(1.0f);
                    state.stagetime = 25.0f;
                    generateCommand(state);
                }
                if (state.stage > 3) {
                    state.gameOver = true;
                } else {
                    WaitTimer(1.0f);
                    state.stagetime = 15.0f;
                    generateCommand(state);
                }
            }

            if (!state.waitfornextcommand) {
                checkInput(state);
                if ((state.p1Pressed && state.p2Pressed) || state.txttime <= 0) {
                    state.waitfornextcommand = true;
                    state.waitTime = 1.5f;
                }
            } else {
                state.waitTime -= GetFrameTime(); // Countdown for waiting 3 seconds
                if (state.waitTime <= 0) {
                    generateCommand(state); // Generate new command
                }
            }
        }

        if (!state.gamestart) {
            string displaytext = state.countdown.getDisplayText();
            positioncenter(displaytext, 100, RED);
        } else if (state.gameOver) {
            if (state.scorep1 > state.scorep2) {
                positioncenter("Player 1 win", 100, BLUE);
            } else if (state.scorep2 > state.scorep1) {
                positioncenter("Player 2 win", 100, RED);
            } else if (state.scorep1 == state.scorep2) {
                positioncenter("Draw", 100, BLACK);
            }
        } else {

            P1.draw(PositionP1, state.p1CurrentFrame);
            P2.draw(PositionP2, state.p2CurrentFrame);

            if (!state.waitfornextcommand) {
                if (state.isOppositeCommand) {
                    commander.draw(PositionC2, 3);
                    commander.draw(PositionC1, 0);
                    if(state.currentCommand == "Up") opposite.draw(Positionopposite,0);
                    if(state.currentCommand == "Down") opposite.draw(Positionopposite,1);
                    if(state.currentCommand == "Left") opposite.draw(Positionopposite,2);
                    if(state.currentCommand == "Right") opposite.draw(Positionopposite,3);
                } else {
                    commander.draw(PositionC1, 1);
                    commander.draw(PositionC2, 2);
                    if(state.currentCommand == "Up") command.draw(Positioncommand,0);
                    if(state.currentCommand == "Down") command.draw(Positioncommand,1);
                    if(state.currentCommand == "Left") command.draw(Positioncommand,2);
                    if(state.currentCommand == "Right") command.draw(Positioncommand,3);
                }
            }else{
                commander.draw(PositionC1, 0);
                commander.draw(PositionC2, 2);
            }
            const char* scoreTextP2 = TextFormat("Score P2: %d", state.scorep2);
            const char* scoreTextP1 = TextFormat("Score P1: %d", state.scorep1);
            drawTextBox(scoreTextP1, 1000, 22, 30, BLUE, WHITE, BLUE,2);
            drawTextBox(scoreTextP2, 35, 22, 30, RED, WHITE, RED,2);
            DrawText("P1",790,600,30,BLUE);
            DrawText("P2",410,600,30,RED);

        }

        EndDrawing();
        if (WindowShouldClose()) {
            break; 
        }
    }
    state.isGameRunning = false;
}