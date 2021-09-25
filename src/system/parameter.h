#pragma once
#include <string>
#include <vector>
#include "offense.h"
#include "system_units.h"
#include "ofMain.h"

class Parameter {

  public:
  Parameter();
  void SwitchParameter(int delta);
  void SwitchParameterValue(int delta);
  void Display();
  void Update();
  void Init(std::vector<OffensivePlayer*> players);

  private:
  ofTrueTypeFont fontMain;
  ofTrueTypeFont fontSecondary;
  std::vector<string> parameters;
  float valueLifeTime = 2.0;
  float parameterLifeTime = 2.0;
  float valueLife;
  float parameterLife;
  int index = 0;
  std::vector<OffensivePlayer*> players;

};