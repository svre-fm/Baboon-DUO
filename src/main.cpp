#include <iostream>
#include <raylib.h>
#include "command.h"
#include "Memory.h"
#include "paint.h"
#include "pingpong.h"
#include "ObstacleRush.h"
#include "tutorial.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Baboon DUO");
    SetTargetFPS(60);
    GameState state;
    Memory play;
    while (!WindowShouldClose()) {  
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!state.isGameRunning) {
            DrawText("Select Game", 150, 50, 30, BLACK);
            DrawText("1. Command Master", 150, 150, 25, DARKGRAY);
            DrawText("2. PingPong", 150, 200, 25, DARKGRAY);
            DrawText("3. Paint", 150, 250, 25, DARKGRAY);
            DrawText("4. Obstacle-Rush", 150, 300, 25, DARKGRAY);
            DrawText("5. Memorygame", 150, 350, 25, DARKGRAY);

            if (IsKeyPressed(KEY_ONE)) {
                bool Ready = false;
                showtutorial_CM(Ready);
                if(Ready){
                    playcommand();
                }
            }
            if (IsKeyPressed(KEY_TWO)) {
                bool Ready = false;
                showtutorial_PP(Ready);
                if(Ready){
                    playpingpong();
                }
            }
            if (IsKeyPressed(KEY_THREE)) {
                bool Ready = false;
                showtutorial_PC(Ready);
                if(Ready){
                    playpaint();
                }
            }
            if (IsKeyPressed(KEY_FOUR)) {
                bool Ready = false;
                showtutorial_OB(Ready);
                if(Ready){
                    playObstacleRush();
                }
            }
            if (IsKeyPressed(KEY_FIVE)) {
                bool Ready = false;
                showtutorial_MM(Ready);
                if(Ready){
                    play.Run();
                }
            }

        }

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}