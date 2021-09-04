
#include "helper_math.h"

glm::vec2 HelperMath::PolarToCartesian(float r, float teta){
  float x = r * glm::cos(teta);
  float y = r * glm::sin(teta);
  return glm::vec2(x, y);
}

float HelperMath::CartesianToPolAngle(glm::vec2 v){
  float ratio = v.y / v.x;
  return glm::atan(ratio);
}

float HelperMath::CartesianToPolRadius(glm::vec2 v){
  return glm::sqrt(v.x * v.x + v.y + v.y);
}

