#pragma once
#include "agent.h"
#include "ofMain.h"

// Forward Declaration
class DefensivePlayer;
class OffensivePlayer; 

class OffensivePlayer : public Agent {

public:
    OffensivePlayer();
    OffensivePlayer(Pitch pitch);
    OffensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
    void updateGame(std::vector<OffensivePlayer*> team, std::vector<DefensivePlayer*> opponents, OffensivePlayer* ballowner);
    void getBall();
    bool hasBall(){ return ball; };

private:
    void passBall(OffensivePlayer* target);
    virtual glm::vec2 nextMove();
    glm::vec2 keepCohesion();
    OffensivePlayer* getClosestMate();
    std::vector<OffensivePlayer*> team;
    std::vector<DefensivePlayer*> opponents;
    OffensivePlayer* ballowner;
    bool ball = false;
    
    // Form Triangles
    // Move into free spaces
    // Keep Cohesion


};

class DefensivePlayer : public Agent {

public:
    DefensivePlayer();
    DefensivePlayer(Pitch pitch);
    DefensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
    void updateGame(std::vector<OffensivePlayer*> opponents, std::vector<DefensivePlayer*> team, OffensivePlayer* ballowner);

private:
    virtual glm::vec2 nextMove();
    std::vector<OffensivePlayer*> opponents;
    std::vector<DefensivePlayer*> team;
    OffensivePlayer* ballowner;
    glm::vec2 moveTowardsBallCarrier();
    // Approach closest opposing Player
    // Move towards ball carrier
    // keep cohesion with team
};