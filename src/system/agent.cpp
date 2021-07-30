#include "agent.h"

Agent::Agent(){
    position = glm::vec2(0.0,0.0);
}

Agent::Agent(Pitch pitch){
    StartOnRandomPosition(pitch.getSize());
}

Agent::Agent(glm::vec2 pos){
    position = pos;
}

void Agent::display(SystemUnits su){
    ofFill();
    ofDrawCircle(su.getXPosOnScreen(position.x), su.getYPosOnScreen(position.y), size);
}

void Agent::update(){


}

void Agent::StartOnRandomPosition(glm::vec2 bounds){

    glm::vec2 pitchSize = glm::vec2(bounds.x, bounds.y);
    position = glm::vec2(ofRandom(pitchSize.x), ofRandom(pitchSize.y));
}