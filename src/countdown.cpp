#include "countdown.h"
#include <string>
#include <cmath>
#include <iostream>

using namespace std;

Countdown::Countdown(float duration) 
    : countdownTime(duration), finished(false) {}

void Countdown::update(float deltaTime) {
    if (countdownTime > 0) {
        countdownTime -= deltaTime;
        finished = false;
    } else {
        finished = true;
    }
}

bool Countdown::isFinished() const {
    return finished;
}

void Countdown::reset(float duration) {
    countdownTime = duration;
    finished = false;
}

string Countdown::getDisplayText() const{
    if(countdownTime > 0){
        return to_string(static_cast<int>(ceil(countdownTime)));
    }else{
        return "Game start!!";
    }
}