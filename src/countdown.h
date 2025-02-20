#pragma once
#include <string>

class Countdown {
public:
    Countdown(float duration);
    void update(float deltaTime);
    bool isFinished() const;
    void reset(float duration);
    std::string getDisplayText() const;

private:
    float countdownTime;
    bool finished;
};