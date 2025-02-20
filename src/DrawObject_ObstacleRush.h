#ifndef OBJECT_H
#define OBJECT_H
#include <raylib.h>

class DRAW {
private:
    Texture2D car1;
    Texture2D car2;
    Texture2D tree;
    Texture2D background;
    
public:
    DRAW();
    ~DRAW();
    void load();
    void unload();
    void drawBackground(Rectangle backRec,float scale) const;
    void drawCar(int carNumber, Rectangle carRec, float rotation, float scale) const;
    void drawObject(int carObject, Rectangle objectRec, float rotation, float scale) const;
    void drawLine(Rectangle lineRec[], float scale) const;
    void drawObstacle(Rectangle ObstacleRec,float rotation,float scale) const;
};

DRAW::DRAW() {
    load();
}

DRAW::~DRAW() {
    unload();
}

void DRAW::load()
{
    car1 = LoadTexture("graphics/Car_1.png");
    car2 = LoadTexture("graphics/Car_2.png");
    tree = LoadTexture("graphics/Tree2.png");
    background = LoadTexture("graphics/background1.png");
}

void DRAW::unload() 
{
    UnloadTexture(car1);
    UnloadTexture(car2);
    UnloadTexture(background);
}

void DRAW::drawCar(int carNumber, Rectangle carRec, float rotation, float scale) const
{
    Texture2D carTexture;
    if (carNumber == 1) {
        carTexture = car1;
    } else {
        carTexture = car2;
    } if (carTexture.id == 0) return;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)carTexture.width, (float)carTexture.height };
    Rectangle destRec = { carRec.x, carRec.y, carTexture.width * scale, carTexture.height * scale };
    Vector2 origin = { (carTexture.width * scale) / 2, (carTexture.height * scale) / 2 };
    DrawTexturePro(carTexture, sourceRec, destRec, origin, rotation, WHITE);
}

void DRAW::drawBackground(Rectangle backRec,float scale) const 
{
    Rectangle sourceRec = { 0.0f, 0.0f, (float)background.width, (float)background.height };
    Rectangle destRec = { 0, 0, background.width * scale, background.height * scale };
    DrawTexturePro(background, sourceRec, destRec, {0,0}, 0, WHITE);
}

#endif
