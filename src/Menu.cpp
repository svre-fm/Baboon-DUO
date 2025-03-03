#include <iostream>
#include <raylib.h>
#include "Menu.h"
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

#include <iostream>
#include <raylib.h>
#include "Menu.h"
using namespace std;

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

void showMenu()
{
    Texture2D startButtonTexture = LoadTexture("pic/menu/button.png");
    Texture2D backgroundTexture = LoadTexture("pic/menu/Background.PNG");
    Texture2D soundButtonTexture = LoadTexture("pic/menu/soundButton.png");  // ปุ่มเสียงเปิด
    Texture2D muteButtonTexture = LoadTexture("pic/menu/muteButton.png");    // ปุ่มเสียงปิด

    // กำหนดขนาดเริ่มต้นของปุ่ม
    float baseWidth = startButtonTexture.width;
    float baseHeight = startButtonTexture.height;
    float scale = 1.0f;
    float rotation = 0;
    bool increasing = true; 
    bool gamestart = false;
    bool soundOn = true;  // สถานะเสียง
    float soundButtonScale = 0.5f; // สเกลของปุ่มเสียง

    while (!WindowShouldClose()) {  
        Vector2 mousePoint = GetMousePosition();

        // ตำแหน่งปุ่มเริ่มเกม
        Rectangle buttonRec = { SCREEN_WIDTH / 2 - (baseWidth * scale) / 2, 
                                SCREEN_HEIGHT / 2 - (baseHeight * scale) / 2 + 100, 
                                baseWidth * scale, 
                                baseHeight * scale };

        // ตำแหน่งปุ่มเปิด-ปิดเสียง
        Rectangle soundButtonRec = { SCREEN_WIDTH - 100, 20, 
                                     soundButtonTexture.width * soundButtonScale, 
                                     soundButtonTexture.height * soundButtonScale };

        ClearBackground(RAYWHITE);
        BeginDrawing();
        DrawTexture(backgroundTexture, 0, 0, WHITE);

        bool isHover = CheckCollisionPointRec(mousePoint, buttonRec);
        bool isSoundHover = CheckCollisionPointRec(mousePoint, soundButtonRec);

        if (isHover) {
            scale = 1.2f;
            if (increasing) {
                rotation += 0.8f;
                if (rotation >= 10) increasing = false;
            } else {
                rotation -= 0.8f;
                if (rotation <= -10) increasing = true;
            }
        } else {
            if (scale > 1.0f) scale -= 0.01f;
            else scale = 1.0f;
            rotation = 0;
        }

        if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            gamestart = true;
        }

        // กดปุ่มเปิด-ปิดเสียง
        if (isSoundHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            soundOn = !soundOn;  // สลับสถานะเสียง
        }

        // แสดงรูปปุ่มเปิด-ปิดเสียงตามสถานะพร้อมสเกล
        if (soundOn) {
            DrawTextureEx(soundButtonTexture, { soundButtonRec.x, soundButtonRec.y }, 0.0f, soundButtonScale, WHITE);
        } else {
            DrawTextureEx(muteButtonTexture, { soundButtonRec.x, soundButtonRec.y }, 0.0f, soundButtonScale, WHITE);
        }

        Rectangle sourceRec = { 0, 0, (float)startButtonTexture.width, (float)startButtonTexture.height };
        Rectangle destRec = { buttonRec.x + buttonRec.width / 2, buttonRec.y + buttonRec.height / 2, 
                              buttonRec.width, buttonRec.height };
        Vector2 origin = { buttonRec.width / 2, buttonRec.height / 2 };

        DrawTexturePro(startButtonTexture, sourceRec, destRec, origin, rotation, WHITE);

        EndDrawing();
    }

    UnloadTexture(startButtonTexture);
    UnloadTexture(backgroundTexture);
    UnloadTexture(soundButtonTexture);
    UnloadTexture(muteButtonTexture);
    CloseWindow();
}

void EndgameScore()
{
    Texture2D player1winTexture = LoadTexture("pic/menu/final(1)win.png");
    Texture2D player2winTexture = LoadTexture("pic/menu/final(2)win.png");
    Texture2D playerDraw = LoadTexture("pic/menu/finalDraw.png");
    
    bool gamestart = false;
    bool game_over = false;
    while (!WindowShouldClose())
    {  
        if(!gamestart){
            ClearBackground(RAYWHITE);
            BeginDrawing();
    
            int player_score[2] = {2, 1};
    
            if(player_score[0] > player_score[1]) DrawTexture(player1winTexture,0,0,WHITE);
            else if(player_score[0] < player_score[1]) DrawTexture(player2winTexture,0,0,WHITE);
            else DrawTexture(playerDraw,0,0,WHITE);
    
            EndDrawing();
        }else if(!game_over){
            if (WindowShouldClose()) {
                ClearBackground(RAYWHITE);
            }
        }

    }
    CloseWindow(); 
}

void score()
{
    Texture2D scoreTexture = LoadTexture("pic/menu/scoreboard.png");
    
    bool gamestart = false;
    bool game_over = false;
    while (!WindowShouldClose())
    {  
        if(!gamestart){
            ClearBackground(RAYWHITE);
            BeginDrawing();
 
            //วาด scoreboard
            DrawTexture(scoreTexture,0,0,WHITE);
            EndDrawing();
        }else if(!game_over){
            if (WindowShouldClose()) {
                ClearBackground(RAYWHITE);
            }
        }

    }
    CloseWindow();
}