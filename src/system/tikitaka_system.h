#pragma once
#include "rules.h"
#include "ofMain.h"
#include "agent.h"
#include "pitch.h"
#include "players.h"
#include "system_conversion.h"

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
    int playerAmount; 
    int nAttacking;
    int nDefending;
    SystemConversion sysconv;
    Agent players[];
    Agent TestPlayer;

};