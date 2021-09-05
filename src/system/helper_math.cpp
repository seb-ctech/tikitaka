
#include "helper_math.h"

glm::vec2 HelperMath::PolarToCartesian(float r, float teta){
  float x = r * glm::cos(teta);
  float y = r * glm::sin(teta);
  return glm::vec2(x, y);
}

float HelperMath::CartesianToPolAngle(glm::vec2 v){
  return glm::atan(v.y, v.x);
}

float HelperMath::CartesianToPolRadius(glm::vec2 v){
  return glm::sqrt(v.x * v.x + v.y * v.y);
}

float HelperMath::DegreesToRadians(float degree){
  return degree * (glm::pi<float>() / 180.0);
}