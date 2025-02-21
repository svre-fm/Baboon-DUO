#pragma once

#ifndef PINGPONG_H
#define PINGPONG_H

// Color definitions
extern Color Green;
extern Color Dark_Green;
extern Color Light_Green;
extern Color Yellow;

// Screen dimensions
extern const int screen_width;
extern const int screen_height;

// Game state variables
extern int player_score;
extern int cpu_score;
extern bool game_over; // Flag to check if the game is over


// Ball class

class banana{
    public:
        float x, y;
        int speed_x, speed_y;
        Texture2D pic ;

        banana();
        ~banana();
        void load();
        void unload();
        void drawbanana();
        void Update();
        void ResetBall();
};

// Paddle class (Base class for both Player and CPU paddles)
class Paddle {
protected:
    void LimitMovement();

public:
    float x, y;
    float width, height;
    int speed;

    void Draw();
    virtual void Update();
};

// Player1 paddle class
class Player1Paddle : public Paddle {
public:
    void Update() override;
};

// Player2 paddle class
class Player2Paddle : public Paddle {
public:
    void Update() override;
};

// Function to play the pingpong game
void playpingpong();

#endif // PINGPONG_H

