#include "shape.h"

glm::vec2 FootballShape::center(glm::vec2 Origin, std::vector<glm::vec2> Positions){
  glm::vec2 center = Origin;
  for (glm::vec2 p : Positions){
    center += p;
  }
  if (glm::length(center) > 0.0 && Positions.size() > 0){
    return center / (Positions.size() + 1);
  } else {
    return center;
  }
}