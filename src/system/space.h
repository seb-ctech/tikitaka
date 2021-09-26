#include "ofMain.h"
#include <vector>
#include "shape.h"

/* This is the Space class.
It defines an approximated contour oround a point from a position sample.
This helps to orient and find the next relevant positions for the players in the simulation.*/

class Space {

public:
  Space();
  Space(glm::vec2 origin, Pitch* pitch, std::vector<glm::vec2> positions);
  void Update(std::vector<glm::vec2> positions);
  float getArea();
  glm::vec2 getCenter();
  std::vector<glm::vec2> getBoundaries(){ return boundaries; };

private:
  void ScanBoundaries(glm::vec2 origin, std::vector<glm::vec2> positions);
  
  Pitch* pitch = nullptr;
  glm::vec2 center;
  std::vector<glm::vec2> boundaries;
};