#include "object.h"

P1::P1(){
    load();
}

P1::~P1(){
    unload();
}

void P1::load(){
    p1 = LoadTexture("pic/P1.png");
    up = LoadTexture("pic/P1up.png");
    down = LoadTexture("pic/P1down.png");
    right = LoadTexture("pic/P1right.png");
    left = LoadTexture("pic/P1left.png");
}

void P1::unload(){
    UnloadTexture(up);
    UnloadTexture(left);
    UnloadTexture(right);
    UnloadTexture(down);
    UnloadTexture(p1);
}

void P1::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = up;
        break;
    case 1:
        texture = down;
        break;
    case 2:
        texture = left;
        break;
    case 3:
        texture = right;
        break;
    default:
        texture = p1;
        break;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void P1::setscale(float scale){
    this->scale = scale;
}

P2::P2(){
    load();
}

P2::~P2(){
    unload();
}

void P2::load(){
    p2 = LoadTexture("pic/P2.png");
    up = LoadTexture("pic/P2up.png");
    down = LoadTexture("pic/P2down.png");
    right = LoadTexture("pic/P2right.png");
    left = LoadTexture("pic/P2left.png");
}

void P2::unload(){
    UnloadTexture(up);
    UnloadTexture(left);
    UnloadTexture(right);
    UnloadTexture(down);
    UnloadTexture(p2);
}

void P2::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = up;
        break;
    case 1:
        texture = down;
        break;
    case 2:
        texture = left;
        break;
    case 3:
        texture = right;
        break;
    default:
        texture = p2;
        break;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void P2::setscale(float scale){
    this->scale = scale;
}

command::command(){
    load();
}

command::~command(){
    unload();
}

void command::load(){
    up = LoadTexture("pic/3.png");
    down = LoadTexture("pic/4.png");
    right = LoadTexture("pic/1.png");
    left = LoadTexture("pic/2.png");
}

void command::unload(){
    UnloadTexture(up);
    UnloadTexture(left);
    UnloadTexture(right);
    UnloadTexture(down);
}

void command::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = up;
        break;
    case 1:
        texture = down;
        break;
    case 2:
        texture = left;
        break;
    case 3:
        texture = right;
        break;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void command::setscale(float scale){
    this->scale = scale;
}

oppositecommand::oppositecommand(){
    load();
}

oppositecommand::~oppositecommand(){
    unload();
}

void oppositecommand::load(){
    up = LoadTexture("pic/7.png");
    down = LoadTexture("pic/8.png");
    right = LoadTexture("pic/5.png");
    left = LoadTexture("pic/6.png");
}

void oppositecommand::unload(){
    UnloadTexture(up);
    UnloadTexture(left);
    UnloadTexture(right);
    UnloadTexture(down);
}

void oppositecommand::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = up;
        break;
    case 1:
        texture = down;
        break;
    case 2:
        texture = left;
        break;
    case 3:
        texture = right;
        break;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void oppositecommand::setscale(float scale){
    this->scale = scale;
}

Commander::Commander(){
    load();
}

Commander::~Commander(){
    unload();
}

void Commander::load(){
    C1 = LoadTexture("pic/C1.png");
    C1attack = LoadTexture("pic/C1Attack.png");
    C2 = LoadTexture("pic/C2.png");
    C2attack = LoadTexture("pic/C2Attack.png");
}

void Commander::unload(){
    UnloadTexture(C1);
    UnloadTexture(C1attack);
    UnloadTexture(C2);
    UnloadTexture(C2attack);
}

void Commander::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = C1;
        break;
    case 1:
        texture = C1attack;
        break;
    case 2:
        texture = C2;
        break;
    case 3:
        texture = C2attack;
        break;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void Commander::setscale(float scale){
    this->scale = scale;
}

check::check(){
    load();
}

check::~check(){
    unload();
}

void check::load(){
    incorrect = LoadTexture("pic/Incorrect.png");
    correct = LoadTexture("pic/correct.png");
    blank = LoadTexture("pic/blank.png");
}

void check::unload(){
    UnloadTexture(incorrect);
    UnloadTexture(correct);
    UnloadTexture(blank);
}

void check::draw(Vector2 position,int direction) const {
    Texture2D texture;
    switch (direction)
    {
    case 0:
        texture = correct;
        break;
    case 1:
        texture = incorrect;
        break;
    default :
        texture = blank;
    }

    DrawTextureEx(texture,position,0.0f,scale,WHITE);
}

void check::setscale(float scale){
    this->scale = scale;
}


result::result(){
    load();
}

result::~result(){
    unload();
}

void result::load(){
    P1win = LoadTexture("pic/P1win.png");
    P2win = LoadTexture("pic/P2win.png");
    Draw = LoadTexture("pic/Draw.png");
}

void result::unload(){
    UnloadTexture(P1win);
    UnloadTexture(P2win);
    UnloadTexture(Draw);
}

void result::draw(int direction) const {
    switch (direction){
    case 0:
        DrawTexture(P1win,0,0,WHITE);
        break;
    case 1:
        DrawTexture(P2win,0,0,WHITE);
        break;
    default :
        DrawTexture(Draw,0,0,WHITE);
    }

}