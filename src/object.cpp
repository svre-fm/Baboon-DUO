#include "object.h"

P1::P1(){
    load();
}

P1::~P1(){
    unload();
}

void P1::load(){
    p1 = LoadTexture("pic/command/P1.png");
    up = LoadTexture("pic/command/P1up.png");
    down = LoadTexture("pic/command/P1down.png");
    right = LoadTexture("pic/command/P1right.png");
    left = LoadTexture("pic/command/P1left.png");
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
    p2 = LoadTexture("pic/command/P2.png");
    up = LoadTexture("pic/command/P2up.png");
    down = LoadTexture("pic/command/P2down.png");
    right = LoadTexture("pic/command/P2right.png");
    left = LoadTexture("pic/command/P2left.png");
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
    up = LoadTexture("pic/command/3.png");
    down = LoadTexture("pic/command/4.png");
    right = LoadTexture("pic/command/1.png");
    left = LoadTexture("pic/command/2.png");
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
    up = LoadTexture("pic/command/7.png");
    down = LoadTexture("pic/command/8.png");
    right = LoadTexture("pic/command/5.png");
    left = LoadTexture("pic/command/6.png");
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
    C1 = LoadTexture("pic/command/C1.png");
    C1attack = LoadTexture("pic/command/C1Attack.png");
    C2 = LoadTexture("pic/command/C2.png");
    C2attack = LoadTexture("pic/command/C2Attack.png");
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
    incorrect = LoadTexture("pic/command/Incorrect.png");
    correct = LoadTexture("pic/command/correct.png");
    blank = LoadTexture("pic/command/blank.png");
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
    P1win = LoadTexture("pic/result/P1win.png");
    P2win = LoadTexture("pic/result/P2win.png");
    Draw = LoadTexture("pic/result/Draw.png");
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

texture::texture(){
    load();
}

texture::~texture(){
    unload();
}

void texture::load(){
    bg = LoadTexture("pic/command/bggame.png");
    P1 = LoadTexture("pic/command/markP1.png");
    P2 = LoadTexture("pic/command/markP2.png");
}

void texture::unload(){
    UnloadTexture(bg);
    UnloadTexture(P1);
    UnloadTexture(P2);
}

void texture::drawbg(float x, float y){
    DrawTexture(bg,x,y,WHITE);
}

void texture::drawP1(float x, float y){
    DrawTexture(P1,x,y,WHITE);
}

void texture::drawP2(float x, float y){
    DrawTexture(P2,x,y,WHITE);
}
