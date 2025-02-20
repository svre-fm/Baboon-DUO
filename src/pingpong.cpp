#include <raylib.h>
#include <iostream>
#include "pingpong.h"

// Color definitions
Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

// Screen dimensions
const int screen_width = 1200;
const int screen_height = 800;

// Game state variables
int player_score = 0;
int cpu_score = 0;
bool game_over = false;


// Ball class implementation

banana::banana(){
    load();
}

banana::~banana(){
    unload();
}

void banana::load(){
    pic = LoadTexture("graphic/banana.png");
}

void banana::unload(){
    UnloadTexture(pic);
}

void banana::drawbanana(){
    DrawTextureEx(pic,{x - pic.width / 2, y - pic.height / 2,},0.0f,1.0f,WHITE);
}

void banana::Update() {
    if (game_over) return;

    x += speed_x;
    y += speed_y;

    if (y + pic.height / 2 >= GetScreenHeight() || y - pic.height / 2 <= 0) {
        speed_y *= -1;
    }

    if (x + pic.width / 2 >= GetScreenWidth()) {  // ตรวจสอบขอบขวา
        cpu_score++;
        ResetBall();
    }
    
    if (x - pic.width / 2 <= 0) {  // ตรวจสอบขอบซ้าย
        player_score++;
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
    DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
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
    std::cout << "Starting the game" << std::endl;

    InitWindow(screen_width, screen_height, "2 Player Pong Game!");
    SetTargetFPS(60);

    banana ball;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    Player1Paddle player1;
    player1.width = 25;
    player1.height = 200;
    player1.x = screen_width - player1.width - 10;
    player1.y = screen_height / 2 - player1.height / 2;
    player1.speed = 8;

    Player2Paddle player2;
    player2.width = 25;
    player2.height = 200;
    player2.x = 10;
    player2.y = screen_height / 2 - player2.height / 2;
    player2.speed = 8;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball.Update();
        player1.Update();
        player2.Update();

        Rectangle ballRect = { ball.x - ball.pic.width / 2, ball.y - ball.pic.height / 2, (float)ball.pic.width, (float)ball.pic.height };

        // ตรวจจับการชนกับ Player 1
        if (CheckCollisionRecs(ballRect, {player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1;
            ball.x = player1.x - ball.pic.width / 2 - 1;  // ป้องกันลูกบอลติดในแพดเดิล
        }
        
        // ตรวจจับการชนกับ Player 2
        if (CheckCollisionRecs(ballRect, {player2.x, player2.y, player2.width, player2.height})) {
            ball.speed_x *= -1;
            ball.x = player2.x + player2.width + ball.pic.width / 2 + 1;  // ป้องกันลูกบอลติดในแพดเดิล
        }        

        if (player_score == 3 || cpu_score == 3) {
            game_over = true;
        }
    

        ClearBackground(Dark_Green);

        if (!game_over) {
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
            ball.drawbanana();
            player1.Draw();
            player2.Draw();
            DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);
        } else {
            ClearBackground(WHITE);
            const char* text = (player_score == 3) ? "Player 1 Wins!" : "Player 2 Wins!";
            int textWidth = MeasureText(text, 80);
            DrawText(text, (screen_width - textWidth) / 2, screen_height / 2 - 40, 80, (player_score == 3) ? RED : BLUE);
        }

        EndDrawing();
    }
    CloseWindow();
}
