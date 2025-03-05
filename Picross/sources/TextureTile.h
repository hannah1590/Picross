#pragma once
#include "raylib.h"

class TextureTile
{
public:
    TextureTile() {};
    TextureTile(Image& image);

    Texture2D getTexture() { return texture; }
    Color getColor() { return imageColor; }
    void setColor(Color color) { imageColor = color; }
    float getValue() { return hsv.z; }

    int getFrequency() { return frequency; }
    void addFrequency() { frequency++; }
    
private:
    Texture2D texture;
    Color imageColor;
    Vector3 hsv; // x = hue, s = saturation, v = value
    int frequency;
};