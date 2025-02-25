#include "Memory.h"
#include <bits/stdc++.h>

Memory::Memory() {
    img1 = LoadTexture("pic/memory/player_001.png");
    img2 = LoadTexture("pic/memory/player_002.png");
    img3 = LoadTexture("pic/memory/O.png"); 
    img4 = LoadTexture("pic/memory/OG.png");  
    img5 = LoadTexture("pic/memory/OR.png");   
    img6 = LoadTexture("pic/memory/jump1.png");
    img7 = LoadTexture("pic/memory/jump2.png"); 
    img8 = LoadTexture("pic/memory/ete1.png");
    img9 = LoadTexture("pic/memory/ete2.png");
    img10 = LoadTexture("pic/memory/score_1.png");
    img11 = LoadTexture("pic/memory/score_2.png");
    img12 = LoadTexture("pic/memory/bg.png");
    img13 = LoadTexture("pic/memory/obj1.png");
    img14 = LoadTexture("pic/memory/obj2.png");

    imgup = LoadTexture("pic/memory/up.png");      // รูป up
    imgleft = LoadTexture("pic/memory/left.png");  // รูป left
    imgdown = LoadTexture("pic/memory/down.png");  // รูป down
    imgright = LoadTexture("pic/memory/right.png"); // รูป right

    P1win = LoadTexture("pic/result/P1win.png");
    P2win = LoadTexture("pic/result/P2win.png");
    draw = LoadTexture("pic/result/Draw.png");

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

    wait = 1.5f;
    
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
    if(!gamestart){
        Cd_gamestart.update(GetFrameTime());
            if (Cd_gamestart.isFinished()) {
                wait -= GetFrameTime();
                if(wait <= 0){
                    gamestart = true;
                }
            }
    }else{
        if (round > 5) {  
            return;  // ถ้าครบ 5 รอบแล้ว ไม่ต้องอัปเดตอะไรอีก
        }

        timer += GetFrameTime();
        countdownTimer += GetFrameTime();

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
            if (timer >= 1.5f) {  // ครบ 2 วินาที (1.5s แสดง + 0.5s ซ่อน)
                timer = 0;
                current_index++;

                if (current_index >= 5) {  // แสดงครบ 5 รูปแล้ว
                    showing_target = false;
                    countdown = 3;  // เริ่มนับถอยหลัง
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
}


void Memory::Draw() {
    style style;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawTexture(img12, 0, 0, WHITE);
    DrawTexture(img13, 430, 400, WHITE);
    DrawTexture(img14, 405, -100, WHITE);

    if(!gamestart){
        string displaytext = Cd_gamestart.getDisplayText();
        style.centerXY(displaytext, 100, WHITE);
    }else{
        if (round > 5) {
            const char* scoreP2 = TextFormat("%d", player2_score);
            const char* scoreP1 = TextFormat("%d", player1_score);
            if (player1_score > player2_score) {
                DrawTexture(P1win, 0, 0, WHITE);
                style.centerX("Player 1 win", 100, 110, DARKBROWN);
                DrawText(scoreP1,405,620,50,DARKBROWN);
                DrawText(scoreP2,780,620,50,DARKBROWN);
            } else if (player2_score > player1_score) {
                DrawTexture(P2win, 0, 0, WHITE);
                style.centerX("Player 2 win", 100, 110, DARKBROWN);
                DrawText(scoreP1,405,620,50,DARKBROWN);
                DrawText(scoreP2,780,620,50,DARKBROWN);
            } else if (player1_score == player2_score) {
                DrawTexture(draw, 0, 0, WHITE);
                style.centerX("Draw", 150, 110, DARKBROWN);
                DrawText(scoreP1,405,620,50,DARKBROWN);
                DrawText(scoreP2,780,620,50,DARKBROWN);
            }
            EndDrawing();
            return;
        }

        DrawTexture(player1Image, 100, 500 - jump, WHITE);
        DrawTexture(player2Image, 800, 500 - jump, WHITE);

        DrawText(TextFormat("Round: %d", round), 480, 160, 50, BLACK);

        DrawTextureEx(img10, (Vector2){150, 30}, 0.0f, 0.5f, WHITE);
        DrawTextureEx(img11, (Vector2){870, 30}, 0.0f, 0.5f, WHITE);

        DrawText(TextFormat("%d", player1_score), 210, 200, 30, BLUE);
        DrawText(TextFormat("%d", player2_score), 930, 200, 30, RED);

        if (showing_target && current_index < 5) {
            if (timer <= 1.0f) {  // แสดงภาพ 1.5 วินาที
                if (random_moves[current_index] == "up") {
                    DrawTextureEx(imgup, (Vector2){screenWidth / 2 - 35, screenHeight / 2 + 85}, 0.0f, 0.35f, WHITE);
                } else if (random_moves[current_index] == "down") {
                    DrawTextureEx(imgdown, (Vector2){screenWidth / 2 - 40, screenHeight / 2 + 85}, 0.0f, 0.35f, WHITE);
                } else if (random_moves[current_index] == "left") {
                    DrawTextureEx(imgleft, (Vector2){screenWidth / 2 - 48, screenHeight / 2 + 92}, 0.0f, 0.35f, WHITE);
                } else if (random_moves[current_index] == "right") {
                    DrawTextureEx(imgright, (Vector2){screenWidth / 2 - 48, screenHeight / 2 + 85}, 0.0f, 0.35f, WHITE);
                }
            }
            // ถ้า timer > 1.5s (ช่วง 0.5 วินาทีสุดท้าย) → ไม่ต้องวาดอะไรเลย
        }

        if (!showing_target && countdown > 0) {
            DrawText(TextFormat("%d", countdown), screenWidth / 2 - 25, screenHeight / 2 + 85, 60, BLACK);
        }
        for (int i = 0; i < 5; i++) {
            DrawTexture((display_p1[i] == 0) ? img3 : (display_p1[i] == 1) ? img4 : img5, 100 + (i * 60), 400, WHITE);
        }
        for (int i = 0; i < 5; i++) {
            DrawTexture((display_p2[i] == 0) ? img3 : (display_p2[i] == 1) ? img4 : img5, 800 + (i * 60), 400, WHITE);
        }
    }
    EndDrawing();
}

void Memory::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
        if (WindowShouldClose()) {
            break; 
        }
        
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
    UnloadTexture(imgup);
    UnloadTexture(imgleft);
    UnloadTexture(imgdown);
    UnloadTexture(imgright);

}