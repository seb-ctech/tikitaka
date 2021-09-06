#include "offense.h"
#include "shape.h"

//TODO: Replace Randomness -> ofRandom() with Decision Making and Algorithms

OffensivePlayer::OffensivePlayer() : Player(){

}


OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch pitch, int index) : Player(pos, pitch, index) {

}

void OffensivePlayer::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  OwnTeam = Attackers;
  OpponentTeam = Defenders;
  Player::setMatch(Attackers, Defenders);
}

//TODO: Refactor Displayed info in separate Methods
void OffensivePlayer::display(SystemUnits su){
  Player::display(su);
  ofFill();
  ofSetColor(220, 100, 50);
  ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size));
  if(ball){
      ofNoFill();
      ofSetColor(220, 200, 80);
      ofSetLineWidth(3);
      ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 1.2);
      //Player::DisplaySpace(su);
      // Passing options
  }
  if(index == 3){
    // std::vector<glm::vec2> sample;
    // sample.push_back(OwnTeam[1]->getPos());
    // sample.push_back(OwnTeam[2]->getPos());
    // std::vector<glm::vec2> pivots = FootballShape::TrianglePivots(sample);
    std::vector<glm::vec2> pivots = TrianglePivots();
    for (glm::vec2 pivot : pivots){
      ofFill();
      ofSetColor(30, 220, 50);
      ofDrawCircle(su.getXPosOnScreen(pivot.x), su.getYPosOnScreen(pivot.y), su.getSizeOnScreen(size) * 0.7);
    }
  }
  std::vector<Player*> SorroundingMates = getAllPlayersInRange(getSorroundingPlayers(OwnTeam), passRange);
  if(SorroundingMates.size() > 0){
    for(Player* p : SorroundingMates){
      if(isFreeLineOfSight(p)){
        ofNoFill();
        ofSetColor(220, 120, 30);
        ofSetLineWidth(1);
        ofDrawLine(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getXPosOnScreen(p->getPos().x), su.getYPosOnScreen(p->getPos().y));
      }
    }
  }
  // Show closest opponent
  Player* closestOpponent = getClosestPlayer(OpponentTeam);
  if(glm::distance(closestOpponent->getPos(), position) < pressureRange){
    ofNoFill();
    ofSetColor(50, 30, 180);
    ofSetLineWidth(1);
    ofDrawLine(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), 
    su.getXPosOnScreen(closestOpponent->getPos().x), su.getYPosOnScreen(closestOpponent->getPos().y)) ;
  }
}

void OffensivePlayer::Action(){
  if(ball){
    BallPassing();
  }
  NextMove();
  if(ofRandom(0,1) < 0.0004){
    NewTargetSpace();
  }
}

void OffensivePlayer::ReceiveBall(){
    ball = true;
}

void OffensivePlayer::PassBallTo(OffensivePlayer* target){
    ball = false;
    target->ReceiveBall();
}


// TODO: Implement the main Space seeking Rules, Triangles, Passing options for mates, etc...
void OffensivePlayer::NewTargetSpace(){
  std::vector<glm::vec2> pivots = TrianglePivots();
  if(pivots.size() > 0){
    int amount = pivots.size() - 1;
    int random = glm::floor(ofRandom(0, amount));
    glm::vec2 newPosition = pivots[random];
    targetSpace = (KeepCohesion() + newPosition) / 2;
  }
}

// TODO: Reevaluate spaces and retarget new Space
glm::vec2 OffensivePlayer::CourseCorrection(glm::vec2 currentTargetSpace){
  return Player::CourseCorrection(currentTargetSpace);
}

//TODO: Implement spacing, avoid running into defender, Adjustments to position in space
glm::vec2 OffensivePlayer::MoveAdjustments(glm::vec2 nextMove){
  return nextMove;
}

//TODO: Implement passing behavior based on line of sight.
// Ray Cast to closest team mates -> check for obstruction and target pos.


//TODO: Integrate line of sight rule
// Raycast to Opponents and Mate, measure the deltaAngle and determine, if it is big enough.
void OffensivePlayer::BallPassing(){
  if(UnderPressure() || ofRandom(0, 1) < passFrequency){
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
      if(!ballReceiver->UnderPressure()){
        PassBallTo(ballReceiver);
      }
    }
  }
}

std::vector<glm::vec2> OffensivePlayer::TrianglePivots(){
  std::vector<std::vector<glm::vec2>> pairs;
  std::vector<glm::vec2> pivots;
  float tolerance = 10;
  FootballShape::Pairs(getOtherPlayersPosition(getAllPlayersInRange(OwnTeam, 60)), pairs);
  for(std::vector<glm::vec2> pair : pairs){
    std::vector<glm::vec2> localPivots = FootballShape::TrianglePivots(pair);
    glm::vec2 pitchSize = pitch.getSize();
    for(glm::vec2 pivot : localPivots){
      bool add = true;
      for(glm::vec2 otherPivot : pivots){
        if(glm::distance(otherPivot, pivot) < tolerance){
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

bool OffensivePlayer::UnderPressure(){
  Player* closestOpponent = getClosestPlayer(OpponentTeam);
  return glm::distance(position, closestOpponent->getPos()) < pressureRange;
}