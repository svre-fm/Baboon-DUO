#include "countdown.h"
#include <string>
using namespace std;

Countdown::Countdown(float duration) 
    : countdownTime(duration), finished(false) {}

void Countdown::update(float deltaTime) {
    if (countdownTime > 0) {
        countdownTime -= deltaTime;
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
        return to_string(static_cast<int>(countdownTime));
    }else{
        return "Game start!!";
    }
}
