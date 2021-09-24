#include "pitch.h"
#include "space.h"

Pitch::Pitch(){
    
}

Pitch::Pitch(float x, float y){
    size = glm::vec2(x, y);
}

float Pitch::closestDistanceToBounds(glm::vec2 position, glm::vec2 location){
	float dToRightBounds = glm::distance(location, glm::vec2(size.x, position.y));
  float dToTopBounds = glm::distance(location, glm::vec2(position.x, size.y)); 
  float dToLeftBounds = glm::distance(location, glm::vec2(0, position.y)); 
  float dToBottomBounds = glm::distance(location, glm::vec2(position.x, 0)); 
	float minDistance = size.x;
	if (dToRightBounds < minDistance){
		minDistance = dToRightBounds;
	}
	if (dToLeftBounds < minDistance){
		minDistance = dToLeftBounds;
	}
	if (dToTopBounds < minDistance){
		minDistance = dToTopBounds;
	}
	if (dToBottomBounds < minDistance){
		minDistance = dToBottomBounds;
	}
	return minDistance;
}

Space Pitch::GetSpace(glm::vec2 location, std::vector<glm::vec2> sorrounding){
	return Space(location, this, sorrounding);
}

glm::vec2 Pitch::RandomPosition(){
	 return glm::vec2(ofRandom(0.0, size.x), ofRandom(0.0, size.y));
}

glm::vec2 Pitch::getClosestBound(glm::vec2 position){
	glm::vec2 rightBound(size.x, position.y);
	glm::vec2 leftBound(0, position.y);
	glm::vec2 topBound(position.x, size.y);
	glm::vec2 bottomBound(position.x, 0);
	float closestDist = glm::distance(position, rightBound);
	glm::vec2 closest = rightBound;
	float distance = glm::distance(position, leftBound);
	if(distance < closestDist){
		closestDist = distance;
		closest = leftBound;
	}
	distance = glm::distance(position, topBound);
	if(distance < closestDist){
		closestDist = distance;
		closest = topBound;
	}
	distance = glm::distance(position, bottomBound);
	if(distance < closestDist){
		closestDist = distance;
		closest = bottomBound;
	}
	return closest;
}

glm::vec2 Pitch::getClosestInBoundPosition(glm::vec2 position, glm::vec2 targetPosition){
	if(targetPosition.x > size.x){
		return castToBound(glm::vec2(size.x, position.y), position, targetPosition);
	}
	if(targetPosition.y > size.y){
		return castToBound(glm::vec2(position.x, size.y), position, targetPosition);
	}
	if(targetPosition.x < 0){
		return castToBound(glm::vec2(0, position.y), position, targetPosition);
	}
	if(targetPosition.y < 0){
		return castToBound(glm::vec2(position.x, 0), position, targetPosition);
	}
	return targetPosition;
}


glm::vec2 Pitch::castToBound(glm::vec2 bound, glm::vec2 position, glm::vec2 target){
	float stepSize = 1.0;
	glm::vec2 direction = glm::normalize(target - position);
	glm::vec2 rayPosition = position;
	float distance = glm::distance(bound, rayPosition);
	while(distance < stepSize * 1.1){
		rayPosition = rayPosition + direction * stepSize;
	}
	return rayPosition;
}