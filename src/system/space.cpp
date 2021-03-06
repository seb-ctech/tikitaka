#include "space.h"

Space::Space(){
  std::vector<glm::vec2> points;
  for (int i = 0; i < 5; i++){
    points.push_back(glm::vec2(0,0));
  }
  boundaries = points;
}

Space::Space(glm::vec2 origin, Pitch* _pitch, std::vector<glm::vec2> positions){
  pitch = _pitch;
  ScanBoundaries(origin, positions);
}

void Space::ScanBoundaries(glm::vec2 origin, std::vector<glm::vec2> positions){
  float angle = 0; 
  int batchSize = 20;
  int steps = 100;
  int n = steps / batchSize;
  std::vector<glm::vec2> foundBounds; 
  float angleStep = glm::two_pi<float>() / steps;
  while (angle < glm::two_pi<float>()){
    glm::vec2 foundPosition = FootballShape::RaycastScan(origin, pitch, positions, angle, 0.5);
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
  boundaries = closestBounds;
}

void Space::Update(std::vector<glm::vec2> positions){
  ScanBoundaries(center, positions);
}

/* 1) For every corner of the space, 
that corner and the next form a triangle 
with the center of the space, dividing the space like a Pie.
2) To get right angled triangles the vector from A to Center is
projected on the vector AB to get the perpendicular intersection.
3) The triangle is split into two triangles with different 
bases and the same height. The area can now be easily computed b*h/2
4) The areas are summed up and divided by the number of the triangles,
which is the same as the number of corner points.*/

float Space::getArea(){
  glm::vec2 c = getCenter();
  float area = 0;
  for(int i = 0; i < boundaries.size() - 1; i++){
    //Triangles
    glm::vec2 a = boundaries[i];
    glm::vec2 b = boundaries[i+1];
    glm::vec2 ab = b - a;
    glm::vec2 ac = c - a;
    //Splitpoint of Triangle
    float proj = glm::dot(glm::normalize(ac), glm::normalize(ab));
    glm::vec2 s = a + proj * ab;
    //Area 1
    float height = glm::distance(c, s);
    float base1 = glm::distance(s, a);
    area += (base1 * height) / 2;
    //Area 2
    float base2 = glm::distance(s, b);
    area += (base2 * height) / 2;
  }
  return area / boundaries.size();
}

glm::vec2 Space::getCenter(){
  glm::vec2 sum;
  for(glm::vec2 point : boundaries){
    sum += point;
  } 
  return sum/boundaries.size();
}