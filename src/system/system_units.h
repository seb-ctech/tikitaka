#pragma once 
#include "ofMain.h"

/* System that converts pitch length and width from a normalized value space to screenspace */

class SystemUnits {

public:
    SystemUnits();
    SystemUnits(glm::vec2 _size);
    float getXPosOnScreen(float x);
    float getSizeOnScreen(float y);
    float getYPosOnScreen(float s);

private:
    glm::vec2 pitchSize;
};