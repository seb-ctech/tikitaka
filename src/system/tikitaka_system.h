#pragma once

#include "ofMain.h"
#include "agent.h"
#include "pitch.h"
#include "players.h"
#include "system_units.h"
#include <vector>

struct Players {
    glm::vec2* attacking;
    glm::vec2* defending;
    glm::vec2 playerWithBall;
};

class Tikitaka {

public:
    Tikitaka();
    void display();
    void update();
    void init();
    Players getPlayerPositions();


private:
    glm::vec2 pitchSize; 
    int playerAmount; 
    int nAttacking;
    int nDefending;
    Pitch pitch;
    SystemUnits units;
    std::vector<Agent*> players;
    Agent TestPlayer;
};