#include "player.h"

Player::Player() : Agent(){
};

Player::Player(glm::vec2 _pos, Pitch _pitch, int _index) : Agent(_pos){
  pitch = _pitch;
  targetSpace = RandomLocation();
  index = _index;
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
  debug << std::to_string(speed * 100) << "/" << std::to_string(speedLimit * 100);
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

void Player::DisplaySpace(SystemUnits su){
  ofSetColor(220, 250, 30);
    std::vector<glm::vec2> positions;
    for(Player* p : OpponentTeam){
      if(!(p->position == position)){
        positions.push_back(p->position);
      }
    }
    // ofFill();
    std::vector<glm::vec2> Boundaries = FootballShape::ScanSpace(position, pitch, positions);
    ofBeginShape();
    for (glm::vec2 point : Boundaries){
      float x = su.getXPosOnScreen(point.x);
      float y = su.getYPosOnScreen(point.y);
      ofDrawRectangle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(1), su.getSizeOnScreen(1));
      ofVertex(x, y);
    }
    ofEndShape();
}

// This is where Players make decisions on every frame.

void Player::Action(){
  if(ofRandom(0, 1) < 0.001){
    NewTargetSpace();
  }
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


// This is where all Movement system merge together into a final acceleration that is used to steer the Player
// He follows the course to a target space, makes MoveAdjustments based on the movement of other players

void Player::NextMove(){
  glm::vec2 move = MoveToTarget();
  move = MoveAdjustments(move);
  move += AvoidOutOfBounds();
  steer(move);
};

// Move to Target allows for Target Corrections and sets the Acceleration
glm::vec2 Player::MoveToTarget(){
  targetSpace = CourseCorrection(targetSpace);
  float distanceFactor = glm::distance(targetSpace, position) / 50;
  return glm::normalize(targetSpace - position) * accFactor * distanceFactor;
};

glm::vec2 Player::CourseCorrection(glm::vec2 oldTarget){
  if(ofRandom(0, 1) > 0.88){
    AdjustWalkingSpeed();
  }
  return oldTarget;
}

void Player::AdjustWalkingSpeed(){
  float distanceFactor = glm::distance(targetSpace, position) / 4;
  float distanceModifier = distanceFactor - 5 * (speed / speedLimit);
  float speedVariation = distanceFactor / 2;
  float randomness = ofRandom(speedVariation * -1, speedVariation);
  speed += (distanceModifier + randomness) * 0.001;
}

void Player::NewTargetSpace(){
  speed = 0.05;
  glm::vec2 next = RandomLocation();
  glm::vec2 cohesion = KeepCohesion();
  targetSpace = (next + cohesion) / 2;
} 

glm::vec2 Player::EvaluateMovement(){
  glm::vec2 evaluatedVelocity = velocity;
  glm::vec2 evaluatedMovement = position + evaluatedVelocity;
  return evaluatedMovement;
}

glm::vec2 Player::MoveAdjustments(glm::vec2 move){
  return move;
}

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
  float tolerance = 0.5;
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
    correction += glm::normalize(difference) * -1.0 * accFactor * minDistance / 4;
  }
  return correction;
};

glm::vec2 Player::RandomLocation(){
  glm::vec2 pitchSize = pitch.getSize();
  glm::vec2 location = glm::vec2(ofRandom(0.0, pitchSize.x), ofRandom(0.0, pitchSize.y));
  return location;
}