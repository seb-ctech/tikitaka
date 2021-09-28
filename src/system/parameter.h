#pragma once
#include <string>
#include <vector>
#include "offense.h"
#include "defense.h"
#include "system_units.h"
#include "ofMain.h"

/* This is a Parameter class.
It holds and displays a parameter collection 
that can be controlled from within the ofApp*/

class Parameter {

public:
  Parameter();
  void SwitchParameter(int delta);
  void SwitchParameterValue(int delta);
  void Display();
  void Update();
  void Init(std::vector<OffensivePlayer*> offPlayers, std::vector<DefensivePlayer*> defPlayers);

private:
  ofTrueTypeFont fontMain;
  ofTrueTypeFont fontSecondary;
  std::vector<string> parameters;
  float valueLifeTime = 1.8;
  float parameterLifeTime = 2.0;
  float valueLife;
  float parameterLife;
  int index = 0;
  std::vector<OffensivePlayer*> Oplayers;
  std::vector<DefensivePlayer*> Dplayers;

};