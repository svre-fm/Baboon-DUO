#include <iostream>
#include <raylib.h>
#include "command.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Baboon DUO");
    SetTargetFPS(60);
    GameState state;

    while (!WindowShouldClose()) {  // ตรวจสอบว่าผู้ใช้ปิดหน้าต่างหรือไม่
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!state.isGameRunning) {
            DrawText("Select Game", 150, 50, 30, BLACK);
            DrawText("1. Command Master", 150, 150, 25, DARKGRAY);

            if (IsKeyPressed(KEY_ONE)) {
                state.isGameRunning = true;
                playcommand(); // เรียก playcommand() โดยตรง
            }
        }

        EndDrawing();
    }

    CloseWindow();  // ปิดหน้าต่างและจบการทำงานของเกม
    return 0;
}