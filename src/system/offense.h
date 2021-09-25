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
    std::vector<glm::vec2> SupportWithTriangle();

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
#
    float pressureRange = 8.0;
    float passRange = 34;
    float passFrequency = 0.01;
    float movementAmount = 0.002;
};