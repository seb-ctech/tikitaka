#include "system_units.h"

SystemUnits::SystemUnits(){
    
}

SystemUnits::SystemUnits(glm::vec2 _size){
    pitchSize = _size;
}

float SystemUnits::getXPosOnScreen(float x){

    float xpos = x / pitchSize.x * ofGetWindowWidth();
    return xpos;
}

float SystemUnits::getYPosOnScreen(float y){
     
    float ypos = y / pitchSize.y * ofGetWindowHeight();
    return ypos;
}

float SystemUnits::getSizeOnScreen(float s){
    float psize = pitchSize.x * pitchSize.y;
    float ssize = ofGetWindowWidth() * ofGetWindowHeight();
    float relativeSize = s / psize * ssize;
    return relativeSize;
}