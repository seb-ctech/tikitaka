#pragma once

#include "ofMain.h"
#include "player.h"
#include "pitch.h"
#include "ball.h"
#include "offense.h"
#include "defense.h"
#include "system_units.h"
#include "shape.h"
#include "parameter.h"
#include <vector>

struct Positions {
    std::vector<glm::vec2> attacking;
    std::vector<glm::vec2> defending;
    glm::vec2 ball;
};

class Tikitaka {

public:
    Tikitaka();
    void display();
    void update();
    void init();
    int getPlayerAmountAtt(){return nAttacking;};
    int getPlayerAmountDef(){return nDefending;};
    Positions getPositions();
    Parameter* getParameter(){return parameter;};
    
private:

    std::vector<glm::vec2> positions_4_3_3(Side s, float, float);
    OffensivePlayer* getPlayerInPossession();
    glm::vec2 pitchSize;
    int playerAmount; 
    int nAttacking;
    int nDefending;
    Pitch* pitch;
    SystemUnits* units;
    Ball* ball;
    Parameter* parameter;
    std::vector<OffensivePlayer*> attackers;
    std::vector<DefensivePlayer*> defenders;
    std::vector<Player*> players;
};