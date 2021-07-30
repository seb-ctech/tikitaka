#pragma once
#include "ofMain.h"
#include "system_units.h"

class Agent {

public:
    Agent();
    Agent(glm::vec2 pos);
    void update();
    void display(SystemUnits su);

private:
    
    void StartOnRandomPosition();

    glm::vec2 position;
    float size = 10.0f;
};