#pragma once
#include "player.h"
#include "ofMain.h"

class OffensivePlayer; 

class DefensivePlayer : public Player {

public:
    DefensivePlayer();
    DefensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
    virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);

private:
    virtual glm::vec2 nextMove();
    glm::vec2 moveTowardsBallCarrier();
    // Approach closest opposing Player
    // Move towards ball carrier
    // keep cohesion with team
};