#include "offense.h"
#include "shape.h"

//TODO: Replace Randomness -> ofRandom() with Decision Making and Algorithms

OffensivePlayer::OffensivePlayer() : Player(){

}


OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch pitch) : Player(pos, pitch) {

}

void OffensivePlayer::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  OwnTeam = Attackers;
  OpponentTeam = Defenders;
}

void OffensivePlayer::display(SystemUnits su){
  Player::display(su);
  ofFill();
  ofSetColor(220, 100, 50);
  ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size));
  if(ball){
      ofNoFill();
      ofSetColor(220, 200, 80);
      ofSetLineWidth(1);
      ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 1.2);
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
  Player::NewTargetSpace();
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
void OffensivePlayer::Action(){
  if(ball){
    if(ofRandom(0, 1) < 0.008){
      PassBallTo(getClosestMate());
      return;
    }
  }
  Player::Action();
}

OffensivePlayer* OffensivePlayer::getClosestMate(){
    Player* closest = nullptr;
    float shortestDist = 100;
    for (Player* mate : OwnTeam){
        float currentDistance = glm::distance(mate->getPos(), position);
        if (currentDistance < shortestDist && mate != this){
            closest = mate;
            shortestDist = currentDistance;
        }
    }
    return dynamic_cast<OffensivePlayer*>(closest);
}