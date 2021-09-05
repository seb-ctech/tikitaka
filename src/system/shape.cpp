#include "shape.h"


//FIXME: See red line, something does not work in the detection
glm::vec2 FootballShape::RaycastScan(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float angle, float stepSize){
  float seekDistance = stepSize;
  glm::vec2 currentPosition = origin;
  glm::vec2 step = HelperMath::PolarToCartesian(stepSize, angle);
  if(positions.size() > 0){
    while(currentPosition.x > stepSize && currentPosition.y > stepSize && currentPosition.x < to.x - stepSize && currentPosition.y < to.y - stepSize){
      for(glm::vec2 pos : positions){
        float distance = glm::distance(currentPosition, pos);
        if (distance <= seekDistance){
          return pos;
        }
      }
      currentPosition += step;
    }
    return currentPosition;
  }
  return glm::vec2(0,0);
}


std::vector<glm::vec2> FootballShape::ScanSpace(glm::vec2 origin, Pitch pitch, std::vector<glm::vec2> positions){
  float angle = 0; 
  int batchSize = 8;
  int steps = 64;
  int n = steps / batchSize;
  std::vector<glm::vec2> foundBounds; 
  float angleStep = glm::two_pi<float>() / steps;
  while (angle < glm::two_pi<float>()){
    glm::vec2 foundPosition = RaycastScan(origin, pitch.getSize(), positions, angle, 2);
    foundBounds.push_back(foundPosition);
    angle += angleStep;
  }
  std::vector<glm::vec2> closestBounds; 
  for(int i = 0; i < n; i++){
    glm::vec2 shortest;
    float minDist = 100;
    for(int j = 0; j < batchSize; j++){
      glm::vec2 current = foundBounds[i * batchSize + j];
      if (glm::distance(origin, current) < minDist){
        shortest = current;
        minDist = glm::distance(shortest, origin);
      }
    }
    bool unique = true;
    for(glm::vec2 value : closestBounds){
      if(shortest == value){
        unique = false;
        break;
      }
    }
    if(unique){
      closestBounds.push_back(shortest);
    }
  }
  return closestBounds;
}