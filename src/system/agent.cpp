#include "agent.h"

Agent::Agent(){
    position = glm::vec2(0.0, 0.0);
    init();
}

Agent::Agent(glm::vec2 pos){
    position = pos;
    init();
}

void Agent::init(){
    infoFont.load("Roboto-Light.ttf", 8);
    init_locomotion();
}

void Agent::init_locomotion(){
    velocity = glm::vec2(0.0, 0.0);
    acceleration = glm::vec2(0.0, 0.0);
}

void Agent::update(){
    locomotion();
}

void Agent::StartOnRandomPosition(glm::vec2 bounds){
    position = glm::vec2(ofRandom(bounds.x), ofRandom(bounds.y));
}

void Agent::locomotion(){
    if(speed > speedLimit) speed = speedLimit;
    if(speed <= speedMin) speed = speedMin;
    if (glm::length(acceleration) >= maxAcc){
        acceleration = glm::normalize(acceleration) * maxAcc;
    }
    velocity += acceleration;
    if (glm::length(velocity) >= speed){
        velocity = glm::normalize(velocity) * speed;
    }
    position += velocity;
}

void Agent::steer(glm::vec2 force){
    // Acceleration must be direct linear value and not accumulate over time.
    acceleration = force;
}




