#include "players.h"

OffensivePlayer::OffensivePlayer() : Agent(){

}

OffensivePlayer::OffensivePlayer(Pitch pitch) : Agent(pitch) {

}

OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch pitch) : Agent(pos, pitch) {

}

void OffensivePlayer::display(SystemUnits su){
    ofFill();
    ofSetColor(220, 100, 50);
    ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size));
    if(hasBall()){
        ofNoFill();
        ofSetColor(220, 200, 80);
        ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 1.2);
    }
}

void OffensivePlayer::updateGame(std::vector<OffensivePlayer*> _team, std::vector<DefensivePlayer*> _opponents, OffensivePlayer* _ballowner){
    team = _team;
    opponents = _opponents;
    ballowner = _ballowner;
}

void OffensivePlayer::getBall(){
    ball = true;
}

void OffensivePlayer::passBall(OffensivePlayer* target){
    ball = false;
    target->getBall();
}

DefensivePlayer::DefensivePlayer() : Agent(){

}

DefensivePlayer::DefensivePlayer(Pitch pitch) : Agent(pitch) {
    
}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch pitch) : Agent(pos, pitch) {

}

void DefensivePlayer::display(SystemUnits su){
    ofSetColor(40, 80, 200);
    ofFill();
    ofDrawPlane(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 2.0, su.getSizeOnScreen(size) * 2.0);
}

void DefensivePlayer::updateGame(std::vector<OffensivePlayer*> _opponents, std::vector<DefensivePlayer*> _team, OffensivePlayer* _ballowner){
    team = _team;
    opponents = _opponents;
    ballowner = _ballowner;
}