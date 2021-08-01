#pragma once
#include "agent.h"
#include "ofMain.h"

class OffensivePlayer : public Agent {

public:
    OffensivePlayer();
    OffensivePlayer(Pitch pitch);
    OffensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
};

class DefensivePlayer : public Agent {

public:
    DefensivePlayer();
    DefensivePlayer(Pitch pitch);
    DefensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
};