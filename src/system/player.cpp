#include "player.h"

Player::Player() : Agent(){
};

Player::Player(glm::vec2 _pos, Pitch* _pitch, int _index) : Agent(_pos){
  pitch = _pitch;
  index = _index;
};

void Player::Update(OffensivePlayer* ballcarry){
  BallCarry = ballcarry;
  Action();
  Agent::Update();
};

// This is where Players make decisions on every frame.

void Player::Action(){
  DecideNextPosition();
  targetPosition = pitch->getClosestInBoundPosition(position, targetPosition);
  NextMove();
}

void Player::Display(SystemUnits* su){
  ofSetColor(220, 220, 230);
  ofFill();
  ofSetColor(30, 35, 35);
  ofFill();
  ofCircle(su->getXPosOnScreen(targetPosition.x), su->getYPosOnScreen(targetPosition.y), su->getSizeOnScreen(1));
  ofNoFill();
  ofSetLineWidth(1);
  ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), 
         su->getXPosOnScreen(targetPosition.x), su->getYPosOnScreen(targetPosition.y));
  glm::vec2 visAcc = position + acceleration * 1000;
  ofSetColor(60, 65, 65);
  ofSetLineWidth(6);
  ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), 
         su->getXPosOnScreen(visAcc.x), su->getYPosOnScreen(visAcc.y));
}

void Player::NextMove(){
  glm::vec2 move = glm::vec2(0,0);
  move = MoveToTarget();
  steer(move);
  StayInBound();
};

void Player::InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* _ball){
  AllPlayers.clear();
  for (Player* p : Attackers) {
    AllPlayers.push_back(p);
  }
  for (Player* p : Defenders) {
    AllPlayers.push_back(p);
  }
  targetPosition = getRandomPosition();
  ball = _ball;
};

glm::vec2 Player::MoveToTarget(){
  float distanceToTarget = glm::distance(targetPosition, position);
  if (distanceToTarget > 0){
    float distanceFactor = glm::distance(targetPosition, position) / 50;
    return glm::normalize(targetPosition - position) * accFactor * distanceFactor;
  }
  return glm::vec2(0,0);
};

void Player::DecideNextPosition(){
  speed = 0.05;
  if(ofRandom(0, 1) < 0.01){
    targetPosition = getRandomPosition();
  } else {
    targetPosition = KeepCohesion();
  }
} 

void Player::AdjustWalkingSpeed(){
  float distanceFactor = glm::distance(targetPosition, position) / 2;
  float distanceModifier = distanceFactor - 5 * (speed / speedLimit);
  float speedVariation = distanceFactor / 2;
  float randomness = ofRandom(speedVariation * -1, speedVariation);
  speed += (distanceModifier + randomness) * 0.001;
}

void Player::DisplaySpace(SystemUnits* su){
  ofSetColor(220, 250, 30, 50);
  ofFill();
  ofBeginShape();
  Space space = pitch->getSpace(position, getOtherPlayersPosition(OpponentTeam));
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

std::vector<Player*> Player::getSorroundingPlayers(std::vector<Player*> group){
  std::vector<glm::vec2> playerPositions = pitch->getSpace(position, getOtherPlayersPosition(group)).getBoundaries();
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

glm::vec2 Player::EvaluateMovement(){
  glm::vec2 evaluatedVelocity = velocity;
  glm::vec2 evaluatedMovement = position + evaluatedVelocity;
  return evaluatedMovement;
}

glm::vec2 Player::KeepCohesion(){
  std::vector<glm::vec2> sorrounding = getOtherPlayersPosition(getSorroundingPlayers(OwnTeam));
  glm::vec2 worstPosition;
  float worstDelta = 0;
  if(sorrounding.size() > 1){
    for (glm::vec2 nextPos : sorrounding){
    float delta = glm::distance(nextPos, position) - cohesionFactor;
      if (glm::abs(delta) > glm::abs(worstDelta)){
        worstDelta = delta;
        worstPosition = nextPos;
      }
    }
    if (worstPosition.x != position.x || worstPosition.y != position.y){
      glm::vec2 direction = glm::normalize(worstPosition - position);
      return position + direction * worstDelta * 0.6;
    }
  }
  return position;
};


void Player::StayInBound(){
  float tolerance = 2.0;
  glm::vec2 size = pitch->getSize();
  if(position.x - tolerance < 0){
    if (velocity.x < 0.0){
       velocity.x *= 0.6;
    }
    acceleration.x = (tolerance - position.x) * accFactor * 10.0;
  }
  if(position.x + tolerance > size.x){
    if(velocity.x > 0.0){
      velocity.x *= 0.6;
    }
    acceleration.x = (size.x - tolerance - position.x) * accFactor;
  }
  if(position.y - tolerance < 0){
    if (velocity.y < 0.0){
      velocity.y *= 0.6;
    }
    acceleration.y = (tolerance - position.y) * accFactor;
  } 
  if(position.y + tolerance > size.y){
    if (velocity.y > 0.0){
      velocity.y *= 0.6;
    }
    acceleration.y = (size.y - tolerance - position.y) * accFactor;
  }
};

glm::vec2 Player::getRandomPosition(){
  return pitch->getRandomPosition();
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