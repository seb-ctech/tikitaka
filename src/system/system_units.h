#pragma once 
#include "ofMain.h"

/* System that converts pitch length and width from a normalized value space to screenspace */

class SystemUnits {

public:

    static float getXPosOnScreen(float x);

    static float getSizeOnScreen(float y);

    static float getYPosOnScreen(float s);
    
    static glm::vec2 getPitchSize();

private:

    //TODO: Refactor to glm::vec2
    static constexpr float pitchWidth = 100.0;
    static constexpr float pitchHeight = 100.0;

};