#ifndef OBJECT_H
#define OBJECT_H

#include <raylib.h>

class Car {
private:
    Texture2D car1;
    Texture2D car2;
    Texture2D object1;
    Texture2D object2;
    Texture2D object3;
    Texture2D object4;
    Texture2D obtacle;
    Texture2D startline1;
    Texture2D finishline2;
    Texture2D grass_background;
    
public:
    Car();
    ~Car();
    void load();
    void unload();
    void drawBackground(Rectangle backRec, float scale) const;
    void drawCar(int carNumber, Rectangle carRec, float rotation, float scale) const;
    void drawObject(int carObject, Rectangle objectRec, float rotation, float scale) const;
    void drawLine(Rectangle lineRec[], float scale) const;
    void drawObstacle(Rectangle ObstacleRec,float rotation,float scale) const;
};

#endif
