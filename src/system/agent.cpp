#include "agent.h"
#include "system_units.h"

Agent::Agent(){
    StartOnRandomPosition();
}

Agent::Agent(glm::vec2 pos){
    position = pos;
}

void Agent::display(){
    ofSetColor(255);
    ofFill();
    ofDrawCircle(position.x, position.y, size);
}

void Agent::update(){


}

void Agent::StartOnRandomPosition(){
    //FIXME: Segmentation Fault
    //glm::vec2 pitchSize = SystemUnits::getPitchSize();
    glm::vec2 pitchSize = glm::vec2(100.0, 100.0);
    position = glm::vec2(ofRandom(pitchSize.x), ofRandom(pitchSize.y));
}