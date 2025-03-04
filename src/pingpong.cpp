#include <raylib.h>
#include <iostream>
#include "pingpong.h"
#include "object.h"
#include "style.h"
#include "global.h"


// Color definitions
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
Color brown = Color{139,69,19,255};

// Screen dimensions
const int screen_width = 1200;
const int screen_height = 800;

// Game state variables
int P1score = 0;
int P2score = 0;
bool game_over = false;


// Ball class implementation

banana::banana(){
    load();
}

banana::~banana(){
    unload();
}

void banana::load(){
    pic = LoadTexture("pic/pingpong/banana.png");
}

void banana::unload(){
    UnloadTexture(pic);
}

void banana::drawbanana(){
    DrawTextureEx(pic,{x - pic.width / 2, y - pic.height / 2,},0.0f,1.5f,WHITE);
}

void banana::Update() {
    if (game_over) return;

    x += speed_x;
    y += speed_y;

    if (y + pic.height / 2 >= GetScreenHeight() || y - pic.height / 2 <= 0) {
        speed_y *= -1;
    }

    if (x + pic.width / 2 >= GetScreenWidth()) {  
        P2score++;
        ResetBall();
    }
    
    if (x - pic.width / 2 <= 0) {
        P1score++;
        ResetBall();
    }
    
}

void banana::ResetBall() {
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;

    int speed_choices[2] = {-1, 1};
    speed_x = 7 * speed_choices[GetRandomValue(0, 1)];
    speed_y = 7 * speed_choices[GetRandomValue(0, 1)];
}


void Paddle::load(const char* path){
   texture = LoadTexture(path);
}

void Paddle::unload(){
    UnloadTexture(texture);
}

// Paddle class implementation
void Paddle::LimitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y + height >= GetScreenHeight()) {
        y = GetScreenHeight() - height;
    }
}

void Paddle::Draw() {
    DrawTextureEx(texture, {x,y}, 0.0f, 1.0f, WHITE);
}

void Paddle::Update() {}

// Player1Paddle class implementation
void Player1Paddle::Update() {
    if (game_over) return;

        // ถ้าสลับปุ่มควบคุม ให้ใช้ปุ่มลูกศร
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }

    LimitMovement();
}

void Player2Paddle::Update() {
    if (game_over) return;
        // ถ้าสลับปุ่มควบคุม ให้ใช้ปุ่ม W และ S
        if (IsKeyDown(KEY_W)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_S)) {
            y += speed;
        }
    LimitMovement();
}

void Player1Paddle::Updateswap() {
    if (game_over) return;

    // เปลี่ยนให้ Player1 ใช้ปุ่ม W/S แทน
    if (IsKeyDown(KEY_W)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        y += speed;
    }

    LimitMovement();
}

void Player2Paddle::Updateswap() {
    if (game_over) return;

    // เปลี่ยนให้ Player2 ใช้ปุ่มลูกศรขึ้น/ลงแทน
    if (IsKeyDown(KEY_UP)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y += speed;
    }

    LimitMovement();
}

PowerUp::PowerUp() : active(false) {}

void PowerUp::unload(){
    UnloadTexture(texture);
}

void PowerUp::spawn(){
    x = GetRandomValue(50,screen_width-50);
    y = GetRandomValue(50,screen_height-50);
    type = GetRandomValue(0,3);
    active = true;
    spawnTime = GetTime();

    switch (type){
        case 0:
            texture = LoadTexture("pic/pingpong/double.png");
            break;
        case 1:
            texture = LoadTexture("pic/pingpong/speed.png");
            break;
        case 2:
            texture = LoadTexture("pic/pingpong/swap.png");
            break;
        case 3:
            texture = LoadTexture("pic/pingpong/invisible.png");
            break;
        }

}

void PowerUp::draw(){
    if(active){
       DrawTextureEx(texture,{x - texture.width / 2, y - texture.height / 2}, 0.0f, 1.0f,WHITE);
    }
}

const char* PowerUp::Getname(){
    switch(type){
            case 0: return "Double Ball" ;
            case 1: return "Speed Up";
            case 2: return "Swap Controls";
            case 3: return "Invisible Ball";
            default: return "";
    }
}

// Main game function
void playpingpong() {
    result result;
    style style;
    Texture2D bg = LoadTexture("pic/pingpong/bg.png");

    banana ball1, ball2;
    ball1.x = screen_width / 2;
    ball1.y = screen_height / 2;
    ball1.speed_x = 8;
    ball1.speed_y = 8;

    ball2.x = screen_width / 2;
    ball2.y = screen_height / 2;
    ball2.speed_x = -8;
    ball2.speed_y = -8;
    bool ball2Active = false;

    Player1Paddle player1;
    player1.load("pic/pingpong/paddleP1.png");
    player1.width = player1.texture.width;
    player1.height = player1.texture.height;
    player1.x = screen_width - player1.width - 10;
    player1.y = screen_height / 2 - player1.height / 2;
    player1.speed = 10;

    Player2Paddle player2;
    player2.load("pic/pingpong/paddleP2.png");
    player2.width = player2.texture.width;
    player2.height = player2.texture.height;
    player2.x = 10;
    player2.y = screen_height / 2 - player2.height / 2;
    player2.speed = 10;

    PowerUp powerUp;
    float powerUpTimer = 0.0f;
    const float powerUpSpawnInterval = 10.0f;  // สุ่ม Power-up ทุก 10 วินาที

    // ตัวแปรสำหรับสลับปุ่มควบคุม
    bool controlsSwapped = false;  // สถานะสลับปุ่มควบคุม

    // ตัวแปรสำหรับลูกบอลล่องหน
    bool ballInvisible = false;    // สถานะลูกบอลล่องหน
    float invisibleTimer = 0.0f;  // เวลาลูกบอลล่องหน

    // ตัวแปรสำหรับแสดงชื่อ Power-up
    const char* powerUpName = "";  // ชื่อ Power-up ที่ได้รับ
    float powerUpNameTimer = 0.0f;  // เวลาแสดงชื่อ Power-up

    // ตัวแปรสำหรับระยะเวลาใช้งาน Power-up
    const float powerUpDuration = 3.0f;  // Power-up ใช้งานได้ 3 วินาที
    float powerUpActiveTime = 0.0f;      // เวลาที่ Power-up ถูกใช้งาน

    float ball_width = ball1.pic.width;
    float ball_height = ball1.pic.height;

    // เริ่มเกม
    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();
        powerUpTimer += deltaTime;
        if (ballInvisible) invisibleTimer += deltaTime;
        if (powerUpNameTimer > 0) powerUpNameTimer -= deltaTime;

        // ตรวจสอบเวลาใช้งาน Power-up
        if (powerUpActiveTime > 0) {
            powerUpActiveTime -= deltaTime;
            if (powerUpActiveTime <= 0) {
                // ยกเลิกผลของ Power-up เมื่อหมดเวลา
                switch (powerUp.type) {
                    case 0:  // ยกเลิกลูกบอลที่ 2
                        ball2Active = false;
                        break;
                    case 1:  // ยกเลิกความเร็วและขนาดลูกบอล
                        ball1.speed_x = 10.0f;
                        ball1.speed_y = 10.0f;
                        ball1.pic.width = ball_width;
                        ball1.pic.height = ball_height;
                        break;
                    case 2:  // ยกเลิกการสลับปุ่มควบคุม
                        controlsSwapped = false;
                        break;
                    case 3:  // ยกเลิกลูกบอลล่องหน
                        ballInvisible = false;
                        break;
                }
            }
        }

        // สุ่ม Power-up ทุกช่วงเวลาที่กำหนด
        if (powerUpTimer >= powerUpSpawnInterval) {
            powerUp.spawn();
            powerUpTimer = 0.0f;
        }

        BeginDrawing();
        ball1.Update();
        if (ball2Active) ball2.Update();
        if(controlsSwapped){
            player1.Updateswap();
            player2.Updateswap();
        }else{
            player1.Update();
            player2.Update();
        }
        

        Rectangle ball1Rect = { ball1.x - ball1.pic.width / 2, ball1.y - ball1.pic.height / 2, (float)ball1.pic.width, (float)ball1.pic.height };
        Rectangle ball2Rect = { ball2.x - ball2.pic.width / 2, ball2.y - ball2.pic.height / 2, (float)ball2.pic.width, (float)ball2.pic.height };

        // ตรวจจับการชนกับ Player 1
        if (CheckCollisionRecs(ball1Rect, {player1.x, player1.y, player1.width, player1.height})) {
            ball1.speed_x *= -1.2;
            ball1.speed_y *= 1.2;
            ball1.x = player1.x - ball1.pic.width / 2 - 1;
        }
        if (ball2Active && CheckCollisionRecs(ball2Rect, {player1.x, player1.y, player1.width, player1.height})) {
            ball2.speed_x *= -1;
            ball2.x = player1.x - ball2.pic.width / 2 - 1;
        }
        
        // ตรวจจับการชนกับ Player 2
        if (CheckCollisionRecs(ball1Rect, {player2.x, player2.y, player2.width, player2.height})) {
            ball1.speed_x *= -1.2;
            ball1.speed_y *= 1.2;
            ball1.x = player2.x + player2.width + ball1.pic.width / 2 + 1;
        }
        if (ball2Active && CheckCollisionRecs(ball2Rect, {player2.x, player2.y, player2.width, player2.height})) {
            ball2.speed_x *= -1;
            ball2.x = player2.x + player2.width + ball2.pic.width / 2 + 1;
        }        

        // ตรวจจับการชนกับ Power-up

            Rectangle powerUpRect = { powerUp.x - powerUp.texture.width / 2, powerUp.y - powerUp.texture.height / 2, (float)powerUp.texture.width, (float)powerUp.texture.height };

            if (powerUp.active && CheckCollisionCircleRec({ball1.x, ball1.y}, ball1.pic.width / 2, powerUpRect)){
            powerUpName = powerUp.Getname();  // เก็บชื่อ Power-up
            powerUpNameTimer = 3.0f;  // แสดงชื่อเป็นเวลา 3 วินาที
            powerUpActiveTime = powerUpDuration;  // ตั้งเวลาใช้งาน Power-up

            switch (powerUp.type) {
                case 0:  // เพิ่มลูกบอล
                    ball2Active = true;
                    break;
                case 1:  // เพิ่มความเร็วและลดขนาด
                    ball1.speed_x *= 1.2f;
                    ball1.speed_y *= 1.2f;
                    ball1.pic.width *= 0.5f;
                    ball1.pic.height *= 0.5f;
                    break;
                case 2:  // สลับปุ่มควบคุม
                    controlsSwapped = true;
                    break;
                case 3:  // ลูกบอลล่องหน
                    ballInvisible = true;
                    invisibleTimer = 0.0f;
                    break;
            }
            powerUp.active = false;  // ปิด Power-up หลังจากใช้งาน
        }

        // เช็คคะแนน
        if (ball1.x + ball1.pic.width / 2 >= GetScreenWidth()) {
            P2score++;
            ball1.ResetBall();
        }
        if (ball1.x - ball1.pic.width / 2 <= 0) {
            P1score++;
            ball1.ResetBall();
        }

        if (P1score == 5 || P2score == 5) {
            game_over = true;
        }

        DrawTexture(bg, 0, 0, WHITE);

        if (!game_over) {
            if (!ballInvisible || (int)(invisibleTimer * 10) % 4 == 0) {
                ball1.drawbanana();
                if (ball2Active) ball2.drawbanana();
            }
            player1.Draw();
            player2.Draw();
            powerUp.draw();

        if(powerUpNameTimer > 0){
            style.centerX(powerUpName,40,50,WHITE);
        }
        DrawText(TextFormat("%i", P2score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", P1score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        } else {
            const char* scoreP1 = TextFormat("%i", P1score);
            const char* scoreP2 = TextFormat("%i", P2score);
            if (P1score > P2score) {
                result.draw(0);
                style.centerX("Player 1 win", 100, 110, DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(1,1);
                    winsPlayer1[Round - 1] = 1;
                    EndDrawing();
                    return;}
            } else if (P2score > P1score) {
                result.draw(1);
                style.centerX("Player 2 win", 100, 110, DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(2,1);
                    winsPlayer2[Round - 1] = 1;
                    EndDrawing();
                    return;}
            } else if (P1score == P2score) {
                result.draw(2);
                style.centerX("Draw", 150, 110, DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
                if(IsKeyPressed(KEY_ENTER)){
                    addscore(0,0);
                    EndDrawing();
                    return;}
            }
        }

        EndDrawing();

        if (WindowShouldClose()) {
            break; 
        }

    }
    powerUp.unload();
    player1.unload();
    player2.unload();
    UnloadTexture(bg);
}