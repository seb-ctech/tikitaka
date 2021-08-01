#include "agent.h"

Agent::Agent(){
}

Agent::Agent(Pitch _pitch){
    StartOnRandomPosition(_pitch.getSize());
    pitch = _pitch;
}

Agent::Agent(glm::vec2 pos){
    position = pos;
}

void Agent::display(SystemUnits su){

}

void Agent::update(){
    locomotion();
}

void Agent::StartOnRandomPosition(glm::vec2 bounds){

    glm::vec2 pitchSize = glm::vec2(bounds.x, bounds.y);
    position = glm::vec2(ofRandom(pitchSize.x), ofRandom(pitchSize.y));
}

void Agent::locomotion(){
    drive();
    if (acceleration.length() >= maxAcc){
        acceleration = glm::normalize(acceleration) * maxAcc;
    }
    velocity += acceleration;
    if (velocity.length() >= maxSpeed){
       velocity = glm::normalize(velocity) * maxSpeed;
    }
    avoidBounds();
    position += velocity;
}

void Agent::drive(){
    glm::vec2 move = nextMove();
    acceleration += move;
    
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