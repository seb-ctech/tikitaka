#pragma once
#include "agent.h"
#include "shape.h"
#include "space.h"
#include "helper_math.h"
#include "ofMain.h"


/* This is a Player class. 
It is an advanced Agent, that also is aware of its team and opponents.
It knows how to keep cohesion and is aware of the match state and the pitch.
The steering behavior is composed of a space targeting system which can be changed mid-course aswell as midcourse corrections based on more general rules.*/

class Ball;
class OffensivePlayer; // Forward Declaration

class Player : public Agent {

public:
  Player();
  Player(glm::vec2 pos, Pitch* pitch, int index);
  virtual void Update(OffensivePlayer* ballcarry);
	virtual void Display(SystemUnits* su);
  virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* ball);
  glm::vec2 EvaluateMovement();
  glm::vec2 getTargetPosition(){ return targetPosition; }
  std::vector<Player*> getAllPlayersInRange(std::vector<Player*> group, float Range);
  std::vector<Player*> getSorroundingPlayers(std::vector<Player*> group);
  Player* getClosestPlayer(std::vector<Player*>);
 
protected:
  virtual void DecideNextPosition();
  virtual void Action();
  void NextMove();
  void AdjustWalkingSpeed();
  glm::vec2 KeepCohesion();
  std::vector<glm::vec2> getOtherPlayersPosition(std::vector<Player*> group);
  std::vector<Player*> getOtherPlayersByPosition(std::vector<glm::vec2> positions);
  Player* getPlayerOnPosition(glm::vec2 position, std::vector<Player*> group, float range = 0.1);
  void DisplaySpace(SystemUnits* su); 
  
  glm::vec2 targetPosition;
  Pitch* pitch;
  std::vector<Player*> AllPlayers;
  std::vector<Player*> OwnTeam;
  std::vector<Player*> OpponentTeam;
  OffensivePlayer* BallCarry;
  float size = 2.0f;
  int index;
  Ball* ball;
  float cohesionFactor = 20.0;
  int interval = 20;

private:
  void StayInBound();
  glm::vec2 MoveToTarget();
  glm::vec2 getRandomPosition();
  std::vector<Player*> RemoveSelfFromGroup(std::vector<Player*> group);
};