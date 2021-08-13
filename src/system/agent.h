#pragma once
#include "ofMain.h"
#include "system_units.h"
#include "pitch.h"

class Agent {

public:
    Agent();
    Agent(Pitch pitch);
    Agent(glm::vec2 pos, Pitch pitch);
    void update(int i);
    virtual void display(SystemUnits su);
    glm::vec2 getPos(){ return position; };
    glm::vec2 getTargetPos(){ return targetPos; }

protected:
    glm::vec2 acceleration;
    glm::vec2 velocity;
    glm::vec2 position;
    float size = 2.0f;
    virtual glm::vec2 nextMove();
    std::vector<Agent*> getClosestAgents(std::vector<Agent*> otherAgents, float Range);

private:
    
    void init();
    void locomotion();
    void drive();
    void avoidBounds();
    void StartOnRandomPosition(glm::vec2 bounds);
    

    int interval;
    float maxAcc = 0.006;
    float maxSpeed = 0.1;
    glm::vec2 targetPos;
    Pitch pitch;
};

