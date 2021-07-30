#pragma once
#include "ofMain.h"
#include "system_units.h"
#include "pitch.h"

class Agent {

public:
    Agent();
    Agent(Pitch pitch);
    Agent(glm::vec2 pos);
    void update();
    void display(SystemUnits su);

private:
    
    void StartOnRandomPosition(glm::vec2 bounds);

    glm::vec2 position;
    float size = 10.0f;
};