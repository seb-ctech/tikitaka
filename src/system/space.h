#include "ofMain.h"
#include <vector>
#include "shape.h"

class Space {

public:
  Space();
  Space(glm::vec2 origin, Pitch pitch, std::vector<glm::vec2> positions);
  float getArea();
  glm::vec2 getCenter();
  void Update(std::vector<glm::vec2> positions);
  std::vector<glm::vec2> getBoundaries(){ return boundaries; };

private:
  Pitch pitch;
  glm::vec2 center;
  std::vector<glm::vec2> boundaries;
  void ScanBoundaries(glm::vec2 origin, std::vector<glm::vec2> positions);
};