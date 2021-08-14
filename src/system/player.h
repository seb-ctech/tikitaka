#pragma once
#include "agent.h"
#include "shape.h"
#include "ofMain.h"

// This is a Player class. 
// It is an advanced Agent, that also is aware of its team and opponents.
// Knows how to keep cohesion and is aware of the match state and the pitch.

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
  virtual glm::vec2 nextMove();
  glm::vec2 getTargetPos(){ return targetPos; }
  std::vector<Player*> getAllPlayersInRange(Team side, float Range);
  std::vector<Player*> getClosestPlayersInArea(Team side);
  glm::vec2 keepCohesion();

  glm::vec2 targetPos;
  std::vector<Player*> AllPlayers;
  std::vector<Player*> OwnTeam;
  std::vector<Player*> OpponentTeam;
  Player* BallCarry;
  float size = 2.0f;

private:
  void AvoidOutOfBounds();
  void MoveToTarget();
  glm::vec2 RandomLocation();
  Pitch pitch;
  int interval;

};