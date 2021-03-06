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

void OffensivePlayer::Action(){
  if(ofGetFrameNum() % interval == 0){
    if(ownsBall){
      BallPassing();
    }
    Player::Action();
  }
}

void OffensivePlayer::Display(SystemUnits* su){
  Player::Display(su);
  DisplayPlayerPosition(su);
  if(ownsBall){
    DisplayBallPossession(su); 
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
  glm::vec2 pivot = FormTriangle();
  ofSetColor(160, 220, 50);
  ofNoFill();
  ofSetLineWidth(2);
  ofDrawCircle(su->getXPosOnScreen(pivot.x), su->getYPosOnScreen(pivot.y), su->getSizeOnScreen(size) * 0.7);
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

void OffensivePlayer::ReceiveBall(){
    ownsBall = true;
}

void OffensivePlayer::PassBallTo(OffensivePlayer* target){
    ownsBall = false;
    ball->PassTo(target);
}

void OffensivePlayer::DecideNextPosition(){
  if (glm::distance(position, targetPosition) < 5 || ofRandom(0, 1) < movementFlexibility){ 
    if(ofRandom(0, 1) < triangleRate){
      targetPosition = FormTriangle();
    } else {
      targetPosition = KeepCohesion();
    }
    targetPosition = SupportBallCarry();
    targetPosition = FreeFromCover();
    AdjustWalkingSpeed();
  }
}

void OffensivePlayer::BallPassing(){
  if(isUnderPressure() || ofRandom(0, 1) < passRate){
    std::vector<Player*> SorroundingMates = getAllPlayersInRange(getSorroundingPlayers(OwnTeam), passRange);
    std::vector<Player*> PlayableMates;
    for (Player* p : SorroundingMates){
      if(isFreeLineOfSight(p)){
        PlayableMates.push_back(p);
      }
    }
    if(PlayableMates.size() > 0){
      OffensivePlayer* ballReceiver;
      std::vector<Player*> FreeMates;
      for (Player* p : PlayableMates){
        if(dynamic_cast<OffensivePlayer*>(p)->isFreeFromCover()){
          FreeMates.push_back(p);
        }
      }
      if (FreeMates.size() > 0){
        float mostSpace = 0.0;
        Player* mostFreeMate = FreeMates[0];
        for (Player* p : FreeMates){
          float distance = glm::distance(p->getPos(), p->getClosestPlayer(OpponentTeam)->getPos());
          if (distance > mostSpace){
            mostFreeMate = p;
            mostSpace = distance;
          }
        }
        ballReceiver = dynamic_cast<OffensivePlayer*>(mostFreeMate);
        PassBallTo(ballReceiver);
      } 
    }
  }
}

glm::vec2 OffensivePlayer::FreeFromCover(){
  if(!isFreeFromCover()){
    Space space = pitch->getSpace(position, getOtherPlayersPosition(OpponentTeam));
    if(space.getArea() < 80){
      return FormTriangle();
    }
    glm::vec2 directionToOpponent = glm::normalize(getClosestPlayer(OpponentTeam)->getPos() - position);
    return position + directionToOpponent * -1.0 * pressureRange / 5;
  }
  return targetPosition;
}

bool OffensivePlayer::isFreeFromCover(){
  glm::vec2 closestOpponentPosition = getClosestPlayer(OpponentTeam)->getPos();
  return glm::distance(closestOpponentPosition, position) >= pressureRange / 2.0;
}

glm::vec2 OffensivePlayer::FormTriangle(){
  float tolerance = 10.0; 
  std::vector<std::vector<glm::vec2>> pairs;
  std::vector<glm::vec2> pivots;

  // Make Pairs of Possible Link Up Players, that are nearby
  std::vector<Player*> targetPlayers = getSorroundingPlayers(OwnTeam);
  for(Player* player : targetPlayers){
    std::vector<Player*> otherPlayers = player->getSorroundingPlayers(OwnTeam);
    for(Player* other : otherPlayers){
      if(other != this){
        std::vector<glm::vec2> pair;
        pair.push_back(player->getPos());
        pair.push_back(other->getPos());
        pairs.push_back(pair);
      }
    }
  }
  
  // Get possible Triangle Pivots for every pair, 
  // that do not overlap with existing team mates or other pivots
  for(std::vector<glm::vec2> pair : pairs){
    std::vector<glm::vec2> localPivots = FootballShape::TrianglePivots(pair);
    for(glm::vec2 pivot : localPivots){
      bool add = true;
      for(glm::vec2 otherPivot : pivots){
        if(glm::distance(otherPivot, pivot) < tolerance){
          add = false;
          break;
        }
        std::vector<glm::vec2> matePositions = getOtherPlayersPosition(OwnTeam);
        for (glm::vec2 matePosition : matePositions){
          if(glm::distance(pivot, matePosition) < tolerance){
            add = false;
            break;
          }
        } 
      }
      if(add){
        pivots.push_back(pivot);
      }
    }
  }
  // Return the optimal pivot to keep cohesion
  return FootballShape::getClosestPositionFromSelection(pivots, KeepCohesion());
}

glm::vec2 OffensivePlayer::SupportBallCarry(){
  glm::vec2 adjustedPosition = targetPosition;
  std::vector<Player*> sorroundingPlayers = getSorroundingPlayers(OwnTeam);
  for(Player* player : sorroundingPlayers){
    if(player == BallCarry){
      glm::vec2 carryPosition = BallCarry->getPos();
      if(!isFreeLineOfSight(BallCarry)){
        glm::vec2 offset = targetPosition - position;
        adjustedPosition = HelperMath::PolarToCartesian(HelperMath::CartesianToPolRadius(offset), HelperMath::CartesianToPolAngle(offset) + ofRandom(-0.1, 0.1));
      }
      if (glm::distance(carryPosition, targetPosition) > passRange){
        glm::vec2 offset = carryPosition - adjustedPosition;
        adjustedPosition = targetPosition + glm::normalize(offset) * glm::distance(carryPosition, adjustedPosition) - passRange;
      }
    }
  }
  return adjustedPosition;
}

bool OffensivePlayer::isFreeLineOfSight(Player* potentialPassReceiver){
  float tolerance = 2;
  float deltaAngle = HelperMath::DegreesToRadians(15);
  glm::vec2 lineToPlayer = potentialPassReceiver->getPos() - position;
  std::vector<glm::vec2> blockingOpponents = FootballShape::RaycastToMany(position, potentialPassReceiver->getPos(), getOtherPlayersPosition(OpponentTeam), tolerance);
  for(glm::vec2 blocker : blockingOpponents){
    glm::vec2 lineToOpponent = blocker - position;
    float angleDifference = glm::abs(HelperMath::CartesianToPolAngle(lineToPlayer)) - glm::abs(HelperMath::CartesianToPolAngle(lineToOpponent));
    float minAngle = deltaAngle * (2 - glm::distance(blocker, position) / glm::distance(potentialPassReceiver->getPos(), position));
    if(glm::abs(angleDifference) < minAngle / (glm::distance(blocker, position) / 10.0) ){
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