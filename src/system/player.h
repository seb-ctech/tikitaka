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

class OffensivePlayer; // Forward Declaration

class Player : public Agent {

public:
  Player();
  Player(glm::vec2 pos, Pitch* pitch, int index);
  virtual void update(OffensivePlayer* ballcarry);
	virtual void display(SystemUnits* su);
  virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);
  glm::vec2 EvaluateMovement();
  Space getTargetSpace(){ return targetSpace; }
  std::vector<Player*> getAllPlayersInRange(std::vector<Player*> group, float Range);
  std::vector<Player*> getSorroundingPlayers(std::vector<Player*> group);
  Player* getClosestPlayer(std::vector<Player*>);
 
protected:
  virtual void NewTargetSpace();
  virtual void CourseCorrection();
  virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
  virtual void Action(); // This is an action a Player can take. The default behavior is a steering move, but he can also pass the Ball.
  void NextMove();
  void AdjustWalkingSpeed();
  glm::vec2 KeepCohesion();
  std::vector<glm::vec2> getOtherPlayersPosition(std::vector<Player*> group);
  std::vector<Player*> getOtherPlayersByPosition(std::vector<glm::vec2> positions);
  Player* getPlayerOnPosition(glm::vec2 position, std::vector<Player*> group, float range = 0.1);
  
  void DisplaySpace(SystemUnits* su); 
  Space targetSpace;
  Pitch* pitch;
  std::vector<Player*> AllPlayers;
  std::vector<Player*> OwnTeam;
  std::vector<Player*> OpponentTeam;
  OffensivePlayer* BallCarry;
  float size = 2.0f;
  int index;

private:
  glm::vec2 AvoidOutOfBounds();
  glm::vec2 MoveToTarget();
  Space RandomSpace();
  std::vector<Player*> RemoveSelfFromGroup(std::vector<Player*> group);
  int interval; // TODO: Move to protected and assign value;
};