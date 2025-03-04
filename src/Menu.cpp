#include <iostream>
#include <raylib.h>
#include "Menu.h"
#include "global.h"
using namespace std;
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800


void showMenu(){
    InitAudioDevice();
    Music musicmenu = LoadMusicStream("sound/menu.mp3");
    Sound clickSound = LoadSound("sound/click.mp3");
    Texture2D startButtonTexture = LoadTexture("pic/menu/button.png");
    Texture2D backgraoundTexture = LoadTexture("pic/menu/Background.PNG");
    PlayMusicStream(musicmenu);
    
    // กำหนดขนาดเริ่มต้นของปุ่ม
    float baseWidth = startButtonTexture.width;
    float baseHeight = startButtonTexture.height;
    float scale = 1.0f;
    float rotation = 0;
    double waittime = -1.0;
    bool click = false;
    bool increasing = true; // ใช้ควบคุมการหมุนไปกลับ
    bool gamestart = false;
    bool game_over = false;
    
    while (!WindowShouldClose() && !gamestart){  
        UpdateMusicStream(musicmenu);
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
            if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                PlaySound(clickSound);
                click = true;
            }

            if(click){
                if (waittime < 0){
                    waittime = GetTime();
                } else if (GetTime() - waittime >= 1.0) {
                    gamestart = true;
                    break;
                }
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
    UnloadSound(clickSound);
    UnloadMusicStream(musicmenu);
    CloseAudioDevice();
    return; 
}

void EndgameScore()
{
    InitAudioDevice();
    Music musicmenu = LoadMusicStream("sound/win.mp3");
    PlayMusicStream(musicmenu);

    Texture2D player1winTexture = LoadTexture("pic/menu/final(1)win.png");
    Texture2D player2winTexture = LoadTexture("pic/menu/final(2)win.png");
    Texture2D playerDraw = LoadTexture("pic/menu/finalDraw.png");
    PlayMusicStream(musicmenu);

    while (!WindowShouldClose()){
        UpdateMusicStream(musicmenu);  
        BeginDrawing(); // เริ่มการวาด
        ClearBackground(RAYWHITE); 

        // ตรวจสอบคะแนนแล้วแสดงภาพที่เหมาะสม
        if (PLAY1_SCORE > PLAY2_SCORE)  
            DrawTexture(player1winTexture, 0, 0, WHITE);
        else if (PLAY2_SCORE > PLAY1_SCORE) 
            DrawTexture(player2winTexture, 0, 0, WHITE);
        else 
            DrawTexture(playerDraw, 0, 0, WHITE);

        EndDrawing(); // จบการวาด
        
        // ออกจากลูปเมื่อกด Enter
        if (IsKeyPressed(KEY_ENTER)) {
            UnloadMusicStream(musicmenu);
            CloseAudioDevice();
            break;
        }
    }
    UnloadMusicStream(musicmenu);
    CloseAudioDevice();
    CloseWindow();
}


void score(){
    InitAudioDevice();
    Music musicmenu = LoadMusicStream("sound/menu.mp3");
    PlayMusicStream(musicmenu);
    Texture2D scoreTexture = LoadTexture("pic/menu/scoreboard.png");  // โหลดภาพ scoreboard
    Texture2D win1 = LoadTexture("pic/menu/1win.png");    // รูปที่ 1
    Texture2D win2 = LoadTexture("pic/menu/2win.png");    // รูปที่ 2
    Texture2D draw = LoadTexture("pic/menu/Draw.png"); 
    Texture2D blank = LoadTexture("pic/command/blank.png");   
    bool gamestart = false;  // สถานะเกมเริ่ม
    PlayMusicStream(musicmenu);
    
    while (!WindowShouldClose()&&!gamestart){
        UpdateMusicStream(musicmenu);  
        ClearBackground(RAYWHITE);
        BeginDrawing();

        // วาด scoreboard

        DrawTexture(scoreTexture, 0, 0, WHITE);
        

        for (int gameCount = 1; gameCount <= 5; gameCount++) {
            if (winsPlayer1[gameCount - 1] == 1) {
                // ถ้า P1 ชนะในเกมนี้
                DrawTexture(win1, 165 + (gameCount * 155), 375, WHITE);
            } else if (winsPlayer2[gameCount - 1] == 1) {
                // ถ้า P2 ชนะในเกมนี้
                DrawTexture(win2, 165 + (gameCount * 155), 375, WHITE);
            } else if(winsPlayer1[gameCount - 1] == 2){
                // ถ้าเกมนี้เสมอ
                DrawTexture(draw, 165 + (gameCount * 155), 375, WHITE);
            }else {
                DrawTexture(blank, 165 + (gameCount * 155), 375, WHITE); 
            }
        }

        
        // ตรวจสอบการกด ENTER เพื่อไปยังเกมถัดไป
        if (IsKeyPressed(KEY_ENTER)) {
            gamestart = true;  // เริ่มเกมใหม่
            UnloadMusicStream(musicmenu);
            CloseAudioDevice();
            return;  // ออกจากฟังก์ชัน score() ทันที
        }
        EndDrawing();
    }
    CloseWindow();
}
