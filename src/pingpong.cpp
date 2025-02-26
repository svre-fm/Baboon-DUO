#include <raylib.h>
#include <iostream>
#include "pingpong.h"
#include "object.h"
#include "style.h"

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

    if (IsKeyDown(KEY_W)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_S)) {
        y += speed;
    }
    LimitMovement();
}


// Main game function
void playpingpong() {
    result result;
    style style;
    Texture2D bg = LoadTexture("pic/pingpong/bg.png");

    banana ball;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 10;
    ball.speed_y = 10;

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

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball.Update();
        player1.Update();
        player2.Update();

        Rectangle ballRect = { ball.x - ball.pic.width / 2, ball.y - ball.pic.height / 2, (float)ball.pic.width, (float)ball.pic.height };

        // ตรวจจับการชนกับ Player 1
        if (CheckCollisionRecs(ballRect, {player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1.4f;
            ball.speed_y *= 1.4f;  // เปลี่ยนทิศทางลูกบอล
            ball.x = player1.x - ball.pic.width / 2 - 1;  // ปรับตำแหน่งลูกบอลให้อยู่ด้านซ้ายของ Paddle 1

            if (abs(ball.speed_x) > ball.max_speed) ball.speed_x = ball.max_speed * (ball.speed_x > 0 ? 1 : -1);
            if (abs(ball.speed_y) > ball.max_speed) ball.speed_y = ball.max_speed * (ball.speed_y > 0 ? 1 : -1);

        }
        
        // ตรวจจับการชนกับ Player 2
        if (CheckCollisionRecs(ballRect, {player2.x, player2.y, player2.width, player2.height})) {
            ball.speed_x *= -1.4f;  // เพิ่มความเร็ว 10%
            ball.speed_y *= 1.4f;   // เพิ่มความเร็ว 10%
            ball.x = player2.x + player2.width + ball.pic.width / 2 + 1;  // ปรับตำแหน่งลูกบอลให้อยู่ด้านขวาของ Paddle 2

            // จำกัดความเร็วไม่ให้เกิน max_speed
            if (abs(ball.speed_x) > ball.max_speed) ball.speed_x = ball.max_speed * (ball.speed_x > 0 ? 1 : -1);
            if (abs(ball.speed_y) > ball.max_speed) ball.speed_y = ball.max_speed * (ball.speed_y > 0 ? 1 : -1);
        }         

        if (P1score == 3 || P2score == 3) {
            game_over = true;
        }
    

    DrawTexture(bg,0,0,WHITE);

    if (!game_over) {
        ball.drawbanana();
        player1.Draw();
        player2.Draw();
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
            } else if (P2score > P1score) {
                result.draw(1);
                style.centerX("Player 2 win", 100, 110, DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
            } else if (P1score == P2score) {
                result.draw(2);
                style.centerX("Draw", 150, 110, DARKBROWN);
                DrawText(scoreP1,780,620,50,DARKBROWN);
                DrawText(scoreP2,405,620,50,DARKBROWN);
            }
        }

        EndDrawing();

        if (WindowShouldClose()) {
            break; 
        }

    }
    player1.unload();
    player2.unload();
    UnloadTexture(bg);
}