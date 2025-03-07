#ifndef MEMORY_H
#define MEMORY_H

#include "raylib.h"
#include <vector>
#include <string>
#include "countdown.h"
#include "style.h"
#include "object.h"

class Memory {
public:
    Memory();
    void Run();
    Countdown Cd_gamestart = Countdown(3.0f);
    bool gamestart = false;
    bool gameover = false;

private:
    void GenerateNewRound();
    void Update();
    void Draw();
    bool gameOver;

    const int screenWidth = 1200;
    const int screenHeight = 800;

    Texture2D img1, img2, img3, img4, img5, img13, img14;
    Texture2D img6, img7, img8, img9, img10, img11, img12;
    Texture2D imgup, imgdown, imgleft, imgright; // รูปภาพทิศทาง
    Texture2D P1win, P2win, draw;

    int round;
    int player1_score, player2_score;
    std::vector<std::string> random_moves;
    std::vector<int> correct_p1;
    std::vector<char> correct_p2;

    std::vector<int> player1_inputs;
    std::vector<char> player2_inputs;

    std::vector<int> display_p1;
    std::vector<int> display_p2;

    int correct_count_p1;
    int correct_count_p2;

    bool players_can_type;
    int current_index;
    float timer;
    float display_duration;
    float wait;
    bool showing_target;
    int countdown;

    float countdownTimer; // ตัวจับเวลา 7.5 วินาที
    Texture2D player1Image;  // ภาพของ player1
    Texture2D player2Image;  // ภาพของ player2
    int jump;
};

#endif