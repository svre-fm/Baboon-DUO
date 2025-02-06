#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

#define Background_color (Color){255, 153, 51}
#define Car_color WHITE
#define Rotation_speed 100 // เพิ่มความเร็วในการหมุนให้มากขึ้น
int main()
{
    float Width = 1200;
    float Height = 800;
    float car_width = 50;
    float car_height = 100;
    float car_x = Width/2 - car_width/2;
    float car_y = Height/2 - car_height/2;
    float car_speed = 0;
    float car_max_speed = 300; // ลดความเร็วสูงสุดเพื่อการควบคุมที่ดีขึ้น
    float car_rotation = 0;
    float car_speedup = 200;
    float car_slowdown = 200;

    InitWindow(Width, Height, "Obstacle Rush");
    SetTargetFPS(60);

    while (!WindowShouldClose()){    
        float dt = GetFrameTime(); // คำนวณ delta time
        
        BeginDrawing();
        ClearBackground(Background_color);

        // การเร่งและลดความเร็ว
        if(IsKeyDown(KEY_UP)){
            car_speed += car_speedup * dt;
            if(car_speed > car_max_speed) car_speed = car_max_speed;
        }else if(IsKeyDown(KEY_DOWN)){
            car_speed -= car_slowdown * dt;
            if(car_speed < -car_max_speed) car_speed = -car_max_speed;
        }else{
            // ทำให้รถชะลอเมื่อไม่ได้กดปุ่มเร่ง
            car_speed *= 0.98;
        }    

        // การหมุนรถ
        if(IsKeyDown(KEY_LEFT)){
            car_rotation -= Rotation_speed * dt;
        }else if(IsKeyDown(KEY_RIGHT)){
            car_rotation += Rotation_speed * dt;
        }

        // อัปเดตตำแหน่งรถตามทิศทางที่หมุน
        float rad = car_rotation * DEG2RAD; // แปลงองศาเป็นเรเดียน
        car_x += car_speed * dt * sin(rad); // การเคลื่อนที่แนวแกน x
        car_y -= car_speed * dt * cos(rad); // การเคลื่อนที่แนวแกน y

        // วาดรถ
        Rectangle car_rec = { car_x, car_y, car_width, car_height };
        Vector2 car_origin = { car_width/2, car_height/2 };

        DrawRectanglePro(car_rec, car_origin, car_rotation, Car_color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
