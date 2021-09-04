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

void Player::display(SystemUnits su){
  ofSetColor(220, 220, 230);
  ofFill();
  std::stringstream debug;
  debug << std::to_string(glm::length(maxSpeed));
  infoFont.drawString(debug.str(), su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y) - 20);
  ofSetColor(30, 35, 35);
  ofFill();
  ofCircle(su.getXPosOnScreen(targetSpace.x), su.getYPosOnScreen(targetSpace.y), su.getSizeOnScreen(1));
  ofNoFill();
  ofSetLineWidth(1);
  ofDrawLine(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), 
         su.getXPosOnScreen(targetSpace.x), su.getYPosOnScreen(targetSpace.y));
  glm::vec2 visAcc = position + acceleration * 1000;
  ofSetColor(60, 65, 65);
  ofSetLineWidth(6);
  ofDrawLine(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), 
         su.getXPosOnScreen(visAcc.x), su.getYPosOnScreen(visAcc.y));
}

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

glm::vec2 Player::EvaluateMovement(){
  glm::vec2 evaluatedVelocity = velocity;
  glm::vec2 evaluatedMovement = position + evaluatedVelocity;
  return evaluatedMovement;
}

glm::vec2 Player::MoveAdjustments(glm::vec2 move){
  return move;
}

// This is were a players makes decisions on every frame;
// He follows the course to a target space, makes MoveAdjustments based on the movement of other player

void Player::NextMove(){
  glm::vec2 move = MoveToTarget();
  move = MoveAdjustments(move);
  move += AvoidOutOfBounds();
  steer(move);
};

glm::vec2 Player::CourseCorrection(glm::vec2 oldTarget){
  if(ofRandom(0, 1) > 0.88){
    return NextTargetSpace();
  }
  return oldTarget;
}

glm::vec2 Player::NextTargetSpace(){
  glm::vec2 next = RandomLocation();
  glm::vec2 cohesion = KeepCohesion();
  return ((next + cohesion) / 2 + next) / 2;
}

glm::vec2 Player::MoveToTarget(){
  if(glm::length((targetSpace - position)) <= 2.0){  
    targetSpace = NextTargetSpace();
    float speedVariation = 2;
    maxSpeed = (speedVariation + ofRandom(speedVariation * -1, speedVariation) + (glm::distance(targetSpace, position) / 4)) * 0.01;
  }
  glm::vec2 finalTargetSpace = CourseCorrection(targetSpace);
  float completionModifier = 1 - glm::distance(finalTargetSpace, position) / 100 + 0.01;
  return glm::normalize(finalTargetSpace - position) * accFactor * completionModifier;
};

glm::vec2 Player::KeepCohesion(){
  std::vector<Player*> closeTeamMates = getAllPlayersInRange(OWN, 40.0);
  std::vector<glm::vec2> positions;
  for(Player* p : closeTeamMates){
    positions.push_back(p->getPos());
  }
  if (positions.size() <= 1){
    return glm::vec2(0,0);
  }
  glm::vec2 center = position;
  for (glm::vec2 p : positions){
    center += p;
  }
  center = center / (positions.size());
  return center;
};

glm::vec2 Player::AvoidOutOfBounds(){
  float tolerance = 2.0;
  glm::vec2 nextPosition = EvaluateMovement();
  glm::vec2 bounds = pitch.getSize();
  glm::vec2 correction(0,0);
  // TODO: Think about moving this to the Pitch object, with a tolerance;
  float dToRightBounds = glm::distance(nextPosition, glm::vec2(bounds.x, position.y));
  float dToTopBounds = glm::distance(nextPosition, glm::vec2(position.x, bounds.y)); 
  float dToLeftBounds = glm::distance(nextPosition, glm::vec2(0, position.y)); 
  float dToBottomBounds = glm::distance(nextPosition, glm::vec2(position.x, 0)); 
  if (dToRightBounds <= tolerance 
    || dToTopBounds <= tolerance
    || dToLeftBounds <= tolerance 
    || dToBottomBounds <= tolerance){
    float minDistance = bounds.x;
    if (dToRightBounds < minDistance){
      minDistance = dToRightBounds;
    }
    if (dToLeftBounds < minDistance){
      minDistance = dToLeftBounds;
    }
    if (dToTopBounds < minDistance){
      minDistance = dToTopBounds;
    }
    if (dToBottomBounds < minDistance){
      minDistance = dToBottomBounds;
    }
    glm::vec2 difference = nextPosition - position;
    correction += glm::normalize(difference) * -1.0 * accFactor * minDistance;
  }
  return correction;
};

glm::vec2 Player::RandomLocation(){
  glm::vec2 pitchSize = pitch.getSize();
  glm::vec2 location = glm::vec2(ofRandom(0.0, pitchSize.x), ofRandom(0.0, pitchSize.y));
  return location;
}