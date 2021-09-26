#include "agent.h"

Agent::Agent(){
    position = glm::vec2(0.0, 0.0);
    Init();
}

Agent::Agent(glm::vec2 pos){
    position = pos;
    Init();
}

void Agent::Init(){
    infoFont.load("Roboto-Light.ttf", 8);
    InitLocomotion();
}

void Agent::InitLocomotion(){
    velocity = glm::vec2(0.0, 0.0);
    acceleration = glm::vec2(0.0, 0.0);
}

void Agent::Update(){
    Locomotion();
}

void Agent::StartOnRandomPosition(glm::vec2 bounds){
    position = glm::vec2(ofRandom(bounds.x), ofRandom(bounds.y));
}

void Agent::Locomotion(){
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




