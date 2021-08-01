#include "players.h"

OffensivePlayer::OffensivePlayer() : Agent(){

}

OffensivePlayer::OffensivePlayer(Pitch pitch) : Agent(pitch) {

}

OffensivePlayer::OffensivePlayer(glm::vec2 pos, Pitch pitch) : Agent(pos, pitch) {

}

void OffensivePlayer::display(SystemUnits su){
    ofSetColor(220, 220, 30);
    ofFill();
    ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size));
}

DefensivePlayer::DefensivePlayer() : Agent(){

}

DefensivePlayer::DefensivePlayer(Pitch pitch) : Agent(pitch) {
    
}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch pitch) : Agent(pos, pitch) {

}

void DefensivePlayer::display(SystemUnits su){
    ofSetColor(20, 40, 230);
    ofFill();
    ofDrawPlane(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), su.getSizeOnScreen(size) * 2.0, su.getSizeOnScreen(size) * 2.0);
}