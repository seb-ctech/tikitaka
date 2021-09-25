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
    OffensivePlayer(glm::vec2 pos, Pitch* pitch, int index);
    void display(SystemUnits* su) override;
    virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* ball);
    void ReceiveBall();
    bool hasBall(){ return ball; };
    int getPassingOptionsAmount();
    float getCohesion();
    bool isUnderPressure();
    
    /** PARAMETER CONTROL **/
    void setPassRange(float delta){ passRange = glm::min(glm::max(5.0f, passRange + delta), 60.0f);};
    void setPressureRange(float delta){pressureRange = glm::min(glm::max(2.0f, pressureRange + delta), 40.0f);};
    void setPassRate(float delta){passRate = glm::min(glm::max(0.0f, passRate + delta * 1.0f / 100.0f), 1.0f);};
    void setFlexibility(float delta){movementFlexibility = glm::min(glm::max(0.0f, movementFlexibility + delta * 1.0f / 100.0f), 1.0f);};
    void setChaosRate(float delta){chaosRate = glm::min(glm::max(0.0f, chaosRate + delta * 1.0f / 100.0f), 1.0f);};
    float getPassRange(){return passRange;};
    float getPassRate(){return passRate;};
    float getPressureRange(){return pressureRange;};
    float getFlexibility(){return movementFlexibility;};
    float getChaosRate(){return chaosRate;};

private:
    virtual void DecideNextPosition();
    virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
    virtual void Action();
    glm::vec2 FormTriangle();
    glm::vec2 FreeFromCover();
    bool isFreeLineOfSight(Player* passReceiver);
    bool isFreeFromCover();
    void BallPassing();
    void PassBallTo(OffensivePlayer* target);
    bool ownsBall = false;

    // DISPLAYING

    void DisplayPlayerPosition(SystemUnits* su);
    void DisplayBallPossession(SystemUnits* su);
    void DisplayCohesion(SystemUnits* su);
    void DisplaySupportWithTriangle(SystemUnits* su);
    void DisplayPassingOptions(SystemUnits* su);
    void DisplayClosestOpponent(SystemUnits* su);

    //** TIKI TAKA PARAMETERS **//
    float pressureRange = 8.0;
    float passRange = 26;
    float passRate = 0.08;
    float movementFlexibility = 0.4;
    float chaosRate = 0.02;
};