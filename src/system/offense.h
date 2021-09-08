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
    void display(SystemUnits su) override;
    virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
    void ReceiveBall();
    bool hasBall(){ return ball; };
    int getPassingOptionsAmount();
    float getCohesion();
    bool isUnderPressure();
    std::vector<glm::vec2> TrianglePivots();

private:
    virtual void NewTargetSpace();
    virtual void CourseCorrection();
    virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
    virtual void Action();
    bool isFreeLineOfSight(Player* passReceiver);
    void BallPassing();
    void PassBallTo(OffensivePlayer* target);
    bool ball = false;
    std::vector<glm::vec2> NewTrianglePivots();

    // DISPLAYING

    void DisplayPlayerPosition(SystemUnits su);
    void DisplayBallPossession(SystemUnits su);
    void DisplayCohesion(SystemUnits su);
    void DisplayTrianglePivots(SystemUnits su);
    void DisplayPassingOptions(SystemUnits su);
    void DisplayClosestOpponent(SystemUnits su);

    float pressureRange = 10.0;
    float passRange = 50;
    float passFrequency = 0.005;
    float movementAmount = 0.002;
};