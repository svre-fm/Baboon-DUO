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
// วาดภาพรถ โดยเลือก car1 หรือ car2

// โหลดไฟล์ภาพรถ
void Car::load() {
    grass_background = LoadTexture("graphics/grass_background.png");
    object1 = LoadTexture("graphics/Bush_01.png");
    object2 = LoadTexture("graphics/Bush_02.png");
    object3 = LoadTexture("graphics/Tree_03.png");
    object4 = LoadTexture("graphics/Tree_04.png");

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
    UnloadTexture(object1);
    UnloadTexture(object2);
    UnloadTexture(object3);
    UnloadTexture(object4);
    UnloadTexture(grass_background);

}

void Car::drawCar(int carNumber, Rectangle carRec, float rotation, float scale) const {
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

void Car::drawBackground(Rectangle backRec,float scale) const {
    Rectangle sourceRec = { 0.0f, 0.0f, (float)grass_background.width, (float)grass_background.height };
    Rectangle destRec = { backRec.x, backRec.y, grass_background.width * scale, grass_background.height * scale };

    DrawTexturePro(grass_background, sourceRec, destRec, {0,0}, 0, WHITE);
}

void Car::drawObject(int objectNum, Rectangle objectRec, float rotation, float scale) const{
    Texture2D ObjectTexture;
    switch (objectNum)
    {
    case 1:
        ObjectTexture = object1; 
        break;
    case 2:
        ObjectTexture = object2; 
        break;
    case 3:
        ObjectTexture = object3; 
        break;
    case 4:
        ObjectTexture = object4; 
        break;
    }
    Rectangle sourceRec = { 0.0f, 0.0f, (float)ObjectTexture.width, (float)ObjectTexture.height };
    Rectangle destRec = { objectRec.x, objectRec.y, ObjectTexture.width * scale, ObjectTexture.height * scale };
    Vector2 origin = { (ObjectTexture.width * scale) / 2, (ObjectTexture.height * scale) / 2 };

    DrawTexturePro(ObjectTexture, sourceRec, destRec, origin, rotation, WHITE);
}