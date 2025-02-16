#ifndef OBJECT_H
#define OBJECT_H

#include <raylib.h>

class Car {
private:
    Texture2D car1;
    Texture2D car2;

public:
    Car();
    ~Car();
    void load();
    void unload();
    void draw(int carNumber, Rectangle carRec, float rotation, float scale) const;
};

#endif
