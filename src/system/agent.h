#pragma once
#include "ofMain.h"

class Agent {

public:
    Agent();
    void update();
    void display();

private:
    glm::vec2 position;

};