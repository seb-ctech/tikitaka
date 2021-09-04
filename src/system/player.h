#pragma once
#include "agent.h"
#include "shape.h"
#include "ofMain.h"

/* This is a Player class. 
It is an advanced Agent, that also is aware of its team and opponents.
It knows how to keep cohesion and is aware of the match state and the pitch.
The steering behavior is composed of a space targeting system which can be changed mid-course aswell as midcourse corrections based on more general rules.*/

enum Team {
  ALL,
  OPP,
  OWN
};

class Player : public Agent {

public:
  Player();
  Player(glm::vec2 pos, Pitch pitch);
  virtual void update(Player* ballcarry);
	virtual void display(SystemUnits su);
  virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
 
protected:
  virtual void NewTargetSpace();
  virtual glm::vec2 CourseCorrection(glm::vec2 currentTargetSpace);
  virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
  virtual void Action(); // This is an action a Player can take. The default behavior is a steering move, but he can also pass the Ball.
  void NextMove();
  void AdjustWalkingSpeed();
  glm::vec2 EvaluateMovement();
  glm::vec2 KeepCohesion();
  glm::vec2 getTargetSpace(){ return targetSpace; }
  std::vector<Player*> getAllPlayersInRange(Team side, float Range);
  std::vector<Player*> getClosestPlayersInArea(Team side);

  glm::vec2 targetSpace;
  std::vector<Player*> AllPlayers;
  std::vector<Player*> OwnTeam;
  std::vector<Player*> OpponentTeam;
  Player* BallCarry;
  float size = 2.0f;

private:
  glm::vec2 AvoidOutOfBounds();
  glm::vec2 MoveToTarget();
  glm::vec2 RandomLocation();
  Pitch pitch;
  int interval;

};