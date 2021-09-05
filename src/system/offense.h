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
    OffensivePlayer(glm::vec2 pos, Pitch pitch, int index);
    void display(SystemUnits su) override;
    virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
    void ReceiveBall();
    bool hasBall(){ return ball; };

private:
    virtual void NewTargetSpace();
    virtual glm::vec2 CourseCorrection(glm::vec2 currentTargetSpace);
    virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
    virtual void Action();
    void BallPassing();
    void PassBallTo(OffensivePlayer* target);
    bool ball = false;
    bool UnderPressure();
    
    // Form Triangles
    // Move into free spaces
    // Keep Cohesion


};