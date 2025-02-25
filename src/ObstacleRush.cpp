#include <iostream>
#include <raylib.h>
#include <cmath>
#include "object_OB.h"
#include "ObstacleRush.h"
#include "countdown.h"
#include "object.h"
#include "style.h"

using namespace std;

#define MAP_WIDTH 1200
#define MAP_HEIGHT 800
#define Rotation_speed 100
#define Speed_increment 200
#define Max_speed 300
#define Bounce_screen 30

void playObstacleRush()
{
    DRAW DrawObject;
    style style;
    result result;

    float car1_width = 20, car1_height = 50; 
    float car2_width = 20, car2_height = 50;
    float car1_x = Bounce_screen + 60;
    float car1_y = MAP_HEIGHT - car1_height - Bounce_screen;
    float car2_x = Bounce_screen + 150; 
    float car2_y = MAP_HEIGHT - car2_height - Bounce_screen;
    float car1_speed = 0, car1_rotation = 0;
    float car2_speed = 0, car2_rotation = 0;
    float wait = 1.5f;
    bool gamestart = false;
    bool game_over = false;
    bool P1win = false;
    bool P2win = false;
    Countdown countdown = Countdown(3.0f);

    while (!WindowShouldClose()) {    
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        cout << car1_speed << " " << car2_speed << endl;

        Rectangle car1_rec = { car1_x, car1_y, car1_width, car1_height };
            Rectangle car2_rec = { car2_x, car2_y, car2_width, car2_height };
            Rectangle background_rec = { 0, 0, MAP_WIDTH, MAP_HEIGHT };
            Rectangle finish_line = {940, 100, 250, 40 };
            Rectangle obstacles[] = {
                {250, 250, 28, 550},
                {250, 250, 418, 28},
                {528, 526, 421, 28},
                {920, 0, 28, 556},

                {150,90,50,50},
                {500,680,30,30}
            };

        int num_obstacles = sizeof(obstacles) / sizeof(obstacles[0]);
        if(!gamestart){
            countdown.update(GetFrameTime());
            if (countdown.isFinished()) {
                wait -= GetFrameTime();
                if(wait <= 0){
                    gamestart = true;
                }
            }
        }else if(!game_over) {
                // Car 1 controls
                if (IsKeyDown(KEY_W)) car1_speed += Speed_increment * dt;
                if (IsKeyDown(KEY_S)) car1_speed -= Speed_increment * dt;
                if (IsKeyDown(KEY_A)) car1_rotation -= Rotation_speed * dt;
                if (IsKeyDown(KEY_D)) car1_rotation += Rotation_speed * dt;

                // Car 2 controls
                if (IsKeyDown(KEY_UP)) car2_speed += Speed_increment * dt;
                if (IsKeyDown(KEY_DOWN)) car2_speed -= Speed_increment * dt;
                if (IsKeyDown(KEY_LEFT)) car2_rotation -= Rotation_speed * dt;
                if (IsKeyDown(KEY_RIGHT)) car2_rotation += Rotation_speed * dt;

                // Speed limits
                if (car1_speed > Max_speed) car1_speed = Max_speed;
                if (car1_speed < -Max_speed) car1_speed = -Max_speed;
                if (car2_speed > Max_speed) car2_speed = Max_speed;
                if (car2_speed < -Max_speed) car2_speed = -Max_speed;

                // Movement calculations
                float rad1 = car1_rotation * DEG2RAD;
                car1_x += car1_speed * dt * sin(rad1);
                car1_y -= car1_speed * dt * cos(rad1);

                float rad2 = car2_rotation * DEG2RAD;
                car2_x += car2_speed * dt * sin(rad2);
                car2_y -= car2_speed * dt * cos(rad2);

                // Screen boundary checks
                if (car1_x < Bounce_screen) {
                    car1_x = Bounce_screen;
                    car1_speed = -car1_speed * 0.5;
                }
                if (car1_x > MAP_WIDTH) {
                    car1_x = MAP_WIDTH;
                    car1_speed = -car1_speed * 0.5;
                }
                if (car1_y < Bounce_screen) {
                    car1_y = Bounce_screen;
                    car1_speed = -car1_speed * 0.5;
                }
                if (car1_y > MAP_HEIGHT) {
                    car1_y = MAP_HEIGHT;
                    car1_speed = -car1_speed * 0.5;
                }

                if (car2_x < Bounce_screen) {
                    car2_x = Bounce_screen;
                    car2_speed = -car2_speed * 0.5;
                }
                if (car2_x > MAP_WIDTH) {
                    car2_x = MAP_WIDTH;
                    car2_speed = -car2_speed * 0.5;
                }
                if (car2_y < Bounce_screen) {
                    car2_y = Bounce_screen;
                    car2_speed = -car2_speed * 0.5;
                }
                if (car2_y > MAP_HEIGHT) {
                    car2_y = MAP_HEIGHT;
                    car2_speed = -car2_speed * 0.5;
                }

                // Obstacle collisions
                for (int i = 0; i < num_obstacles; i++) {
                    Rectangle car1_collision_rec = { car1_x - car1_width / 2, car1_y - car1_height / 2, car1_width, car1_height };
                    Rectangle car2_collision_rec = { car2_x - car2_width / 2, car2_y - car2_height / 2, car2_width, car2_height };

                    if (CheckCollisionRecs(car1_collision_rec, obstacles[i])) {
                        if (car1_speed > 0) {
                            car1_x -= 3 * sin(car1_rotation * DEG2RAD);
                            car1_y += 3 * cos(car1_rotation * DEG2RAD);
                        } else if (car1_speed < 0) {
                            car1_x += 3 * sin(car1_rotation * DEG2RAD);
                            car1_y -= 3 * cos(car1_rotation * DEG2RAD);
                        }
                        car1_speed = -car1_speed * 0.5;
                    }

                    if (CheckCollisionRecs(car2_collision_rec, obstacles[i])) {
                        if (car2_speed > 0) {
                            car2_x -= 3 * sin(car2_rotation * DEG2RAD);
                            car2_y += 3 * cos(car2_rotation * DEG2RAD);
                        } else if (car2_speed < 0) {
                            car2_x += 3 * sin(car2_rotation * DEG2RAD);
                            car2_y -= 3 * cos(car2_rotation * DEG2RAD);
                        }
                        car2_speed = -car2_speed * 0.5;
                    }
                }

                // Finish line checks
                if (CheckCollisionRecs(car1_rec, finish_line)) {
                    game_over = true;
                    P2win = true;
                }
                if (CheckCollisionRecs(car2_rec, finish_line)) {
                    game_over = true;
                    P1win = true;
                }
            }

        // Drawing
        DrawObject.drawBackground(background_rec, 1);
        if(!gamestart){
            string displaytext = countdown.getDisplayText();
            style.centerXY(displaytext, 100, WHITE);
        }else if(!game_over){
        DrawObject.drawCar(1, car1_rec, car1_rotation, 0.08);
        DrawObject.drawCar(2, car2_rec, car2_rotation, 0.08);
        }
        //วาด obstacles ดูว่าสอดคล้องกับ รูปหรือไหม
        for (int i = 0; i < num_obstacles; i++) {
            DrawRectangleRec(obstacles[i], GRAY);
        }
        
        
        if (game_over) {
            if (P1win) {
                result.draw(0);
                style.centerX("Player 1 win", 100, 110, DARKBROWN);
            } else if (P2win) {
                result.draw(1);
                style.centerX("Player 2 win", 100, 110, DARKBROWN);
            }
        }

        EndDrawing();

        if (WindowShouldClose()) {
            break; 
        }

    }
}