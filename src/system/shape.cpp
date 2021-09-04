#include "shape.h"

glm::vec2 FootballShape::RaycastScan(glm::vec2 origin, Pitch pitch, std::vector<glm::vec2> positions, float angle, float stepSize){
  float seekDistance = 2.0;
  glm::vec2 currentPosition = origin;
  glm::vec2 direction = glm::normalize(HelperMath::PolarToCartesian(1, angle));
  glm::vec2 step = direction * stepSize;
  glm::vec2 pitchSize = pitch.getSize();
  if(positions.size() > 0){
    while(currentPosition.x > 1 && currentPosition.y > 1 && currentPosition.x < pitchSize.x - 1 && currentPosition.y < pitchSize.y - 1){
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
    glm::vec2 foundPosition = RaycastScan(origin, pitch, positions, angle, 2);
    foundBounds.push_back(foundPosition);
    angle += angleStep;
  }
  std::vector<glm::vec2> closestBounds; 
  for(int i = 0; i < n; i++){
    glm::vec2 shortest = glm::vec2(0,0);
    for(int j = 0; j < batchSize; j++){
      float minDist = glm::distance(origin, shortest);
      glm::vec2 current = foundBounds[i * batchSize + j];
      if (glm::distance(origin, current) < minDist){
        shortest = current;
      }
    }
    closestBounds.push_back(shortest);
  }
  return closestBounds;
}