#include "offense.h"
#include "shape.h"
#include "ball.h"

OffensivePlayer::OffensivePlayer() : Player(){

}


OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch* pitch, int index) : Player(pos, pitch, index) {

}

void OffensivePlayer::InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* ball){
  OwnTeam = Attackers;
  OpponentTeam = Defenders;
  Player::InitMatch(Attackers, Defenders, ball);
}

void OffensivePlayer::display(SystemUnits* su){
  Player::display(su);
  if(ownsBall){
    Player::DisplaySpace(su);
  }
  DisplayPlayerPosition(su);
  if(ownsBall){
    DisplayBallPossession(su);
    if(getPassingOptionsAmount() < 3){
      DisplaySupportWithTriangle(su); 
    }
  }
  DisplayPassingOptions(su);
  DisplayClosestOpponent(su);
}

void OffensivePlayer::DisplayPlayerPosition(SystemUnits* su){
  ofFill();
  ofSetColor(220, 100, 50);
  ofDrawCircle(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), su->getSizeOnScreen(size));
}

void OffensivePlayer::DisplayBallPossession(SystemUnits* su){
  ofNoFill();
  ofSetColor(220, 200, 80);
  ofSetLineWidth(3);
  ofDrawCircle(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), su->getSizeOnScreen(size) * 1.2);
}

void OffensivePlayer::DisplayCohesion(SystemUnits* su){
  std::stringstream debug;
  debug << std::to_string(getCohesion());
  infoFont.drawString(debug.str(), su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y) - 20);
}

void OffensivePlayer::DisplaySupportWithTriangle(SystemUnits* su){
  std::vector<glm::vec2> pivots = SupportWithTriangle();
  for (glm::vec2 pivot : pivots){
    ofFill();
    ofSetColor(30, 220, 50);
    ofDrawCircle(su->getXPosOnScreen(pivot.x), su->getYPosOnScreen(pivot.y), su->getSizeOnScreen(size) * 0.7);
  }
}

void OffensivePlayer::DisplayPassingOptions(SystemUnits* su){
  // std::vector<glm::vec2> sample;
  // sample.push_back(OwnTeam[1]->getPos());
  // sample.push_back(OwnTeam[2]->getPos());
  // std::vector<glm::vec2> pivots = FootballShape::SupportWithTriangle(sample);
  std::vector<Player*> SorroundingMates = getAllPlayersInRange(getSorroundingPlayers(OwnTeam), passRange);
  if(SorroundingMates.size() > 0){
    for(Player* p : SorroundingMates){
      if(isFreeLineOfSight(p)){
        ofNoFill();
        ofSetColor(220, 120, 30);
        ofSetLineWidth(1);
        ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), su->getXPosOnScreen(p->getPos().x), su->getYPosOnScreen(p->getPos().y));
      }
    }
  }
}

void OffensivePlayer::DisplayClosestOpponent(SystemUnits* su){
  Player* closestOpponent = getClosestPlayer(OpponentTeam);
  if(glm::distance(closestOpponent->getPos(), position) < pressureRange){
    ofNoFill();
    ofSetColor(50, 30, 180);
    ofSetLineWidth(1);
    ofDrawLine(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), 
    su->getXPosOnScreen(closestOpponent->getPos().x), su->getYPosOnScreen(closestOpponent->getPos().y)) ;
  }
}

void OffensivePlayer::Action(){
  if(ofGetFrameNum() % interval == 0){
    if(ownsBall){
      BallPassing();
      repositionMode = false;
    }
    repositionMode = true;
    NextMove();
    DecideNextPosition();
  }
}

void OffensivePlayer::ReceiveBall(){
    ownsBall = true;
}

void OffensivePlayer::PassBallTo(OffensivePlayer* target){
    ownsBall = false;
    ball->PassTo(target);
}

void OffensivePlayer::DecideNextPosition(){
  if(ownsBall){
    targetPosition = KeepCohesion();
    targetPosition = FreeFromCover();
  } else {
    if (glm::distance(position, targetPosition) < 4 || ofRandom(0, 1) < movementAmount){
      targetPosition = KeepCohesion();
      targetPosition = FormTriangle();
      targetPosition = FreeFromCover();
    }
  }
}

glm::vec2 OffensivePlayer::FormTriangle(){
  int passoptions = BallCarry->getPassingOptionsAmount();
  if (passoptions < 3 && ofRandom(0, 1) < 0.4) {
    std::vector<glm::vec2> options;
    std::vector<Player*> carryMates = BallCarry->getSorroundingPlayers(OwnTeam);
    Space space = pitch->GetSpace(position, getOtherPlayersPosition(OpponentTeam));
    float spaceSize = space.getArea();
    for (Player* mate : carryMates){
      if ( (mate == this || spaceSize < 100) && !isFreeLineOfSight(BallCarry) ){
        options = SupportWithTriangle();
        glm::vec2 targetPosition = FootballShape::getClosestPositionFromSelection(options, KeepCohesion());
        return pitch->getClosestInBoundPosition(position, targetPosition);
      }
    }
  }
  return targetPosition;
}

glm::vec2 OffensivePlayer::MoveAdjustments(glm::vec2 nextMove){
  if(ownsBall){
    Player* clostestOpponent = getClosestPlayer(OpponentTeam);
    if (glm::distance(clostestOpponent->getPos(), position) < pressureRange){
      glm::vec2 difference = clostestOpponent->getPos() - position;
      if (glm::abs(difference.x) > glm::abs(difference.y)){
        nextMove.x = velocity.x * -1.0 * (1 - glm::abs(difference.x) / pressureRange);
      } else {
        nextMove.y = velocity.y * -1.0 * (1 - glm::abs(difference.y) / pressureRange);
      }
    }
  }
  return nextMove;
}

void OffensivePlayer::BallPassing(){
  if(isUnderPressure() || ofRandom(0, 1) < passFrequency){
    std::vector<Player*> SorroundingMates = getAllPlayersInRange(getSorroundingPlayers(OwnTeam), passRange);
    std::vector<Player*> PlayableMates;
    for (Player* p : SorroundingMates){
      if(isFreeLineOfSight(p)){
        PlayableMates.push_back(p);
      }
    }
    if(PlayableMates.size() > 0){
      std::vector<Player*> FreeMates;
      for (Player* p : PlayableMates){
        if(dynamic_cast<OffensivePlayer*>(p)->isFreeFromCover()){
          FreeMates.push_back(p);
        }
      }
      if (FreeMates.size() > 0){
        PlayableMates = FreeMates;
      }
      OffensivePlayer* ballReceiver = dynamic_cast<OffensivePlayer*>(getClosestPlayer(PlayableMates));
      PassBallTo(ballReceiver);
    }
  }
}

glm::vec2 OffensivePlayer::FreeFromCover(){
  if(!isFreeFromCover()){
    glm::vec2 directionToOpponent = glm::normalize(getClosestPlayer(OpponentTeam)->getPos() - position);
    return position + directionToOpponent * -1.0 * pressureRange;
  }
  return targetPosition;
}

bool OffensivePlayer::isFreeFromCover(){
  glm::vec2 closestOpponentPosition = getClosestPlayer(OpponentTeam)->getPos();
  return glm::distance(closestOpponentPosition, position) >= pressureRange;
}

std::vector<glm::vec2> OffensivePlayer::SupportWithTriangle(){
  float tolerance = 5.0; 
  std::vector<std::vector<glm::vec2>> pairs;
  std::vector<glm::vec2> pivots;
  std::vector<glm::vec2> targetPlayers = getOtherPlayersPosition(BallCarry->getSorroundingPlayers(OwnTeam));
  for(glm::vec2 player : targetPlayers){
    std::vector<glm::vec2> pair;
    pair.push_back(BallCarry->getPos());
    pair.push_back(player);
    pairs.push_back(pair);
  }
  for(std::vector<glm::vec2> pair : pairs){
    std::vector<glm::vec2> localPivots = FootballShape::TrianglePivots(pair);
    for(glm::vec2 pivot : localPivots){
      bool add = true;
      for(glm::vec2 otherPivot : pivots){
        if(glm::distance(otherPivot, pivot) < tolerance){
          add = false;
          break;
        }
        Space space = pitch->GetSpace(pivot, getOtherPlayersPosition(OpponentTeam));
        if(space.getArea() < 80){
          add = false;
          break;
        }
      }
      if(add){
        pivots.push_back(pivot);
      }
    }
  }
  return pivots;
}

bool OffensivePlayer::isFreeLineOfSight(Player* potentialPassReceiver){
  float tolerance = 3;
  float deltaAngle = HelperMath::DegreesToRadians(12);
  glm::vec2 lineToPlayer = potentialPassReceiver->getPos() - position;
  std::vector<glm::vec2> blockingOpponents = FootballShape::RaycastToMany(position, potentialPassReceiver->getPos(), getOtherPlayersPosition(OpponentTeam), tolerance);
  for(glm::vec2 blocker : blockingOpponents){
    glm::vec2 lineToOpponent = blocker - position;
    float angleDifference = glm::abs(HelperMath::CartesianToPolAngle(lineToPlayer)) - glm::abs(HelperMath::CartesianToPolAngle(lineToOpponent));
    float minAngle = deltaAngle * (2 - glm::distance(blocker, position) / glm::distance(potentialPassReceiver->getPos(), position));
    if(glm::abs(angleDifference) < minAngle){
      return false;
    }
  }
  return true;
}

bool OffensivePlayer::isUnderPressure(){
  Player* closestOpponent = getClosestPlayer(OpponentTeam);
  return glm::distance(position, closestOpponent->getPos()) < pressureRange;
}


int OffensivePlayer::getPassingOptionsAmount(){
  std::vector<Player*> sorroundingMates = getSorroundingPlayers(OwnTeam);
  int count = 0;
  for(Player* mate : sorroundingMates){
    if(isFreeLineOfSight(mate)){
      count++;
    }
  }
  return count;
}


float OffensivePlayer::getCohesion(){
  std::vector<Player*> sorroundingMates = getSorroundingPlayers(OwnTeam);
  float distanceSum = 0;
  for(Player* mate : sorroundingMates){
    distanceSum += glm::distance(position, mate->getPos());
  }
  return distanceSum/sorroundingMates.size();
}