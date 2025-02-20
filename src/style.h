#pragma once

#include <raylib.h>
#include <iostream>
using namespace std;

class style {
    public:
        void drawTextBox(const char* text, float posX, float posY, int fontSize, Color textColor, Color boxColor, Color borderColor, int borderSize);
        void centerXY(string txt, int fontsize, Color colortxt);
        void centerX(string txt, int fontsize,int txty , Color colortxt);
    
        private:
    int screenWidth = 1200;
    int screenHeight = 800;
};