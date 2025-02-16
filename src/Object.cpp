#include "Object.h"
#include <iostream>

// Constructor: โหลดภาพตอนสร้าง object
Car::Car() {
    load();
}

// Destructor: เคลียร์หน่วยความจำตอน object ถูกทำลาย
Car::~Car() {
    unload();
}

// โหลดไฟล์ภาพรถ
void Car::load() {
    car1 = LoadTexture("graphics/Car_1.png");
    car2 = LoadTexture("graphics/Car_2.png");

    if (car1.id == 0 || car2.id == 0) {
        std::cerr << "Error: Failed to load car textures!" << std::endl;
    }
}

// เคลียร์หน่วยความจำ
void Car::unload() {
    UnloadTexture(car1);
    UnloadTexture(car2);
}

// วาดภาพรถ โดยเลือก car1 หรือ car2
void Car::draw(int carNumber, Rectangle carRec, float rotation, float scale) const {
    const Texture2D& carTexture = (carNumber == 1) ? car1 : car2;

    if (carTexture.id == 0) return;

    Rectangle sourceRec = { 0.0f, 0.0f, (float)carTexture.width, (float)carTexture.height };
    Rectangle destRec = { carRec.x, carRec.y, carTexture.width * scale, carTexture.height * scale };
    Vector2 origin = { (carTexture.width * scale) / 2, (carTexture.height * scale) / 2 };

    DrawTexturePro(carTexture, sourceRec, destRec, origin, rotation, WHITE);
}
