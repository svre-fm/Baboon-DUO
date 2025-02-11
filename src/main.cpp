#include <iostream>
#include <raylib.h>
#include "command.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Baboon DUO");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("select game", 150, 50, 30, BLACK);
            DrawText("1. Command Master", 150, 150, 25, DARKGRAY);

             if (IsKeyPressed(KEY_ONE)) {
                playcommand();
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}


