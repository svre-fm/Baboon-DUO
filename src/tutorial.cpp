#include "tutorial.h"

class page{
    public:
        Vector2 mousePos = GetMousePosition();
        bool P1press = false;
        bool P2press = false;
        double waittime = -1.0;
        bool showFirstImage = true;
        float swapInterval = 0.5f;
        float timer = 0.0f;
        Color transparent = {255, 255, 255, 0};
        Rectangle BTleft = {45, 400, 107, 53};
        Rectangle BTright = {1045, 400, 107, 53};
        Rectangle BTleft_up = {30, 390, 138, 68};
        Rectangle BTright_up = {1030, 390, 138, 68};
        
        page();
        ~page();
        void load();
        void unload();
        void drawpage_CM(int direction) const;
        void drawpage_MM(int direction) const;
        void drawpage_OB(int direction) const;
        void drawpage_PP(int direction) const;
        void drawpage_PC(int direction) const;
        void drawbg_CM();
        void drawbg_MM();
        void drawbg_OB();
        void drawbg_PP();
        void drawbg_PC();
        void drawready(float X,float Y);
        void drawarrow();

    private:
        Texture2D CM_1;
        Texture2D CM_2;
        Texture2D CM_3;
        Texture2D MM_1;
        Texture2D MM_2;
        Texture2D PP_1;
        Texture2D PP_2;
        Texture2D PP_3;
        Texture2D OB_1;
        Texture2D OB_2;
        Texture2D PC_1;
        Texture2D PC_2;
        Texture2D PC_3;
        Texture2D bg_CM;
        Texture2D bg_MM;
        Texture2D bg_OB;
        Texture2D bg_PP;
        Texture2D bg_PC;
        Texture2D ready;
        Texture2D al,ar;
};

page::page(){
    load();
}

page::~page(){
    unload();
}

void page::load(){
    CM_1 = LoadTexture("pic/tutorial/CM_1.png");
    CM_2 = LoadTexture("pic/tutorial/CM_2.png");
    CM_3 = LoadTexture("pic/tutorial/CM_3.png");
    bg_CM = LoadTexture("pic/tutorial/command.png");
    MM_1 = LoadTexture("pic/tutorial/MM_1.png");
    MM_2 = LoadTexture("pic/tutorial/MM_2.png");
    bg_MM = LoadTexture("pic/tutorial/memory.png");
    PP_1 = LoadTexture("pic/tutorial/PP_1.png");
    PP_2 = LoadTexture("pic/tutorial/PP_2.png");
    PP_3 = LoadTexture("pic/tutorial/PP_3.png");
    bg_PP = LoadTexture("pic/tutorial/Pingpong.png");
    OB_1 = LoadTexture("pic/tutorial/OB_1.png");
    OB_2 = LoadTexture("pic/tutorial/OB_2.png");
    bg_OB = LoadTexture("pic/tutorial/obstacle.png");
    PC_1 = LoadTexture("pic/tutorial/PC_1.png");
    PC_2 = LoadTexture("pic/tutorial/PC_2.png");
    PC_3 = LoadTexture("pic/tutorial/PC_3.png");
    bg_PC = LoadTexture("pic/tutorial/paint.png");
    ready = LoadTexture("pic/tutorial/ready.png");
    al = LoadTexture("pic/tutorial/leftarrow.png");
    ar = LoadTexture("pic/tutorial/rightarrow.png");
}

void page::unload(){
    UnloadTexture(CM_1);
    UnloadTexture(CM_2);
    UnloadTexture(CM_3);
    UnloadTexture(bg_CM);
    UnloadTexture(MM_1);
    UnloadTexture(MM_2);
    UnloadTexture(bg_MM);
    UnloadTexture(PP_1);
    UnloadTexture(PP_2);
    UnloadTexture(PP_3);
    UnloadTexture(bg_PP);
    UnloadTexture(OB_1);
    UnloadTexture(OB_2);
    UnloadTexture(bg_OB);
    UnloadTexture(PC_1);
    UnloadTexture(PC_2);
    UnloadTexture(PC_3);
    UnloadTexture(bg_PC);
    UnloadTexture(ready);
    UnloadTexture(al);
    UnloadTexture(ar);
}

void page::drawpage_CM(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(CM_1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(CM_2,0,0,WHITE);
        break;
    case 2:
        DrawTexture(CM_3,0,0,WHITE);
        break;

    default :
        DrawTexture(CM_1,0,0,WHITE);
    }
}

void page::drawpage_MM(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(MM_1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(MM_2,0,0,WHITE);
        break;
    default :
        DrawTexture(MM_1,0,0,WHITE);
    }
}

void page::drawpage_PP(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(PP_1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(PP_2,0,0,WHITE);
        break;
    case 2:
        DrawTexture(PP_3,0,0,WHITE);
        break;

    default :
        DrawTexture(PP_1,0,0,WHITE);
    }
}

void page::drawpage_OB(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(OB_1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(OB_2,0,0,WHITE);
        break;
    default :
        DrawTexture(OB_1,0,0,WHITE);
    }
}

void page::drawpage_PC(int direction) const {
    
    switch (direction){
    case 0:
        DrawTexture(PC_1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(PC_2,0,0,WHITE);
        break;
    case 2:
        DrawTexture(PC_3,0,0,WHITE);
        break;

    default :
        DrawTexture(PC_1,0,0,WHITE);
    }
}

void page::drawarrow() {
 
    timer += GetFrameTime();
        if (timer >= swapInterval) {
            showFirstImage = !showFirstImage; // สลับภาพ
            timer = 0.0f;
        }
    
    if (showFirstImage) {
        DrawTextureEx(al, (Vector2){30, 390}, 0.0f, 1.4f, WHITE);
        DrawTextureEx(ar, (Vector2){1030, 390}, 0.0f, 1.4f, WHITE);
        DrawRectangle(45, 400, 107, 53, transparent);
        DrawRectangle(1045, 400, 107, 53, transparent);
        } else {
        DrawTextureEx(al, (Vector2){10, 380}, 0.0f, 1.8f, WHITE);
        DrawTextureEx(ar, (Vector2){1010, 380}, 0.0f, 1.8f, WHITE);
        DrawRectangle(30, 390, 138, 68, transparent);
        DrawRectangle(1030, 390, 138, 68, transparent);
        }
}

void page::drawbg_CM(){
    DrawTexture(bg_CM,0,0,WHITE);
}

void page::drawbg_MM(){
    DrawTexture(bg_MM,0,0,WHITE);
}

void page::drawbg_PC(){
    DrawTexture(bg_PC,0,0,WHITE);
}

void page::drawbg_PP(){
    DrawTexture(bg_PP,0,0,WHITE);
}

void page::drawbg_OB(){
    DrawTexture(bg_OB,0,0,WHITE);
}

void page::drawready(float X,float Y){
    DrawTextureEx(ready,{X,Y},0,0.5,WHITE);
}

void showtutorial_CM(bool& Ready){
    page tutorial;
    int page = 0;
    while(!WindowShouldClose()){
        tutorial.mousePos = GetMousePosition();
        BeginDrawing();

            tutorial.drawbg_CM();
            tutorial.drawpage_CM(page);
            tutorial.drawarrow();

            if(tutorial.showFirstImage){
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft))){
                    page--;
                    if(page < 0) page = 2;
                }
            }else{
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright_up))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft_up))){
                    page--;
                    if(page < 0) page = 2;
                }
            }

            if(IsKeyPressed(KEY_ENTER)) tutorial.P1press = true;
            if(IsKeyPressed(KEY_SPACE)) tutorial.P2press = true;
                
            if(tutorial.P2press) tutorial.drawready(10,565);
            if(tutorial.P1press) tutorial.drawready(1006,575);

            if (tutorial.P1press && tutorial.P2press) {
                if (tutorial.waittime < 0)
                 {
                    tutorial.waittime = GetTime();
                } else if (GetTime() - tutorial.waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
    
}
void showtutorial_MM(bool& Ready){
    page tutorial;
    int page = 0;
    while(!WindowShouldClose()){
        tutorial.mousePos = GetMousePosition();
        BeginDrawing();

            tutorial.drawbg_MM();
            tutorial.drawpage_MM(page);
            tutorial.drawarrow();

            if(tutorial.showFirstImage){
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft))){
                    page--;
                    if(page < 0) page = 2;
                }
            }else{
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright_up))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft_up))){
                    page--;
                    if(page < 0) page = 2;
                }
            }

            if(IsKeyPressed(KEY_ENTER)) tutorial.P1press = true;
            if(IsKeyPressed(KEY_SPACE)) tutorial.P2press = true;
                
            if(tutorial.P2press) tutorial.drawready(10,565);
            if(tutorial.P1press) tutorial.drawready(1006,575);

            if (tutorial.P1press && tutorial.P2press) {
                if (tutorial.waittime < 0) {
                    tutorial.waittime = GetTime();
                } else if (GetTime() - tutorial.waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
}

void showtutorial_PP(bool& Ready){
    page tutorial;
    int page = 0;
    while(!WindowShouldClose()){
        tutorial.mousePos = GetMousePosition();
        BeginDrawing();

            tutorial.drawbg_PP();
            tutorial.drawpage_PP(page);
            tutorial.drawarrow();

            if(tutorial.showFirstImage){
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft))){
                    page--;
                    if(page < 0) page = 2;
                }
            }else{
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright_up))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft_up))){
                    page--;
                    if(page < 0) page = 2;
                }
            }

            if(IsKeyPressed(KEY_ENTER)) tutorial.P1press = true;
            if(IsKeyPressed(KEY_SPACE)) tutorial.P2press = true;
                
            if(tutorial.P2press) tutorial.drawready(10,565);
            if(tutorial.P1press) tutorial.drawready(1006,575);

            if (tutorial.P1press && tutorial.P2press) {
                if (tutorial.waittime < 0) {
                    tutorial.waittime = GetTime();
                } else if (GetTime() - tutorial.waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
}
void showtutorial_OB(bool& Ready){
    page tutorial;
    int page = 0;
    while(!WindowShouldClose()){
        tutorial.mousePos = GetMousePosition();
        BeginDrawing();

            tutorial.drawbg_OB();
            tutorial.drawpage_OB(page);
            tutorial.drawarrow();

            if(tutorial.showFirstImage){
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft))){
                    page--;
                    if(page < 0) page = 2;
                }
            }else{
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright_up))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft_up))){
                    page--;
                    if(page < 0) page = 2;
                }
            }

            if(IsKeyPressed(KEY_ENTER)) tutorial.P1press = true;
            if(IsKeyPressed(KEY_SPACE)) tutorial.P2press = true;
                
            if(tutorial.P2press) tutorial.drawready(10,565);
            if(tutorial.P1press) tutorial.drawready(1006,575);

            if (tutorial.P1press && tutorial.P2press) {
                if (tutorial.waittime < 0) {
                    tutorial.waittime = GetTime();
                } else if (GetTime() - tutorial.waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
}
void showtutorial_PC(bool& Ready){
    page tutorial;
    int page = 0;
    while(!WindowShouldClose()){
        tutorial.mousePos = GetMousePosition();
        BeginDrawing();

            tutorial.drawbg_PC();
            tutorial.drawpage_PC(page);
            tutorial.drawarrow();

            if(tutorial.showFirstImage){
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft))){
                    page--;
                    if(page < 0) page = 2;
                }
            }else{
                if(IsKeyPressed(KEY_RIGHT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTright_up))){
                    page++;
                    if(page > 2) page = 0;
                }
                if(IsKeyPressed(KEY_LEFT) || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(tutorial.mousePos, tutorial.BTleft_up))){
                    page--;
                    if(page < 0) page = 2;
                }
            }

            if(IsKeyPressed(KEY_ENTER)) tutorial.P1press = true;
            if(IsKeyPressed(KEY_SPACE)) tutorial.P2press = true;
                
            if(tutorial.P2press) tutorial.drawready(10,565);
            if(tutorial.P1press) tutorial.drawready(1006,575);

            if (tutorial.P1press && tutorial.P2press) {
                if (tutorial.waittime < 0) {
                    tutorial.waittime = GetTime();
                } else if (GetTime() - tutorial.waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
}

