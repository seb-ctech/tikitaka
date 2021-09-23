#pragma once
#include "ball.h"
#include "offense.h"

Ball::Ball(){
  position = glm::vec2(0,0);
}

void Ball::Update(){
  if(attached){
    position = owner->getPos();
  } else {
    MoveToNextOwner();
  }
}

void Ball::Display(SystemUnits* su){
  if(!attached){
    ofSetColor(220, 200, 80);
    ofFill();
    ofDrawCircle(su->getXPosOnScreen(position.x), su->getYPosOnScreen(position.y), su->getSizeOnScreen(size) * 1.2);
  }
}


void Ball::PassTo(OffensivePlayer* target){
  attached = false;
  owner = target;
}


void Ball::AttachToPlayer(OffensivePlayer* target){
  if(owner != target){
    owner = target;
  }
  target->ReceiveBall();
  attached = true;
}

void Ball::MoveToNextOwner(){
  float distanceToTarget = glm::distance(owner->getPos(), position);
  if(distanceToTarget < attachTolerance){
    AttachToPlayer(owner);
  } else {
    glm::vec2 direction = glm::normalize(owner->getPos() - position);
    position = position + direction * passPower;
  }
}