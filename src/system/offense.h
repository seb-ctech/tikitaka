#pragma once
#include "player.h"
#include "ofMain.h"

class DefensivePlayer; // Forward Declaration

/* This is the class for an Offensive Player, playing by Tiki-Taka rules.
It will try to distribute evenly in space, forming triangles with its team mates, and do short-passes.
*/

class OffensivePlayer : public Player {

public:
    OffensivePlayer();
    OffensivePlayer(glm::vec2 pos, Pitch pitch);
    void display(SystemUnits su) override;
    virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
    void ReceiveBall();
    bool hasBall(){ return ball; };

private:
    virtual glm::vec2 NextTargetSpace();
    virtual glm::vec2 CourseCorrection(glm::vec2 currentTargetSpace);
    virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
    virtual void Action();
    void PassBallTo(OffensivePlayer* target);
    OffensivePlayer* getClosestMate();
    bool ball = false;
    
    // Form Triangles
    // Move into free spaces
    // Keep Cohesion


};