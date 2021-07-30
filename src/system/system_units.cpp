#include "system_units.h"

float SystemUnits::getXPosOnScreen(float x){

    float xpos = x / pitchWidth * ofGetWindowWidth();
    return xpos;
}

float SystemUnits::getYPosOnScreen(float y){
     
    float ypos = y / pitchHeight * ofGetWindowHeight();
    return ypos;
}

float SystemUnits::getSizeOnScreen(float s){
    float psize = pitchWidth * pitchHeight;
    float ssize = ofGetWindowWidth() * ofGetWindowHeight();
    float relativeSize = s / psize * ssize;
    return relativeSize;
}

glm::vec2 SystemUnits::getPitchSize(){
    return glm::vec2(pitchWidth, pitchHeight);
}