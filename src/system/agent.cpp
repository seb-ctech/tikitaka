#include "agent.h"

Agent::Agent(){
    position = glm::vec2(0.0, 0.0);
    init();
}

Agent::Agent(Pitch _pitch){
    StartOnRandomPosition(_pitch.getSize());
    pitch = _pitch;
    init();
}

Agent::Agent(glm::vec2 pos, Pitch _pitch){
    position = pos;
    pitch = _pitch;
    init();
}

void Agent::init(){
    velocity = glm::vec2(0.0, 0.0);
    acceleration = glm::vec2(0.0, 0.0);
}

void Agent::display(SystemUnits su){

}

void Agent::update(int i){
    locomotion();
}

void Agent::StartOnRandomPosition(glm::vec2 bounds){

    glm::vec2 pitchSize = glm::vec2(bounds.x, bounds.y);
    position = glm::vec2(ofRandom(pitchSize.x), ofRandom(pitchSize.y));
}

void Agent::locomotion(){
    drive();
    if (glm::length(acceleration) >= maxAcc){
        acceleration = glm::normalize(acceleration) * maxAcc;
    }
    velocity += acceleration;
    if (glm::length(velocity) >= maxSpeed){
        velocity = glm::normalize(velocity) * maxSpeed;
    }
    avoidBounds();
    position += velocity;
}

void Agent::drive(){
    if(ofGetFrameNum() % 200 == 0){
        glm::vec2 move = nextMove();
        acceleration = move;
    }
}

glm::vec2 Agent::nextMove(){
    glm::vec2 move = glm::vec2(ofRandomf() * 0.01, ofRandomf() * 0.01);
    return move;
}

void Agent::avoidBounds(){
    glm::vec2 nextPos = position + velocity;
    glm::vec2 pitchSize = pitch.getSize();
    if (nextPos.x >= pitchSize.x
        || nextPos.x <= 0 
        || nextPos.y >= pitchSize.y 
        || nextPos.y <= 0){
            velocity *= -1.0;
            acceleration *= 0.0;
        }
}