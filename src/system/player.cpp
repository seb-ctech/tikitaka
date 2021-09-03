#include "player.h"

// TODO: Implement and Test with different Adjustment Ratios, both for Offensive and Defensive.

Player::Player() : Agent(){
};

Player::Player(glm::vec2 _pos, Pitch _pitch) : Agent(_pos){
  pitch = _pitch;
  targetSpace = RandomLocation();
};

void Player::update(Player* ballcarry){
  BallCarry = ballcarry;
  Action();
  Agent::update();
};

void Player::Action(){
  NextMove();
}

void Player::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  AllPlayers.clear();
  for (Player* p : Attackers) {
    AllPlayers.push_back(p);
  }
  for (Player* p : Defenders) {
    AllPlayers.push_back(p);
  }
};

std::vector<Player*> Player::getClosestPlayersInArea(Team team){
  std::vector<Player*> SorroundingPlayers;
  std::vector<Player*> SamplePlayers;
  switch (team) {
    case ALL: SamplePlayers = AllPlayers;
    case OWN: SamplePlayers = OwnTeam;
    case OPP: SamplePlayers = OpponentTeam;
  }
  return SorroundingPlayers;
};

std::vector<Player*> Player::getAllPlayersInRange(Team team, float Range){
  std::vector<Player*> closestPlayers;
  std::vector<Player*> SamplePlayers;
  switch (team) {
    case ALL: SamplePlayers = AllPlayers;
    case OWN: SamplePlayers = OwnTeam;
    case OPP: SamplePlayers = OpponentTeam;
  }
  for (Player* a : SamplePlayers){
      float distance = glm::distance(position, a->position);
      if (distance <= Range){
          closestPlayers.push_back(a);
      }
  }
  return closestPlayers;
};

glm::vec2 Player::EvaluateMovement(glm::vec2 move, int steps = 1){
  glm::vec2 evaluatedAcceleration = move;
  glm::vec2 evaluatedVelocity = velocity + evaluatedAcceleration;
  glm::vec2 evaluatedMovement = position + evaluatedVelocity * steps;
  return evaluatedMovement;
}

glm::vec2 Player::MoveAdjustments(glm::vec2 move){
  return move;
}

// This is were a players makes decisions on every frame;
// He follows the course to a target space, makes MoveAdjustments based on the movement of other player
void Player::NextMove(){
  glm::vec2 move = MoveToTarget();
  move += KeepCohesion() * 0.4;
  move = MoveAdjustments(move);
  move = AvoidOutOfBounds(move);
  steer(move);
};

glm::vec2 Player::CourseCorrection(glm::vec2 oldTarget){
  if(ofRandom(0, 1) > 0.88){
    return NextTargetSpace();
  }
  return oldTarget;
}

glm::vec2 Player::NextTargetSpace(){
  return RandomLocation();
}

glm::vec2 Player::MoveToTarget(){
  if(glm::length((targetSpace - position)) <= 2.0){     
    targetSpace = NextTargetSpace();
    float speedVariation = 0.02;
    maxSpeed = 0.06 + ofRandom(speedVariation * -1, speedVariation);
  }
  glm::vec2 finalTargetSpace = CourseCorrection(targetSpace);
  return glm::normalize(finalTargetSpace - position) * accFactor;
};

glm::vec2 Player::KeepCohesion(){
  std::vector<Player*> closeTeamMates = getAllPlayersInRange(OWN, 40.0);
  std::vector<glm::vec2> positions;
  for(Player* p : closeTeamMates){
    positions.push_back(p->getPos());
  }
  glm::vec2 center = FootballShape::center(position, positions);
  return glm::normalize(center - position) * accFactor;
};

glm::vec2 Player::AvoidOutOfBounds(glm::vec2 move){
    glm::vec2 nextPos = EvaluateMovement(move);
    glm::vec2 pitchSize = pitch.getSize();
    if (nextPos.x >= pitchSize.x
     || nextPos.x <= 0){
       move.x *= -1.0;
     }
    if (nextPos.y >= pitchSize.y 
     || nextPos.y <= 0){
      move.y *= -1.0;
    }
    return move;
};

glm::vec2 Player::RandomLocation(){
  glm::vec2 pitchSize = pitch.getSize();
  glm::vec2 location = glm::vec2(ofRandom(0.0, pitchSize.x), ofRandom(0.0, pitchSize.y));
  return location;
}