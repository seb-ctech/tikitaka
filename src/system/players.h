#pragma once
#include "agent.h"
#include "ofMain.h"

class OffensivePlayer : public Agent {

public:
    OffensivePlayer();
    OffensivePlayer(Pitch pitch);

};

class DefensivePlayer : public Agent {

public:
    DefensivePlayer();
    DefensivePlayer(Pitch pitch);
};