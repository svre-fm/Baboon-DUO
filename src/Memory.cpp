#include "Memory.h"
#include <bits/stdc++.h>

Memory::Memory() {
    InitWindow(screenWidth, screenHeight, "Memory Game (Raylib)");

    img1 = LoadTexture("pic/player_001.png");
    img2 = LoadTexture("pic/player_002.png");
    img3 = LoadTexture("pic/O.png"); 
    img4 = LoadTexture("pic/OG.png");  
    img5 = LoadTexture("pic/OR.png");   
    img6 = LoadTexture("pic/jump1.png");
    img7 = LoadTexture("pic/jump2.png"); 
    img8 = LoadTexture("pic/ete1.png");
    img9 = LoadTexture("pic/ete2.png");
    img10 = LoadTexture("pic/score_1.png");
    img11 = LoadTexture("pic/score_2.png");
    img12 =  LoadTexture("pic/bg.png");
    

    SetTargetFPS(60);
    srand(time(0));

    round = 1;
    player1_score = 0;
    player2_score = 0;

    random_moves.resize(5);
    correct_p1.resize(5);
    correct_p2.resize(5);
    display_p1.assign(5, 0);
    display_p2.assign(5, 0);

    correct_count_p1 = 0;
    correct_count_p2 = 0;

    players_can_type = false;
    current_index = 0;
    timer = 0;
    display_duration = 1.5f;
    showing_target = true;
    countdown = 3;

    countdownTimer = 0.0f;
    player1Image = img1;  
    player2Image = img2;
    
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
    display_p1.assign(5, 0);
    display_p2.assign(5, 0);
    correct_count_p1 = 0;
    correct_count_p2 = 0;

    players_can_type = false;
    current_index = 0;
    timer = 0;
    showing_target = true;
    countdown = 3;
    countdownTimer = 0;
}

void Memory::Update() {
    timer += GetFrameTime();
    countdownTimer += GetFrameTime();  // นับเวลารวมของตัวนับ 7.5 วินาที

    // การสลับภาพในช่วงเวลาต่างๆ
    if (countdownTimer < 1.5f) {
        player1Image = img1;  // ช่วงแรก player1 ใช้ img1
        player2Image = img2;  // ช่วงแรก player2 ใช้ img2
        jump = 0;
    } else if (countdownTimer < 3.0f) {
        player1Image = img6;  // ช่วงที่สอง player1 ใช้ img6
        player2Image = img7;  // ช่วงที่สอง player2 ใช้ img7
        jump = 50;
    } else if (countdownTimer < 4.5f) {
        player1Image = img1;  // ช่วงที่สาม player1 ใช้ img1
        player2Image = img2;  // ช่วงที่สาม player2 ใช้ img2
        jump = 0;
    } else if (countdownTimer < 6.0f) {
        player1Image = img6;  // ช่วงที่สี่ player1 ใช้ img6
        player2Image = img7;  // ช่วงที่สี่ player2 ใช้ img7
        jump = 50;
    } else if (countdownTimer < 7.5f) {
        player1Image = img1;  // ช่วงที่ห้า player1 ใช้ img1
        player2Image = img2;  // ช่วงที่ห้า player2 ใช้ img2
        jump = 0;
    }else if(countdownTimer < 10.5f) {
        player1Image = img8; 
        player2Image = img9;
    }//else //{
        // player1Image = img10;     
        // player2Image = img11;
    //}


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
        // โค้ดในการจัดการการกรอกข้อมูลของผู้เล่นเหมือนเดิม
        if (player1_inputs.size() < 5 && (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_D))) {
            char input = 0;
            if (IsKeyPressed(KEY_W)) input = 'w';
            else if (IsKeyPressed(KEY_A)) input = 'a';
            else if (IsKeyPressed(KEY_S)) input = 's';
            else if (IsKeyPressed(KEY_D)) input = 'd';

            int index = player1_inputs.size();
            if (index < 5) {
                player1_inputs.push_back(input);
                display_p1[index] = (input == correct_p1[index]) ? 1 : -1;
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
                display_p2[index] = (input == correct_p2[index]) ? 1 : -1;
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

    DrawTexture(img12, 0, 0, WHITE);

    DrawTexture(player1Image, 100, 500-jump, WHITE);  // ใช้ player1Image แทน img1
    DrawTexture(player2Image, 800, 500-jump, WHITE);  // ใช้ player2Image แทน img2
    
    DrawText("Memory Game", 450, 20, 40, DARKBLUE);
    DrawText(TextFormat("Round: %d", round), 500, 80, 30, BLACK);

    DrawTextureEx(img10, (Vector2){150, 30}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(img11, (Vector2){870, 30}, 0.0f, 0.5f, WHITE);

    DrawText(TextFormat("%d", player1_score), 210, 200, 30, BLUE);
    DrawText(TextFormat("%d", player2_score), 930, 200, 30, RED);

    if (showing_target && current_index < 5) {
        Color textColor = (fmodf(timer, 1.5f) < 1.0f) ? BLACK : RAYWHITE;
        DrawText(random_moves[current_index].c_str(), screenWidth / 2 - 50, screenHeight / 2 - 50, 50, textColor);
    }

    if (!showing_target && countdown > 0) {
        DrawText(TextFormat("%d", countdown), screenWidth / 2 - 20, screenHeight / 2 - 50, 60, BLACK);
    }
    for (int i = 0; i < 5; i++) {
        DrawTexture((display_p1[i] == 0) ? img3 : (display_p1[i] == 1) ? img4 : img5, 100 + (i * 60), 400, WHITE);
    }

    for (int i = 0; i < 5; i++) {
        DrawTexture((display_p2[i] == 0) ? img3 : (display_p2[i] == 1) ? img4 : img5, 800 + (i * 60), 400, WHITE);
    }

    EndDrawing();
}



void Memory::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }

    UnloadTexture(img1);
    UnloadTexture(img2);
    UnloadTexture(img3);
    UnloadTexture(img4);
    UnloadTexture(img5);
    UnloadTexture(img6);
    UnloadTexture(img7);
    UnloadTexture(img8);
    UnloadTexture(img9);

    CloseWindow();
}
