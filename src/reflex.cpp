#include <iostream>
#include <raylib.h>
#include "reflex.h"
#include <ctime>

using namespace std;

const int screenWidth = 1200;
const int screenHeight = 800;

// กำหนดค่าตัวแปร
int player1Score = 0;
int player2Score = 0;
bool isGreen = false;
float timeToChangeColor;
float timer = 0.0f;

void WaitTimer(float seconds){
    float startTime = GetTime();
    while(GetTime() - startTime < seconds);
}

void playreflex() {
    InitWindow(screenWidth, screenHeight, "Reflex Rush Duel");
    SetTargetFPS(60);

    srand(time(0));

    while (!WindowShouldClose()) {
        // รีเซ็ตค่าสำหรับรอบใหม่
        isGreen = false;
        timer = 0.0f;
        timeToChangeColor = GetRandomValue(2, 5) + GetRandomValue(0, 100) / 100.0f; // สุ่ม 2-5 วินาทีแบบไม่แน่นอน

        // รอจนกว่าจะถึงเวลาที่เปลี่ยนเป็นไฟเขียว
        while (timer < timeToChangeColor && !WindowShouldClose()) {
            timer += GetFrameTime();

            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // ชื่อเกมอยู่ตรงกลางด้านบน
            DrawText("Reflex Rush Duel", screenWidth / 2 - MeasureText("Reflex Rush Duel", 40) / 2, 20, 40, DARKGRAY);
            
            DrawText(TextFormat("Player 1 Score: %d", player1Score), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("Player 2 Score: %d", player2Score), 10, 70, 20, DARKGRAY);

            // ข้อความไฟแดงอยู่ตรงกลางจอและใหญ่ขึ้น
            DrawText("Red light!", screenWidth / 2 - MeasureText("Red light!", 50) / 2, screenHeight / 2 - 25, 50, RED);
            
            EndDrawing();
        }

        // เปลี่ยนเป็นไฟเขียว
        isGreen = true;
        timer = 0.0f;  // รีเซ็ตเวลา

        // รอให้ผู้เล่นกดปุ่ม
        bool scored = false;
        while (!scored && !WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawText("Reflex Rush Duel", screenWidth / 2 - MeasureText("Reflex Rush Duel", 40) / 2, 20, 40, DARKGRAY);
            DrawText(TextFormat("Player 1 Score: %d", player1Score), 10, 40, 20, DARKGRAY);
            DrawText(TextFormat("Player 2 Score: %d", player2Score), 10, 70, 20, DARKGRAY);

            // ข้อความไฟเขียวอยู่ตรงกลางจอและใหญ่ขึ้น
            DrawText("Green light!", screenWidth / 2 - MeasureText("Green light!", 50) / 2, screenHeight / 2 - 25, 50, GREEN);
            
            EndDrawing();

            if (IsKeyPressed(KEY_W)) {
                player1Score++;
                scored = true;
            }
            if (IsKeyPressed(KEY_UP)) {
                player2Score++;
                scored = true;
            }
        }

        // ตรวจสอบผู้ชนะ
        if (player1Score == 2 || player2Score == 2) {
            break;
        }
    }

    // แสดงผู้ชนะ
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Reflex Rush Duel", screenWidth / 2 - MeasureText("Reflex Rush Duel", 40) / 2, 20, 40, DARKGRAY);
    if (player1Score == 2) {
        DrawText("Player 1 Wins!", screenWidth / 2 - MeasureText("Player 1 Wins!", 50) / 2, screenHeight / 2 - 25, 50, GREEN);
    } else {
        DrawText("Player 2 Wins!", screenWidth / 2 - MeasureText("Player 2 Wins!", 50) / 2, screenHeight / 2 - 25, 50, GREEN);
    }
    EndDrawing();

    WaitTimer(3);
    CloseWindow();
}
