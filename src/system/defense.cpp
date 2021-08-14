#include "defense.h"
#include "shape.h"


DefensivePlayer::DefensivePlayer() : Player(){

}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch pitch) : Player(pos, pitch) {

}

void DefensivePlayer::display(SystemUnits su){
    ofSetColor(40, 80, 200);
    ofFill();
    ofDrawPlane(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 2.0, su.getSizeOnScreen(size) * 2.0);
}

void DefensivePlayer::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  Player::setMatch(Attackers, Defenders);
  OwnTeam = Attackers;
  OpponentTeam = Defenders;
}

glm::vec2 DefensivePlayer::nextMove(){
    if(ofRandom(0, 1) < 0.95){
        return moveTowardsBallCarrier();
    }
    return Player::nextMove();
}

glm::vec2 DefensivePlayer::moveTowardsBallCarrier(){
    float distance = glm::distance(BallCarry->getPos(), position);
    float influence = 1.0 - distance / 100.0;
    return glm::mix(BallCarry->getPos(), position, influence);
}