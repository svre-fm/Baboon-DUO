#include <raylib.h>
#include <iostream>
#include "pingpong.h"

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};
const int screen_width = 1280;
const int screen_height = 800;
int player_score = 0;
int cpu_score = 0;
bool game_over = false; // Flag to check if the game is over

class Ball {
 public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update() {
        if (game_over) return; // If the game is over, stop updating the ball

        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        // Cpu wins
        if (x + radius >= GetScreenWidth()) {
            cpu_score++;
            ResetBall();
        }

        if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle {
 protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }

 public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    virtual void Update() {
        // Default controls for Paddle
    }
};

class Player1Paddle : public Paddle {
 public:
    void Update() override {
        if (game_over) return; // Stop updating paddles if the game is over

        if (IsKeyDown(KEY_UP)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y = y + speed;
        }
        LimitMovement();
    }
};

class Player2Paddle : public Paddle {
 public:
    void Update() override {
        if (game_over) return; // Stop updating paddles if the game is over

        if (IsKeyDown(KEY_W)) {
            y = y - speed;
        }
        if (IsKeyDown(KEY_S)) {
            y = y + speed;
        }
        LimitMovement();
    }
};

Ball ball;
Player1Paddle player1;  // Player 1's paddle
Player2Paddle player2; // Player 2's paddle

void playpingpong() {
    std::cout << "Starting the game" << std::endl;
    
    InitWindow(screen_width, screen_height, "2 Player Pong Game!");
    SetTargetFPS(60);
    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 9;
    ball.speed_y = 9;

    player1.width = 25;
    player1.height = 120;
    player1.x = screen_width - player1.width - 10;
    player1.y = screen_height / 2 - player1.height / 2;
    player1.speed = 6;

    player2.width = 25;
    player2.height = 120;
    player2.x = 10;
    player2.y = screen_height / 2 - player2.height / 2;
    player2.speed = 6;

    while (WindowShouldClose() == false) {
        BeginDrawing();

        // Updating
        ball.Update();
        player1.Update();
        player2.Update();

        // Checking for collisions
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player2.x, player2.y, player2.width, player2.height})) {
            ball.speed_x *= -1;
        }

        // Drawing
        ClearBackground(Dark_Green);
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player1.Draw();
        player2.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        // Check if any player has won
        if (player_score == 3) {
            DrawText("Player 1 Wins!", screen_width / 2 - 150, screen_height / 2 - 40, 80, WHITE);
            DrawText("Press Enter to Exit", screen_width / 2 - 180, screen_height / 2 + 40, 40, WHITE);
            game_over = true; // Set game_over flag to true
        } else if (cpu_score == 3) {
            DrawText("Player 2 Wins!", screen_width / 2 - 150, screen_height / 2 - 40, 80, WHITE);
            DrawText("Press Enter to Exit", screen_width / 2 - 180, screen_height / 2 + 40, 40, WHITE);
            game_over = true; // Set game_over flag to true
        }

        if (game_over && IsKeyPressed(KEY_ENTER)) {
            CloseWindow();  // Close the game window if Enter is pressed
        }

        EndDrawing();
    }

}
