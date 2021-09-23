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
  //DisplayCohesion(su);
  if(ownsBall){
    DisplayBallPossession(su);
    DisplayTrianglePivots(su); 
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

void OffensivePlayer::DisplayTrianglePivots(SystemUnits* su){
  std::vector<glm::vec2> pivots = TrianglePivots();
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
  // std::vector<glm::vec2> pivots = FootballShape::TrianglePivots(sample);
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
    }
    NextMove();
    if(glm::distance(targetSpace.getCenter(), position) < 4){
      NewTargetSpace();
    }
  }
}

void OffensivePlayer::ReceiveBall(){
    ownsBall = true;
}

void OffensivePlayer::PassBallTo(OffensivePlayer* target){
    ownsBall = false;
    ball->PassTo(target);
}

void OffensivePlayer::NewTargetSpace(){
  std::vector<glm::vec2> options;
  Space space = pitch->GetSpace(position, getOtherPlayersPosition(OpponentTeam));
  float spaceSize = space.getArea();
  int mateOptions = BallCarry->getPassingOptionsAmount();
  float cohesion = getCohesion();
  if (mateOptions < 3){
    options = BallCarry->TrianglePivots();
  } else if (spaceSize < 20 || cohesion > 50) {
    options = NewTrianglePivots();
  }
  
  if(options.size() > 0){
    glm::vec2 closestOption = options[0];
    for (glm::vec2 option : options){
      if(glm::distance(option, position) < glm::distance(closestOption, position)){
        closestOption = option;
      }
    }
    glm::vec2 randomOption = options[glm::floor(ofRandom(0, options.size()))];
    targetSpace = pitch->GetSpace(randomOption, getOtherPlayersPosition(OpponentTeam));
  }
}

void OffensivePlayer::CourseCorrection(){
  float distance = glm::distance(targetSpace.getCenter(), getClosestPlayer(AllPlayers)->getPos());
  if (distance < 5){
    AdjustWalkingSpeed();
  }
}

glm::vec2 OffensivePlayer::MoveAdjustments(glm::vec2 nextMove){
  if(ownsBall){
    Player* clostestOpponent = getClosestPlayer(OpponentTeam);
    float distance = glm::distance(position, clostestOpponent->getPos());
    if (distance < pressureRange){
      float delta = 1 - distance / pressureRange;
      return glm::normalize(clostestOpponent->getPos() - position) * -1  * delta;
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
      Player* freeMate = PlayableMates[0];
      for(Player* p : PlayableMates){
        Player* closestOpponent = p->getClosestPlayer(OpponentTeam);
        Player* currentClosest = freeMate->getClosestPlayer(OpponentTeam);
        float distance = glm::distance(closestOpponent->getPos(), p->getPos());
        float currentDistance = glm::distance(currentClosest->getPos(), freeMate->getPos());
        if(distance > currentDistance){
          freeMate = p;
        }
      }
      OffensivePlayer* ballReceiver = dynamic_cast<OffensivePlayer*>(freeMate);
      if(!ballReceiver->isUnderPressure()){
        PassBallTo(ballReceiver);
      }
    }
  }
}

std::vector<glm::vec2> OffensivePlayer::TrianglePivots(){
  std::vector<std::vector<glm::vec2>> pairs;
  std::vector<glm::vec2> pivots;
  float tolerance = 10;
  std::vector<glm::vec2> sorroundingMates = getOtherPlayersPosition(getSorroundingPlayers(OwnTeam));
  for(glm::vec2 otherMate : sorroundingMates){
    std::vector<glm::vec2> pair;
    pair.push_back(position);
    pair.push_back(otherMate);
    pairs.push_back(pair);
  }
  for(std::vector<glm::vec2> pair : pairs){
    std::vector<glm::vec2> localPivots = FootballShape::TrianglePivots(pair);
    glm::vec2 pitchSize = pitch->getSize();
    for(glm::vec2 pivot : localPivots){
      bool add = true;
      for(glm::vec2 otherPivot : pivots){
        if(glm::distance(otherPivot, pivot) < tolerance){
          add = false;
          break;
        }
        Space space = pitch->GetSpace(pivot, getOtherPlayersPosition(OpponentTeam));
        if(space.getArea() < 10){
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

std::vector<glm::vec2> OffensivePlayer::NewTrianglePivots(){
  std::vector<std::vector<glm::vec2>> pairs;
  std::vector<glm::vec2> pivots;
  float tolerance = 10;
  FootballShape::Pairs(getOtherPlayersPosition(getSorroundingPlayers(OwnTeam)), pairs);
  for(std::vector<glm::vec2> pair : pairs){
    std::vector<glm::vec2> localPivots = FootballShape::TrianglePivots(pair);
    glm::vec2 pitchSize = pitch->getSize();
    for(glm::vec2 pivot : localPivots){
      bool add = true;
      for(glm::vec2 otherPivot : pivots){
        if(glm::distance(otherPivot, pivot) < tolerance){
          add = false;
          break;
        }
        Space space = pitch->GetSpace(pivot, getOtherPlayersPosition(OpponentTeam));
        if(space.getArea() < 10){
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
  float tolerance = 5;
  float deltaAngle = HelperMath::DegreesToRadians(10);
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