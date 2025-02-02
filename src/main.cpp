#include <iostream>
#include <raylib.h>

using namespace std;

#define Background_color (Color){255, 153, 51}
#define Car_color WHITE
int main(){

    int Width = 1200;
    int Height = 800;

    int car_width = 50;
    int car_height = 100;
    float car_x = Width/2 - 30;
    float car_y = Height/2 - 50;
    float car_speed = 0;
    float car_max_speed = 1000;
    // -1 up ,1 down
    int car_direction = -1;


    InitWindow(Width, Height, "Obstacle Rush");
    SetTargetFPS(60);

    while (!WindowShouldClose()){    
        // get time in seconds for last frame drawn (delta time)
        float dt = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(Background_color);

        if(IsKeyDown(KEY_UP)){

            car_direction = -1;
            //increase speed per frame when the key up.
            car_speed += 10 * dt;
            if(car_speed > car_max_speed) car_speed = car_max_speed;

        }else if(IsKeyDown(KEY_DOWN)){

            car_direction = -1;
            //decrease speed per frame when the key down.
            car_speed -= 10 * dt;
            if(car_speed > car_max_speed) car_speed = car_max_speed;

        }else{
            
            //try stop
            car_speed += 5 * dt * car_direction;
            if(car_direction == -1 && car_speed < 0) car_speed = 0;
            else if(car_direction == 1 && car_speed > 0) car_speed = 0;

        }    

        //move up
        car_y -= car_speed;

        DrawRectangle(car_x, car_y,car_width, car_height, Car_color);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}