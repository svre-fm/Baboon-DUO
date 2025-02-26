#pragma once

#include <raylib.h>
#include <iostream>
#include "object.h"
#include "style.h"
#include "countdown.h"



// Color definitions
extern Color Green;
extern Color Dark_Green;
extern Color Light_Green;
extern Color Yellow;

// Screen dimensions
extern const int screen_width;
extern const int screen_height;

// Game state variables
extern int P1score;
extern int P2score;
extern bool game_over;
extern bool gamestart;

// Ball class

class banana
{
public:
    float x, y;
    int speed_x, speed_y;
    const float max_speed = 12.0f;
    Texture2D pic;

    banana();
    ~banana();
    void load();
    void unload();
    void drawbanana();
    void Update();
    void ResetBall();
};

// Paddle class (Base class for both Player and CPU paddles)
class Paddle
{
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    float speed;
    Texture2D texture;

    void load(const char* path);
    void unload();
    void Draw();
    virtual void Update();
};

// Player1 paddle class
class Player1Paddle : public Paddle
{
public:
    void Update() override;
    void Updateswap() ;
};

// Player2 paddle class
class Player2Paddle : public Paddle
{
public:
    void Update() override;
    void Updateswap() ;
};

class PowerUp{
public :
    float x,y;
    int type;
    bool active;
    float spawnTime;
    Texture2D texture;

    PowerUp();
    void unload();
    void spawn();
    void draw();
    const char* Getname();

};

void playpingpong();

