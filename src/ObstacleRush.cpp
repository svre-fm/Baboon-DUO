#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

#define MAP_WIDTH 1200
#define MAP_HEIGHT 800
#define Car1_color BLUE
#define Car2_color RED
#define Rotation_speed 100
#define Speed_increment 200
#define Max_speed 300
#define Bounce_screen 30

void playObstacleRush()
{
    float car1_width = 50, car1_height = 100;
    float car2_width = 50, car2_height = 100;

    float car1_x = MAP_WIDTH / 3 - car1_width / 2, car1_y = MAP_HEIGHT / 2 - car1_height / 2;
    float car2_x = 2 * MAP_WIDTH / 3 - car2_width / 2, car2_y = MAP_HEIGHT / 2 - car2_height / 2;

    float car1_speed = 0, car1_rotation = 0;
    float car2_speed = 0, car2_rotation = 0;

    InitWindow(MAP_WIDTH, MAP_HEIGHT, "Obstacle Rush");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {    
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // ควบคุมรถคันที่ 1
        if (IsKeyDown(KEY_W)) car1_speed += Speed_increment * dt;
        if (IsKeyDown(KEY_S)) car1_speed -= Speed_increment * dt;
        if (IsKeyDown(KEY_A)) car1_rotation -= Rotation_speed * dt;
        if (IsKeyDown(KEY_D)) car1_rotation += Rotation_speed * dt;

        // ควบคุมรถคันที่ 2
        if (IsKeyDown(KEY_UP)) car2_speed += Speed_increment * dt;
        if (IsKeyDown(KEY_DOWN)) car2_speed -= Speed_increment * dt;
        if (IsKeyDown(KEY_LEFT)) car2_rotation -= Rotation_speed * dt;
        if (IsKeyDown(KEY_RIGHT)) car2_rotation += Rotation_speed * dt;

        // จำกัดความเร็วของรถ
        if (car1_speed > Max_speed) car1_speed = Max_speed;
        if (car1_speed < -Max_speed) car1_speed = -Max_speed;

        if (car2_speed > Max_speed) car2_speed = Max_speed;
        if (car2_speed < -Max_speed) car2_speed = -Max_speed;

        // คำนวณการเคลื่อนที่
        float rad1 = car1_rotation * DEG2RAD;
        car1_x += car1_speed * dt * sin(rad1);
        car1_y -= car1_speed * dt * cos(rad1);

        float rad2 = car2_rotation * DEG2RAD;
        car2_x += car2_speed * dt * sin(rad2);
        car2_y -= car2_speed * dt * cos(rad2);

        //  **ป้องกันรถหลุดออกขอบจอ**
        if (car1_x < Bounce_screen) { // ขอบซ้าย 
            car1_x = Bounce_screen;
            car1_speed = -car1_speed * 0.5;
        }
        if (car1_x > MAP_WIDTH - Bounce_screen) { // ขอบขวา
            car1_x = MAP_WIDTH - Bounce_screen;
            car1_speed = -car1_speed * 0.5;
        }
        if (car1_y < Bounce_screen) { // ขอบบน
            car1_y = Bounce_screen;
            car1_speed = -car1_speed * 0.5;
        }
        if (car1_y > MAP_HEIGHT - Bounce_screen) { // ขอบล่าง
            car1_y = MAP_HEIGHT - Bounce_screen;
            car1_speed = -car1_speed * 0.5;
        }

        if (car2_x < Bounce_screen) { // ขอบซ้าย
            car2_x = Bounce_screen;
            car2_speed = -car2_speed * 0.5;
        }
        if (car2_x > MAP_WIDTH - Bounce_screen) { // ขอบขวา
            car2_x = MAP_WIDTH - Bounce_screen;
            car2_speed = -car2_speed * 0.5;
        }
        if (car2_y < Bounce_screen) { // ขอบบน
            car2_y = Bounce_screen;
            car2_speed = -car2_speed * 0.5;
        }
        if (car2_y > MAP_HEIGHT - Bounce_screen) { // ขอบล่าง
            car2_y = MAP_HEIGHT - Bounce_screen;
            car2_speed = -car2_speed * 0.5;
        }

        // วาดรถ
        Rectangle car1_rec = { car1_x, car1_y, car1_width, car1_height };
        Rectangle car2_rec = { car2_x, car2_y, car2_width, car2_height };

        Vector2 car_origin = { car1_width / 2, car1_height / 2 };
        DrawRectanglePro(car1_rec, car_origin, car1_rotation, Car1_color);
        DrawRectanglePro(car2_rec, car_origin, car2_rotation, Car2_color);

        EndDrawing();
    }

    CloseWindow();
}
