#include "countdown.h"
#include <string>
#include <cmath>

Countdown::Countdown(float duration) 
    : countdownTime(duration), finished(false) {}

void Countdown::update(float deltaTime) {
    if (deltaTime <= 0) return; // ตรวจสอบค่า deltaTime
    if (countdownTime > 0) {
        countdownTime = std::max(0.0f, countdownTime - deltaTime); // ป้องกันค่า countdownTime ติดลบ
        finished = (countdownTime <= 0); // อัปเดตสถานะ finished
    } else {
        finished = true;
    }
}

bool Countdown::isFinished() const {
    return finished;
}

void Countdown::reset(float duration) {
    if (duration <= 0) {
        return;
    }
    countdownTime = duration;
    finished = false;
}

std::string Countdown::getDisplayText() const {
    if (countdownTime > 0) {
        return std::to_string(static_cast<int>(std::ceil(countdownTime))); // แสดงเวลาที่เหลือเป็นจำนวนเต็ม
    } else {
        return "Game start!!"; // แสดงข้อความเมื่อนับถอยหลังเสร็จสิ้น
    }
}