#ifndef MEMORY_H
#define MEMORY_H

#include "raylib.h"
#include <vector>
#include <string>

class Memory {
public:
    Memory();
    void Run();

private:
    void GenerateNewRound();
    void Update();
    void Draw();

    const int screenWidth = 1200;
    const int screenHeight = 800;

    Texture2D img1, img2, img3, img4, img5, img13, img14;
    Texture2D img6, img7, img8, img9, img10, img11, img12;
    Texture2D imgup, imgdown, imgleft, imgright; // รูปภาพทิศทาง

    int round;
    int player1_score, player2_score;
    std::vector<std::string> random_moves;
    std::vector<char> correct_p1;
    std::vector<int> correct_p2;

    std::vector<char> player1_inputs;
    std::vector<int> player2_inputs;

    std::vector<int> display_p1;
    std::vector<int> display_p2;

    int correct_count_p1;
    int correct_count_p2;

    bool players_can_type;
    int current_index;
    float timer;
    float display_duration;
    bool showing_target;
    int countdown;

    float countdownTimer; // ตัวจับเวลา 7.5 วินาที
    Texture2D player1Image;  // ภาพของ player1
    Texture2D player2Image;  // ภาพของ player2
    int jump;
};

#endif
