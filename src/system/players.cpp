#include "players.h"
#include "shape.h"

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


glm::vec2 OffensivePlayer::nextMove(){

    if (ofRandom(0, 1) < 0.04){
        return Agent::nextMove();
    }
    glm::vec2 nextMove {0.0, 0.0};
    nextMove += keepCohesion();
    return nextMove;
}

glm::vec2 OffensivePlayer::keepCohesion(){
    std::vector<Agent*> teamAgents;
    for (Agent* a : team){
        teamAgents.push_back(a);
    }
    std::vector<Agent*> closeTeamMates =  getClosestAgents(teamAgents, 30.0);
    std::vector<glm::vec2> positions;
    for(Agent* a : closeTeamMates){
        positions.push_back(a->getPos());
    }
    glm::vec2 center = FootballShape::center(this->position, positions);
    return center;
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

glm::vec2 DefensivePlayer::nextMove(){
    return(this->position);
}