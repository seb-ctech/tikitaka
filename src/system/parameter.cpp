#include "parameter.h"

Parameter::Parameter(){
  parameters.push_back("PASS RANGE");
  parameters.push_back("PASS RATE");
  parameters.push_back("PRESSURE RANGE");
  parameters.push_back("PRESSURE AMOUNT");
  parameters.push_back("RESPONSIVENESS");
  parameters.push_back("TRIANGLES");
  parameterLife = 0;
  valueLife = 0;
  fontMain.load("Roboto-Light.ttf", 60);
  fontSecondary.load("Roboto-Light.ttf", 20);
}

void Parameter::Init(std::vector<OffensivePlayer*> _Oplayers, std::vector<DefensivePlayer*> _Dplayers){
  Oplayers = _Oplayers;
  Dplayers = _Dplayers;
}

void Parameter::Display(){
  ofFill();
  ofSetColor(255);
  float width = fontMain.stringWidth(parameters[index]);
  float x = ((float)ofGetWidth() - width) / 2;
  if(parameterLife > 0){
    fontMain.drawString(parameters[index], x, ofGetHeight() / 2.0);
  }
  if(valueLife > 0){
    OffensivePlayer* offPlayer = Oplayers[0];
    float value;
    switch(index){
      case 0:
      value = 1- ((100.0 - offPlayer->getPassRange()) / 100.0);
      break;
      case 1:
      value = offPlayer->getPassRate();
      break;
      case 2:
      value = 1 - ((100.0 - offPlayer->getPressureRange()) / 100.0);
      break;
      case 3:
      value = 1 - ((10.0 - Dplayers[0]->getPressure()) / 10.0);
      break;
      case 4:
      value = offPlayer->getFlexibility();
      break;
      case 5:
      value = offPlayer->getTriangleRate();
      break;
    }
    ofSetLineWidth(12);
    ofNoFill();
    ofDrawLine(x, ofGetHeight() / 2.0 + 20, x + width * value, ofGetHeight() / 2.0 + 20);
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
  valueLife = valueLifeTime;
  index = index + delta;
  if(index < 0){
    index = parameters.size() - 1;
  }
  if(index >= parameters.size()){
    index = 0;
  }
}

void Parameter::SwitchParameterValue(int delta){
  parameterLife = valueLifeTime;
  valueLife = valueLifeTime;
  
    switch(index){
      case 0:
      for (OffensivePlayer* Offplayer : Oplayers){      
        Offplayer->setPassRange(delta);
      }
      break;

      case 1:
      for (OffensivePlayer* Offplayer : Oplayers){
        Offplayer->setPassRate(delta);
      }
      break;

      case 2:
      for (OffensivePlayer* Offplayer : Oplayers){
        Offplayer->setPressureRange(delta);
      }
      break;

      case 3:
      for (DefensivePlayer* Dplayer : Dplayers){
        Dplayer->setPressure(delta);
      }
      break;
    
      case 4:
      for (OffensivePlayer* Offplayer : Oplayers){
        Offplayer->setFlexibility(delta);
      }
      break;
      case 5:
      for (OffensivePlayer* Offplayer : Oplayers){
        Offplayer->setTriangleRate(delta);
      }
      break;

    }
}
