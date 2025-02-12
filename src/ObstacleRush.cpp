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
    float car1_width = 30, car1_height = 50;
    float car2_width = 30, car2_height = 50;

    float car1_x = Bounce_screen + 20 ;
    float car1_y = MAP_HEIGHT - car1_height - Bounce_screen;

    float car2_x = Bounce_screen + 80; 
    float car2_y = MAP_HEIGHT - car2_height - Bounce_screen;

    float car1_speed = 0, car1_rotation = 0;
    float car2_speed = 0, car2_rotation = 0;

    bool game_over = false;
    string winner = "";

    InitWindow(MAP_WIDTH, MAP_HEIGHT, "Obstacle Rush");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {    
        float dt = GetFrameTime();
        BeginDrawing();
        ClearBackground(RAYWHITE);

        cout << car1_speed << " " << car2_speed << endl;

        Vector2 car_origin = { car1_width / 2, car1_height / 2 };
        Rectangle car1_rec = { car1_x, car1_y, car1_width, car1_height };
        Rectangle car2_rec = { car2_x, car2_y, car2_width, car2_height };
        Rectangle finish_line = { MAP_WIDTH - 300, 50, 300, 20 };
        Rectangle obstacles[] = {
            { 200, 300, 10, 500 },
            { 700, 300, 120, 60 },
            { 500, 600, 80, 40 },
            { 500, 600, 10 , 500}
        };
        
        int num_obstacles = sizeof(obstacles) / sizeof(obstacles[0]);

        if(!game_over){
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
            if (car1_x > MAP_WIDTH) { // ขอบขวา
                car1_x = MAP_WIDTH;
                car1_speed = -car1_speed * 0.5;
            }
            if (car1_y < Bounce_screen) { // ขอบบน
                car1_y = Bounce_screen;
                car1_speed = -car1_speed * 0.5;
            }
            if (car1_y > MAP_HEIGHT) { // ขอบล่าง
                car1_y = MAP_HEIGHT;
                car1_speed = -car1_speed * 0.5;
            }

            if (car2_x < Bounce_screen) { // ขอบซ้าย
                car2_x = Bounce_screen;
                car2_speed = -car2_speed * 0.5;
            }
            if (car2_x > MAP_WIDTH) { // ขอบขวา
                car2_x = MAP_WIDTH;
                car2_speed = -car2_speed * 0.5;
            }
            if (car2_y < Bounce_screen) { // ขอบบน
                car2_y = Bounce_screen;
                car2_speed = -car2_speed * 0.5;
            }
            if (car2_y > MAP_HEIGHT ) { // ขอบล่าง
                car2_y = MAP_HEIGHT ;
                car2_speed = -car2_speed * 0.5;
            }

            for (int i = 0; i < num_obstacles; i++) {
                // สร้าง Rectangle ของรถที่ใช้ตรวจสอบการชน
                Rectangle car1_rec = { car1_x - car1_width / 2, car1_y - car1_height / 2, car1_width, car1_height };
                Rectangle car2_rec = { car2_x - car2_width / 2, car2_y - car2_height / 2, car2_width, car2_height };
            
                // ตรวจสอบว่ารถชนสิ่งกีดขวางหรือไม่
                if (CheckCollisionRecs(car1_rec, obstacles[i])) {
                    // ตรวจสอบว่าชนด้านหน้า (กำลังเคลื่อนที่ไปข้างหน้า)
                    if (car1_speed > 0) {
                        car1_x -= 3 * sin(car1_rotation * DEG2RAD);
                        car1_y += 3 * cos(car1_rotation * DEG2RAD);
                    }
                    // ตรวจสอบว่าชนด้านหลัง (กำลังถอยหลัง)
                    else if (car1_speed < 0) {
                        car1_x += 3 * sin(car1_rotation * DEG2RAD);
                        car1_y -= 3 * cos(car1_rotation * DEG2RAD);
                    }
                    // ลดความเร็วของรถเมื่อชน
                    car1_speed = -car1_speed * 0.5;
                }
            
                if (CheckCollisionRecs(car2_rec, obstacles[i])) {
                    if (car2_speed > 0) {
                        car2_x -= 3 * sin(car2_rotation * DEG2RAD);
                        car2_y += 3 * cos(car2_rotation * DEG2RAD);
                    }
                    else if (car2_speed < 0) {
                        car2_x += 3 * sin(car2_rotation * DEG2RAD);
                        car2_y -= 3 * cos(car2_rotation * DEG2RAD);
                    }
                    car2_speed = -car2_speed * 0.5;
                }
            }

            // ตรวจสอบการชนเส้นชัย
            if (CheckCollisionRecs(car1_rec, finish_line)) {
                game_over = true;
                winner = "Player 1 Wins!";
            }
            if (CheckCollisionRecs(car2_rec, finish_line)) {
                game_over = true;
                winner = "Player 2 Wins!";
            }
        }
        
        //วาดสิ่งกีดขวาง
        for (int i = 0; i < num_obstacles; i++) {
            DrawRectangleRec(obstacles[i], GRAY);
        }

        // วาดเส้นชัย
        DrawRectangleRec(finish_line, GREEN);
        DrawText("Finish Line", finish_line.x + 100 , finish_line.y - 20, 20, BLACK);
      
        // วาดรถ
        DrawRectanglePro(car1_rec, car_origin, car1_rotation, Car1_color);
        DrawRectanglePro(car2_rec, car_origin, car2_rotation, Car2_color);

        if (game_over){
            DrawText(winner.c_str(), MAP_WIDTH / 2 - 100, MAP_HEIGHT / 2, 40, RED);
        }
        
        
        EndDrawing();
    }

    CloseWindow();
}