#include "player.h"

Player::Player() : Agent(){
};

Player::Player(glm::vec2 _pos, Pitch* _pitch, int _index) : Agent(_pos){
  pitch = _pitch;
  index = _index;
};

void Player::update(OffensivePlayer* ballcarry){
  BallCarry = ballcarry;
  Action();
  Agent::update();
};

void Player::display(SystemUnits* su){
  ofSetColor(220, 220, 230);
  ofFill();
  ofSetColor(30, 35, 35);
  ofFill();
  ofCircle(su->getXPosOnScreen(targetSpace.getCenter().x), su->getYPosOnScreen(targetSpace.getCenter().y), su->getSizeOnScreen(1));
  ofNoFill();
  ofSetLineWidth(1);
  ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), 
         su->getXPosOnScreen(targetSpace.getCenter().x), su->getYPosOnScreen(targetSpace.getCenter().y));
  glm::vec2 visAcc = position + acceleration * 1000;
  ofSetColor(60, 65, 65);
  ofSetLineWidth(6);
  ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), 
         su->getXPosOnScreen(visAcc.x), su->getYPosOnScreen(visAcc.y));
}

void Player::DisplaySpace(SystemUnits* su){
  ofSetColor(220, 250, 30, 50);
  ofFill();
  ofBeginShape();
  Space space = pitch->GetSpace(position, getOtherPlayersPosition(OpponentTeam));
  for (glm::vec2 point : space.getBoundaries()){
    float x = su->getXPosOnScreen(point.x);
    float y = su->getYPosOnScreen(point.y);
    ofDrawRectangle(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), su->getSizeOnScreen(1), su->getSizeOnScreen(1));
    ofVertex(x, y);
  }
  ofEndShape();
  std::stringstream debug;
  debug << std::to_string(space.getArea());
  glm::vec2 c = space.getCenter();
  infoFont.drawString(debug.str(), su->getXPosOnScreen(c.x), su->getYPosOnScreen(c.y) - 20);
}

std::vector<glm::vec2> Player::getOtherPlayersPosition(std::vector<Player*> group){
  std::vector<glm::vec2> positions;
  for(Player* p : RemoveSelfFromGroup(group)){
    if(!(p->getPos() == position)){
      positions.push_back(p->getPos());
    }
  }
  return positions;
}

std::vector<Player*> Player::getOtherPlayersByPosition(std::vector<glm::vec2> positions){
  std::vector<Player*> players;
  for (glm::vec2 p : positions){
    Player* player = getPlayerOnPosition(p, AllPlayers);
    if(!(player == nullptr)){
      players.push_back(player);
    }
  }
  return players;
}

Player* Player::getPlayerOnPosition(glm::vec2 position, std::vector<Player*> group, float range){
  for(Player* p : group){
    if(glm::distance(p->getPos(), position) <= range){
      return p;
    }
  }
  return nullptr;
}

// This is where Players make decisions on every frame.

void Player::Action(){
  if(ofRandom(0, 1) < 0.0002){
    NewTargetSpace();
  }
  NextMove();
}

void Player::InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* _ball){
  AllPlayers.clear();
  for (Player* p : Attackers) {
    AllPlayers.push_back(p);
  }
  for (Player* p : Defenders) {
    AllPlayers.push_back(p);
  }
  targetSpace = RandomSpace();
  ball = _ball;
};

std::vector<Player*> Player::getSorroundingPlayers(std::vector<Player*> group){
  std::vector<glm::vec2> playerPositions = pitch->GetSpace(position, getOtherPlayersPosition(group)).getBoundaries();
  return getOtherPlayersByPosition(playerPositions);
};

std::vector<Player*> Player::getAllPlayersInRange(std::vector<Player*> group, float Range){
  std::vector<Player*> newGroup = RemoveSelfFromGroup(group);
  std::vector<Player*> playersInRange;
  for (Player* a : newGroup){
    float distance = glm::distance(position, a->getPos());
    if (distance <= Range){
      playersInRange.push_back(a);
    }
  }
  return playersInRange;
};

Player* Player::getClosestPlayer(std::vector<Player*> group){
  std::vector<Player*> newGroup = RemoveSelfFromGroup(group);
  Player* closest = newGroup[glm::floor(ofRandom(0, newGroup.size()))];
  for(int i = 0; i < newGroup.size(); i++){
    if(glm::distance(position, newGroup[i]->getPos()) < glm::distance(position, closest->getPos())){
      closest = newGroup[i];
    }
  }
  return closest;
}

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
  CourseCorrection();
  float distanceFactor = glm::distance(targetSpace.getCenter(), position) / 50;
  return glm::normalize(targetSpace.getCenter() - position) * accFactor * distanceFactor;
};

void Player::CourseCorrection(){
  if(ofRandom(0, 1) > 0.88){
    AdjustWalkingSpeed();
  }
}

void Player::AdjustWalkingSpeed(){
  float distanceFactor = glm::distance(targetSpace.getCenter(), position) / 4;
  float distanceModifier = distanceFactor - 5 * (speed / speedLimit);
  float speedVariation = distanceFactor / 2;
  float randomness = ofRandom(speedVariation * -1, speedVariation);
  speed += (distanceModifier + randomness) * 0.001;
}

void Player::NewTargetSpace(){
  speed = 0.05;
  Space next = RandomSpace();
  glm::vec2 cohesion = KeepCohesion();
  glm::vec2 mean = (next.getCenter() + cohesion) / 2;
  targetSpace = pitch->GetSpace((next.getCenter() + mean) / 2, getOtherPlayersPosition(OpponentTeam));
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
  std::vector<Player*> closeTeamMates = getAllPlayersInRange(OwnTeam, 40.0);
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


//FIXME: Sometimes Players go out of bounds forever!
glm::vec2 Player::AvoidOutOfBounds(){
  float tolerance = 0.5;
  glm::vec2 nextPosition = EvaluateMovement();
  glm::vec2 correction(0,0);
  float minDistance = pitch->closestDistanceToBounds(position, nextPosition);
  if (minDistance <= tolerance){
    glm::vec2 difference = nextPosition - position;
    correction += glm::normalize(difference) * -1.0 * accFactor * minDistance / 4;
  }
  return correction;
};

Space Player::RandomSpace(){
  glm::vec2 pitchSize = pitch->getSize();
  glm::vec2 location = glm::vec2(ofRandom(0.0, pitchSize.x), ofRandom(0.0, pitchSize.y));
  return pitch->GetSpace(location, getOtherPlayersPosition(OpponentTeam));
}

std::vector<Player*> Player::RemoveSelfFromGroup(std::vector<Player*> group){
  std::vector<Player*> newGroup;
  for(Player* p : group){
    if(!(p == this)){
      newGroup.push_back(p);
    }
  }
  return newGroup;
}