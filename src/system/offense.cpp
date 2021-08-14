#include "offense.h"
#include "shape.h"

OffensivePlayer::OffensivePlayer() : Player(){

}


OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch pitch) : Player(pos, pitch) {

}

void OffensivePlayer::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  OwnTeam = Attackers;
  OpponentTeam = Defenders;
}

void OffensivePlayer::display(SystemUnits su){
    ofFill();
    ofSetColor(220, 100, 50);
    ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size));
    if(ball){
        ofNoFill();
        ofSetColor(220, 200, 80);
        ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 1.2);
    }
}

void OffensivePlayer::receiveBall(){
    ball = true;
}

void OffensivePlayer::passBallTo(OffensivePlayer* target){
    ball = false;
    target->receiveBall();
}

//TODO: Implement passing behavior based on line of sight.
// Ray Cast to closest team mates, check for abstruction and target pos.
glm::vec2 OffensivePlayer::nextMove(){

    if (ofRandom(0, 1) < 0.04){
        return Player::nextMove();
    }
    if (ofRandom(0, 1) < 0.8 && ball){
        passBallTo(getClosestMate());
    }
    glm::vec2 nextMove {0.0, 0.0};
    nextMove += keepCohesion();
    return nextMove;
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