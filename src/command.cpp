#include <bits/stdc++.h>
#include "global.h"
#include "command.h"

void playcommand() {
    // ตัวแปรเกมต่าง ๆ
    GameState state;
    texture texture;
    Position Position;
    P1 P1;
    P2 P2;
    command command;
    Commander commander;
    oppositecommand opposite;
    check check;
    result result;
    style style;

    generateCommand(state);
    P1.setscale(0.45f);
    P2.setscale(0.45f);
    command.setscale(1.0f);
    opposite.setscale(1.0f);
    commander.setscale(0.25f);
    check.setscale(0.8f);

    float wait = 1.5f;

    while (!WindowShouldClose()) {  

        BeginDrawing();
        ClearBackground(RAYWHITE);

        texture.drawbg(0,0);

        // ถ้าเกมยังไม่เริ่ม
        if (!state.gamestart) {
            state.countdown.update(GetFrameTime());
            if (state.countdown.isFinished()) {
                wait -= GetFrameTime();
                if(wait <= 0){
                    state.gamestart = true;
                    generateCommand(state);
                }
            }
        } else if (!state.gameOver) {
            state.stagetime -= GetFrameTime();
            state.txttime -= GetFrameTime();

            // เงื่อนไขในแต่ละช่วงเวลา
            if (state.stagetime <= 0) {
                state.stage++;
                if (state.stage == 2) {
                    state.stagetime = 10.0f;
                    generateCommand(state);
                }
                if (state.stage == 3) {
                    state.stagetime = 30.0f;
                    generateCommand(state);
                }
                if (state.stage > 3) {
                    state.gameOver = true;
                }
            }

            // การตรวจสอบการคลิกและรอคำสั่ง
            if (!state.waitfornextcommand) {
                checkInput(state);
                if ((state.p1Pressed && state.p2Pressed) || state.txttime <= 0) {
                    state.waitfornextcommand = true;
                    state.waitTime = 1.5f;
                }
            } else {
                state.waitTime -= GetFrameTime();
                if (state.waitTime <= 0) {
                    generateCommand(state);
                }
            }
        }

        // แสดงข้อความเมื่อเกมเริ่ม
        if (!state.gamestart) {
            string displaytext = state.countdown.getDisplayText();
            style.centerXY(displaytext, 100, WHITE);
        } else if (state.gameOver) {
            const char* scoreP2 = TextFormat("%d", state.scorep2);
            const char* scoreP1 = TextFormat("%d", state.scorep1);
            if (state.scorep1 > state.scorep2) {
                result.draw(0);
                style.centerX("Player 1 win", 100, 110, DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(1,1);
                    winsPlayer1[Round - 1] = 1;
                    EndDrawing();
                    break;}
            } else if (state.scorep2 > state.scorep1) {
                result.draw(1);
                style.centerX("Player 2 win", 100, 110, DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(2,1);
                    winsPlayer2[Round - 1] = 1;
                    EndDrawing();
                    break;}
            } else {
                result.draw(2);
                style.centerX("Draw", 150, 110, DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(0,0);
                    winsPlayer1[Round - 1] = 2;
                    EndDrawing();
                    break;}
            }
        } else {
            // การวาดตัวละครและคำสั่ง
            P1.draw(Position.P1, state.p1CurrentFrame);
            P2.draw(Position.P2, state.p2CurrentFrame);
            check.draw(Position.checkP1, state.p1correct);
            check.draw(Position.checkP2, state.p2correct);
            
            // การแสดงผลคำสั่ง
            if (!state.waitfornextcommand) {
                if (state.isOppositeCommand) {
                    commander.draw(Position.C2, 3);
                    commander.draw(Position.C1, 0);
                    if(state.currentCommand == "Up") opposite.draw(Position.opposite,0);
                    if(state.currentCommand == "Down") opposite.draw(Position.opposite,1);
                    if(state.currentCommand == "Left") opposite.draw(Position.opposite,2);
                    if(state.currentCommand == "Right") opposite.draw(Position.opposite,3);
                } else {
                    commander.draw(Position.C1, 1);
                    commander.draw(Position.C2, 2);
                    if(state.currentCommand == "Up") command.draw(Position.command,0);
                    if(state.currentCommand == "Down") command.draw(Position.command,1);
                    if(state.currentCommand == "Left") command.draw(Position.command,2);
                    if(state.currentCommand == "Right") command.draw(Position.command,3);
                }
            }else{
                commander.draw(Position.C1, 0);
                commander.draw(Position.C2, 2);
            }

            const char* scoreTextP2 = TextFormat("Score P2: %d", state.scorep2);
            const char* scoreTextP1 = TextFormat("Score P1: %d", state.scorep1);
            style.drawTextBox(scoreTextP1, 1000, 22, 30, BLUE, WHITE, BLUE,2);
            style.drawTextBox(scoreTextP2, 35, 22, 30, RED, WHITE, RED,2);
            texture.drawP1(0,-5);
            texture.drawP2(0,-5);
        }

        EndDrawing();
        if (WindowShouldClose()) {
            break; 
        }
    }
    
    // ปิดการใช้งานเสียงและทรัพยากร
}