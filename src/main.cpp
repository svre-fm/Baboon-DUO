#include <iostream>
#include <raylib.h>
#include "ObstacleRush.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Baboon DUO");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("select game", 150, 50, 30, BLACK);
            DrawText("1. ObstacleRush", 150, 150, 25, DARKGRAY);

             if (IsKeyPressed(KEY_ONE)) {
                playObstacleRush();
            }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}