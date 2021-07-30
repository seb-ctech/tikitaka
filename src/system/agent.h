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
    virtual void display(SystemUnits su);

protected:
    glm::vec2 position;
    float size = 2.0f;

private:
    
    void StartOnRandomPosition(glm::vec2 bounds);
};