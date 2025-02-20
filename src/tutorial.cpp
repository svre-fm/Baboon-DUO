#include "tutorial_CM.h"

class page{
    public:
        page();
        ~page();
        void load();
        void unload();
        void draw(int direction) const;
        void drawbg();
        void drawready(float X,float Y);

    private:
        Texture2D page1;
        Texture2D page2;
        Texture2D page3;
        Texture2D bg;
        Texture2D ready;
};

page::page(){
    load();
}

page::~page(){
    unload();
}

void page::load(){
    page1 = LoadTexture("pic/1_CM.png");
    page2 = LoadTexture("pic/2_CM.png");
    page3 = LoadTexture("pic/3_CM.png");
    bg = LoadTexture("pic/command.png");
    ready = LoadTexture("pic/ready.png");
}

void page::unload(){
    UnloadTexture(page1);
    UnloadTexture(page2);
    UnloadTexture(page3);
    UnloadTexture(bg);
    UnloadTexture(ready);
}

void page::draw(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(page1,0,0,WHITE);
        break;
    case 1:
        DrawTexture(page2,0,0,WHITE);
        break;
    case 2:
        DrawTexture(page3,0,0,WHITE);
        break;

    default :
        DrawTexture(page1,0,0,WHITE);
    }
}

void page::drawbg(){
    DrawTexture(bg,0,0,WHITE);
}

void page::drawready(float X,float Y){
    DrawTextureEx(ready,{X,Y},0,0.5,WHITE);
}

void showtutorial(bool &Ready){
    page tutorial;
    int page = 0;
    bool P1press = false;
    bool P2press = false;
    double waittime = -1.0;
    while(!WindowShouldClose()){
        BeginDrawing();

            tutorial.drawbg();

            if(IsKeyPressed(KEY_RIGHT)){
                page++;
                if(page > 2) page = 0;
            }
            if(IsKeyPressed(KEY_LEFT)){
                page--;
                if(page < 0) page = 2;
            }

            tutorial.draw(page);

            if(IsKeyPressed(KEY_ENTER)) P1press = true;
            if(IsKeyPressed(KEY_SPACE)) P2press = true;
                
            if(P2press) tutorial.drawready(10,565);
            if(P1press) tutorial.drawready(1006,575);

            if (P1press && P2press) {
                if (waittime < 0) {
                    waittime = GetTime();
                } else if (GetTime() - waittime >= 1.5) {
                    Ready = true;
                    break;
                }
            }
    
        EndDrawing();
    }
}


