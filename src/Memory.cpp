#include "Memory.h"
#include <cstdlib>
#include <ctime>

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

    player1_failed = false;
    player2_failed = false;

    current_index = 0;
    timer = 0;
    display_duration = 1.5f;  // 1.5s for showing each target (1s normal, 0.5s background color)
    showing_target = true;

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

    player1_failed = false;
    player2_failed = false;

    current_index = 0;
    timer = 0;
    showing_target = true;
}

void Memory::Update() {
    // ติดตามเวลาการแสดงเป้าหมาย
    timer += GetFrameTime();
    
    if (showing_target) {
        // แสดงตัวเลขในช่วงเวลา 1.5 วินาที
        if (timer >= 1.0f && timer < 1.5f) {
            // แสดงตัวเลขด้วยสีปกติในช่วง 1 วินาทีแรก
            showing_target = true;
        } else if (timer >= 1.5f) {
            // ตัวเลขหายไปในช่วง 0.5 วินาทีที่เหลือ
            timer = 0;
            current_index++;
            
            // เปลี่ยนไปแสดงเลขถัดไปหลังจากแสดงครบ 1.5 วินาที
            if (current_index >= 5) {
                showing_target = false;
            }
        }
    }

    // ✅ Player 1 (WASD) - รีเซ็ตเมื่อกดผิด
    if (!player1_failed && (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))) {
        char input = 0;
        if (IsKeyPressed(KEY_W)) input = 'w';
        else if (IsKeyPressed(KEY_A)) input = 'a';
        else if (IsKeyPressed(KEY_S)) input = 's';
        else if (IsKeyPressed(KEY_D)) input = 'd';

        int index = player1_inputs.size();
        if (index < 5) {
            player1_inputs.push_back(input);
            if (input == correct_p1[index]) {
                display_p1[index] = '+';
                correct_count_p1++;
            } else {
                display_p1[index] = '-';
                player1_failed = true;
            }
        }
    }

    // ✅ Player 2 (Arrow Keys) - รีเซ็ตเมื่อกดผิด
    if (!player2_failed && (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_RIGHT))) {
        int input = 0;
        if (IsKeyPressed(KEY_UP)) input = KEY_UP;
        else if (IsKeyPressed(KEY_LEFT)) input = KEY_LEFT;
        else if (IsKeyPressed(KEY_DOWN)) input = KEY_DOWN;
        else if (IsKeyPressed(KEY_RIGHT)) input = KEY_RIGHT;

        int index = player2_inputs.size();
        if (index < 5) {
            player2_inputs.push_back(input);
            if (input == correct_p2[index]) {
                display_p2[index] = '+';
                correct_count_p2++;
            } else {
                display_p2[index] = '-';
                player2_failed = true;
            }
        }
    }

    // ✅ ถ้าผู้เล่นพิมพ์ผิด ต้องพิมพ์ใหม่
    if (player1_failed) {
        player1_inputs.clear();
        display_p1.assign(5, '_');
        correct_count_p1 = 0;
        player1_failed = false;
    }
    if (player2_failed) {
        player2_inputs.clear();
        display_p2.assign(5, '_');
        correct_count_p2 = 0;
        player2_failed = false;
    }

    // ✅ ถ้าทีมใดทีมหนึ่งได้ + ครบ 5 ตัว ให้ไปด่านต่อไปทันที  
    if (correct_count_p1 == 5) {
        player1_score++;
        GenerateNewRound();
    } else if (correct_count_p2 == 5) {
        player2_score++;
        GenerateNewRound();
    }
}

void Memory::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Memory Game", 450, 20, 40, DARKBLUE);
    DrawText(TextFormat("Round: %d", round), 500, 80, 30, BLACK);
    DrawText(TextFormat("Player 1 Score: %d", player1_score), 100, 140, 30, RED);
    DrawText(TextFormat("Player 2 Score: %d", player2_score), 900, 140, 30, BLUE);

    DrawText("Target:", 550, 200, 30, BLACK);

    if (showing_target && current_index < 5) {
        // แสดงตัวเลขที่ตำแหน่งกลางหน้าจอ
        if (timer < 1.0f) {
            // 1 วินาทีแรกเป็นสีปกติ
            DrawText(random_moves[current_index].c_str(), GetScreenWidth() / 2 - MeasureText(random_moves[current_index].c_str(), 50) / 2, GetScreenHeight() / 2 - 25, 50, BLACK);
        } else {
            // 0.5 วินาทีถัดไปเป็นสีพื้นหลัง
            DrawText(random_moves[current_index].c_str(), GetScreenWidth() / 2 - MeasureText(random_moves[current_index].c_str(), 50) / 2, GetScreenHeight() / 2 - 25, 50, RAYWHITE);
        }
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
