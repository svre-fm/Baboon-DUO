#include "Memory.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Memory::Memory() {
    InitWindow(screenWidth, screenHeight, "Memory Game (Raylib)");
    SetTargetFPS(60);
    srand(time(0));

    round = 1;
    player1_score = 0;
    player2_score = 0;

    random_moves.resize(5);
    correct_p1.resize(5);
    correct_p2.resize(5);
    display_p1.assign(5, '_');
    display_p2.assign(5, '_');

    correct_count_p1 = 0;
    correct_count_p2 = 0;

    players_can_type = false;
    current_index = 0;
    timer = 0;
    display_duration = 2.0f;  // 2 วินาทีต่อเลข (1 วิ สีปกติ + 1 วิ สีพื้นหลัง)
    showing_target = true;
    countdown = 3;

    GenerateNewRound();
}

void Memory::GenerateNewRound() {
    std::vector<std::string> moves = {"up", "down", "left", "right"};
    
    for (int j = 0; j < 5; ++j) {
        int randIndex = rand() % 4;
        random_moves[j] = moves[randIndex];

        if (random_moves[j] == "up") {
            correct_p1[j] = 'w';
            correct_p2[j] = KEY_UP;
        } else if (random_moves[j] == "down") {
            correct_p1[j] = 's';
            correct_p2[j] = KEY_DOWN;
        } else if (random_moves[j] == "left") {
            correct_p1[j] = 'a';
            correct_p2[j] = KEY_LEFT;
        } else if (random_moves[j] == "right") {
            correct_p1[j] = 'd';
            correct_p2[j] = KEY_RIGHT;
        }
    }
    
    player1_inputs.clear();
    player2_inputs.clear();
    display_p1.assign(5, '_');
    display_p2.assign(5, '_');
    correct_count_p1 = 0;
    correct_count_p2 = 0;

    players_can_type = false;
    current_index = 0;
    timer = 0;
    showing_target = true;
    countdown = 3;
}

void Memory::Update() {
    timer += GetFrameTime();
    
    if (showing_target) {
        if (timer >= display_duration) {
            timer = 0;
            current_index++;

            if (current_index >= 5) {
                showing_target = false;
                countdown = 3;  // ตั้งค่าเริ่มต้นนับถอยหลัง
            }
        }
    } else if (countdown > 0) {
        if (timer >= 1.0f) {
            timer = 0;
            countdown--;
            if (countdown == 0) {
                players_can_type = true;
            }
        }
    } else if (players_can_type) {
        if (player1_inputs.size() < 5 && (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))) {
            char input = 0;
            if (IsKeyPressed(KEY_W)) input = 'w';
            else if (IsKeyPressed(KEY_A)) input = 'a';
            else if (IsKeyPressed(KEY_S)) input = 's';
            else if (IsKeyPressed(KEY_D)) input = 'd';

            int index = player1_inputs.size();
            if (index < 5) {
                player1_inputs.push_back(input);
                display_p1[index] = (input == correct_p1[index]) ? '+' : '-';
                if (input == correct_p1[index]) correct_count_p1++;
            }
        }

        if (player2_inputs.size() < 5 && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT))) {
            int input = 0;
            if (IsKeyPressed(KEY_UP)) input = KEY_UP;
            else if (IsKeyPressed(KEY_LEFT)) input = KEY_LEFT;
            else if (IsKeyPressed(KEY_DOWN)) input = KEY_DOWN;
            else if (IsKeyPressed(KEY_RIGHT)) input = KEY_RIGHT;

            int index = player2_inputs.size();
            if (index < 5) {
                player2_inputs.push_back(input);
                display_p2[index] = (input == correct_p2[index]) ? '+' : '-';
                if (input == correct_p2[index]) correct_count_p2++;
            }
        }

        if (player1_inputs.size() == 5 && player2_inputs.size() == 5) {
            if (correct_count_p1 == 5) player1_score++;
            if (correct_count_p2 == 5) player2_score++;
            round++;
            GenerateNewRound();
        }
    }
}

void Memory::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Memory Game", 450, 20, 40, DARKBLUE);
    DrawText(TextFormat("Round: %d", round), 500, 80, 30, BLACK);
    DrawText(TextFormat("Player 1 Score: %d", player1_score), 100, 140, 30, RED);
    DrawText(TextFormat("Player 2 Score: %d", player2_score), 900, 140, 30, BLUE);

    if (showing_target && current_index < 5) {
        Color textColor = (fmodf(timer, 2.0f) < 1.0f) ? BLACK : RAYWHITE;
        DrawText(random_moves[current_index].c_str(), screenWidth / 2 - 50, screenHeight / 2 - 50, 50, textColor);
    }

    if (!showing_target && countdown > 0) {
        DrawText(TextFormat("%d", countdown), screenWidth / 2 - 20, screenHeight / 2 - 50, 60, BLACK);
    }

    DrawText("Player 1:", 200, 350, 30, RED);
    for (int i = 0; i < 5; i++) {
        DrawText(TextFormat("%c", display_p1[i]), 250 + (i * 60), 400, 40, RED);
    }

    DrawText("Player 2:", 800, 350, 30, BLUE);
    for (int i = 0; i < 5; i++) {
        DrawText(TextFormat("%c", display_p2[i]), 850 + (i * 60), 400, 40, BLUE);
    }

    EndDrawing();
}

void Memory::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    CloseWindow();
}
