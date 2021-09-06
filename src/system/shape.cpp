#include "shape.h"

glm::vec2 FootballShape::RaycastTo(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float stepSize){
  float seekDistance = stepSize;
  glm::vec2 currentPosition = origin;
  glm::vec2 step = glm::normalize(to - origin) * stepSize ;
  if(positions.size() > 0){
    while((currentPosition.x > stepSize && currentPosition.y > stepSize) 
       && (glm::distance(currentPosition, to) > stepSize)){
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
}

std::vector<glm::vec2> FootballShape::RaycastToMany(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float stepSize, int max){
  std::vector<glm::vec2> results;
  int count = 0;
  float seekDistance = stepSize;
  glm::vec2 currentPosition = origin;
  glm::vec2 step = glm::normalize(to - origin) * stepSize ;
  if(positions.size() > 0){
    while((currentPosition.x > stepSize && currentPosition.y > stepSize) 
       && (count < max || max < 1) 
       && (glm::distance(currentPosition, to) > stepSize)){
      for(glm::vec2 pos : positions){
        float distance = glm::distance(currentPosition, pos);
        if (distance <= seekDistance){
          results.push_back(pos);
        }
      }
      currentPosition += step;
      count++;
    }
  }
  return results;
}

glm::vec2 FootballShape::RaycastScan(glm::vec2 origin, Pitch pitch, std::vector<glm::vec2> positions, float angle, float stepSize){
  float seekDistance = stepSize;
  glm::vec2 currentPosition = origin;
  glm::vec2 step = HelperMath::PolarToCartesian(stepSize, angle);
  glm::vec2 pitchSize = pitch.getSize();
  if(positions.size() > 0){
    while((currentPosition.x > stepSize && currentPosition.y > stepSize) 
       && (currentPosition.x < pitchSize.x - stepSize && currentPosition.y < pitchSize.y - stepSize)){
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