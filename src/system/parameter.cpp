#include "parameter.h"

Parameter::Parameter(){
  parameters.push_back("PASS RANGE");
  parameters.push_back("PASS RATE");
  parameters.push_back("PRESSURE RANGE");
  parameters.push_back("FLEXIBILITY");
  parameters.push_back("CHAOS RATE");
  parameterLife = 0;
  valueLife = 0;
  fontMain.load("Roboto-Light.ttf", 60);
  fontSecondary.load("Roboto-Light.ttf", 20);
}

void Parameter::Init(std::vector<OffensivePlayer*> _players){
  players = _players;
}

void Parameter::Display(){
  ofFill();
  ofSetColor(255);
  if(parameterLife > 0){
    fontMain.drawString(parameters[index], ofGetWidth() / 4.0, ofGetHeight() / 2.0);
  }
  if(valueLife > 0){
    OffensivePlayer* offPlayer = players[0];
    float value;
    switch(index){
      case 0:
      value = offPlayer->getPassRange();
      break;
      case 1:
      value = offPlayer->getPassRate();
      break;
      case 2:
      value = offPlayer->getPressureRange();
      break;
      case 3:
      value = offPlayer->getFlexibility();
      break;
      case 4:
      value = offPlayer->getChaosRate();
      break;
    }
    fontSecondary.drawString(std::to_string(value), ofGetWidth() / 4.0, ofGetHeight() / 2.0 + 40);
  }
}

void Parameter::Update(){
  if(parameterLife > 0){
    parameterLife = parameterLife - 0.01;
  }
  if(valueLife > 0){
    valueLife = valueLife - 0.01;
  }
  if(parameterLife < 0){
    parameterLife = 0;
  }
  if(valueLife < 0){
    valueLife = 0;
  }
}

void Parameter::SwitchParameter(int delta){
  parameterLife = parameterLifeTime;
  index = index + delta;
  if(index >= parameters.size()){
    index = 0;
  }
  if(index < 0){
    index = parameters.size() - 1;
  }
}

void Parameter::SwitchParameterValue(int delta){
  valueLife = valueLifeTime;
  for (OffensivePlayer* player : players){
    switch(index){
      case 0:
      player->setPassRange(delta);
      break;
      case 1:
      player->setPassRate(delta);
      break;
      case 2:
      player->setPressureRange(delta);
      break;
      case 3:
      player->setFlexibility(delta);
      break;
      case 4:
      player->setChaosRate(delta);
      break;
    }
  }
}