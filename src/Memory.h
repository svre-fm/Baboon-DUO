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
    const int screenWidth = 1280;
    const int screenHeight = 720;

    int round;
    int player1_score;
    int player2_score;

    std::vector<std::string> random_moves;
    std::vector<char> correct_p1;
    std::vector<int> correct_p2;
    std::vector<char> display_p1;
    std::vector<char> display_p2;

    std::vector<char> player1_inputs;
    std::vector<int> player2_inputs;

    int correct_count_p1;
    int correct_count_p2;

    bool showing_target;
    bool players_can_type;
    int current_index;
    float timer;
    float display_duration;
    
    int countdown; // ตัวแปรสำหรับนับถอยหลัง

    void GenerateNewRound();
    void Update();
    void Draw();
};

#endif
