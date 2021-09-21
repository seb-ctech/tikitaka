#pragma once

#include "ofMain.h"
#include "player.h"
#include "pitch.h"
#include "offense.h"
#include "defense.h"
#include "system_units.h"
#include "shape.h"
#include <vector>

struct Positions {
    std::vector<glm::vec2> attacking;
    std::vector<glm::vec2> defending;
    glm::vec2 ballcarry;
};

class Tikitaka {

public:
    Tikitaka();
    void display();
    void update();
    void init();
    Positions getPlayerPositions();


private:

    std::vector<glm::vec2> positions_4_3_3(Side s, float, float);
    OffensivePlayer* getPlayerInPossession();

    glm::vec2 pitchSize; 
    int playerAmount; 
    int nAttacking;
    int nDefending;
    Pitch* pitch;
    SystemUnits* units;
    std::vector<OffensivePlayer*> attackers;
    std::vector<DefensivePlayer*> defenders;
    std::vector<Player*> players;
};