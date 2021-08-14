#pragma once
#include "player.h"
#include "ofMain.h"

class DefensivePlayer;

class OffensivePlayer : public Player {

public:
    OffensivePlayer();
    OffensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
    virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
    void receiveBall();
    bool hasBall(){ return ball; };

private:
    void passBallTo(OffensivePlayer* target);
    virtual glm::vec2 nextMove();
    OffensivePlayer* getClosestMate();
    bool ball = false;
    
    // Form Triangles
    // Move into free spaces
    // Keep Cohesion


};