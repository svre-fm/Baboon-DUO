#ifndef MEMORY_H
#define MEMORY_H

#include "raylib.h"
#include <vector>
#include <string>

class Memory {
private:
    const int screenWidth = 1200;
    const int screenHeight = 800;

    int round;
    int player1_score;
    int player2_score;

    std::vector<std::string> random_moves;
    std::vector<char> correct_p1;
    std::vector<int> correct_p2;

    std::vector<char> player1_inputs;
    std::vector<int> player2_inputs;

    std::vector<char> display_p1;
    std::vector<char> display_p2;

    int correct_count_p1;
    int correct_count_p2;

    bool player1_failed;
    bool player2_failed;

    int current_index;
    float timer;
    float display_duration;
    bool showing_target;

public:
    Memory();
    void GenerateNewRound();
    void Update();
    void Draw();
    void Run();
};

#endif
