#include <iostream>
#include <raylib.h>
#include "Menu.h"
using namespace std;
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800

void showMenu()
{
    Texture2D startButtonTexture = LoadTexture("pic/menu/button.png");
    Texture2D backgraoundTexture = LoadTexture("pic/menu/Background.PNG");
    
    // กำหนดขนาดเริ่มต้นของปุ่ม
    float baseWidth = startButtonTexture.width;
    float baseHeight = startButtonTexture.height;
    float scale = 1.0f;
    float rotation = 0;
    bool increasing = true; // ใช้ควบคุมการหมุนไปกลับ
    bool gamestart = false;
    bool game_over = false;
    
    while (!WindowShouldClose()) {  
        Vector2 mousePoint = GetMousePosition();
        Rectangle buttonRec = { SCREEN_WIDTH / 2 - 100, 
                                SCREEN_HEIGHT / 2 + 50, 
                                baseWidth * scale, 
                                baseHeight * scale };
        
        ClearBackground(RAYWHITE);
        BeginDrawing();
        
        if(!gamestart)
        {
            bool isHover = CheckCollisionPointRec(mousePoint, buttonRec);
            if (isHover) {
                scale = 1.0f; // ขยายขนาดปุ่ม
                if (increasing) {
                    rotation += 0.80f;
                    if (rotation >= 10) increasing = false;
                } else {
                    rotation -= 0.80f;
                    if (rotation <= -10) increasing = true;
                }
            } else {
                if (scale > 1.0f) scale -= 0.01; // ค่อย ๆ ลดขนาดปุ่มจนถึง 1.0
                else scale = 1.0f; // ป้องกัน scale ต่ำกว่า 1.0
                rotation = 0; // คืนค่าการหมุนปกติ
            }
    
            // ตรวจสอบการคลิกปุ่ม
            if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                ClearBackground(RAYWHITE); // ปิดเมนูเพื่อไปที่หน้าเกม
                EndDrawing();
                gamestart = true;
            }

            Rectangle sourceRec = { 0, 0, (float)startButtonTexture.width, (float)startButtonTexture.height };
            Rectangle destRec = { buttonRec.x , buttonRec.y, buttonRec.width, buttonRec.height };
            Vector2 origin = { 0, 0};
            
            DrawTexture(backgraoundTexture,0,0,WHITE);
            DrawTexturePro(startButtonTexture, sourceRec, destRec, origin, rotation, WHITE);
            EndDrawing();
        }
        else if(!game_over) 
        {
            if (WindowShouldClose()) {
                ClearBackground(RAYWHITE);
            }
        }
    }

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