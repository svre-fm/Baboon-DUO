#include "style.h"

style::style(){
    load();
}

style::~style(){
    unload();
}

void style::load(){
    fontA = LoadFont("Font/LoveYaLikeASister-Regular.ttf");
    fontB = LoadFont("Font/SourGummy-VariableFont_wdth,wght.ttf");
}

void style::unload(){
    UnloadFont(fontA);
    UnloadFont(fontB);
}

void style::drawTextBox(const char* text, float posX, float posY, int fontSize, Color textColor, Color boxColor, Color borderColor, int borderSize) {
    
    int textWidth = MeasureText(text, fontSize);
    int boxX = posX - 10; 
    int boxY = posY - 10; 
    int boxWidth = textWidth + 20; 
    int boxHeight = fontSize + 20; 
    DrawRectangle(boxX - borderSize, boxY - borderSize, boxWidth + 2 * borderSize, boxHeight + 2 * borderSize, borderColor);
    DrawRectangle(boxX, boxY, boxWidth, boxHeight, boxColor);
    DrawText(text,posX,posY,fontSize,textColor);
}

void style::centerXY(string txt, int fontsize, Color colortxt) {
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth) / 2;
    int txtY = (screenHeight - fontsize) / 2;
    DrawText(txt.c_str(), txtX, txtY, fontsize, colortxt);
}

void style::centerX(string txt, int fontsize,int txty , Color colortxt) {
    int textwidth = MeasureText(txt.c_str(), fontsize);
    int txtX = (screenWidth - textwidth) / 2;
    DrawText(txt.c_str(), txtX, txty, fontsize, colortxt);
}