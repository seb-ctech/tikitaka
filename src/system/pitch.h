#pragma once
#include "ofMain.h"

class Pitch {

    public: 

    Pitch();
    Pitch(float x, float y);

    glm::vec2 getSize(){
        return size;
    }

    private:

    glm::vec2 size;
};