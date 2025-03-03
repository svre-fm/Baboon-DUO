#include <iostream>
#include <raylib.h>
#include "command.h"
#include "Memory.h"
#include "paint.h"
#include "pingpong.h"
#include "ObstacleRush.h"
#include "tutorial.h"
#include "Menu.h"
#include "global.h"

using namespace std;

int main() {
    InitWindow(1200, 800, "Baboon DUO");
    SetTargetFPS(60);
    GameState state;
    Memory play;
    GAME_OVER = false;
    // สุ่มเกมแค่ครั้งเดียว
    int rand_game[5] = {0, 1, 2, 3, 4};
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int random_index = rand() % 5;  // เลือก index สุ่มจาก 0-4
        int temp = rand_game[i];
        rand_game[i] = rand_game[random_index];
        rand_game[random_index] = temp;
    }
    
    // สุ่มเลือกเกมที่จะแสดง
    int games_played = 0;  // ตัวแปรที่ใช้ติดตามจำนวนเกมที่เล่นแล้ว
    int selected_game = rand_game[games_played];  // เริ่มเกมที่สุ่มมา
    showMenu();
    while (!WindowShouldClose() && games_played < 5) {  // ทำงานจนกว่าเล่นครบ 5 เกม
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (!state.isGameRunning) {
             // แสดงเมนู
            
            // เมื่อออกจากเมนูแล้ว, จะเข้าสู่ switch-case และเลือกเกมที่สุ่มไว้
            if (!GAME_OVER) {  // ถ้าเกมยังไม่จบ
                bool Ready = false;  // ประกาศตัวแปร Ready ข้างนอกก่อน

                // ใช้ switch-case เลือกเกมที่สุ่มไว้
                switch (selected_game) {
                    case 0:
                        showtutorial_CM(Ready);
                        if (Ready) {
                            playcommand();
                            Round++;
                            score();
                        }
                        break;

                    case 1:
                        showtutorial_PP(Ready);
                        if (Ready) {
                            playpingpong();
                            Round++;
                            score();
                        }
                        break;

                    case 2:
                        showtutorial_PC(Ready);
                        if (Ready) {
                            playpaint();
                            Round++;
                            score();
                        }
                        break;

                    case 3:
                        showtutorial_OB(Ready);
                        if (Ready) {
                            playObstacleRush();
                            Round++;
                            score();
                        }
                        break;

                    case 4:
                        showtutorial_MM(Ready);
                        if (Ready) {
                            play.Run();
                            Round++;
                            score();}
                        break;

                    default:
                        cout << "เลขไม่ถูกต้อง" << endl;
                        break;
                }

                games_played++;  // เพิ่มจำนวนเกมที่เล่นแล้ว
                if (games_played < 5) {
                    selected_game = rand_game[games_played];  // เลือกเกมถัดไปในลำดับที่สุ่ม
                }
                if (PLAY1_SCORE == 3) {
                    EndgameScore();  // เรียกฟังก์ชันเมื่อ p1 ชนะ 3 เกม
                } else if (PLAY2_SCORE == 3) {
                    EndgameScore();  // เรียกฟังก์ชันเมื่อ p2 ชนะ 3 เกม
                }else if(Round > 5){
                    EndgameScore();
                }
                
            }
        }

        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}
