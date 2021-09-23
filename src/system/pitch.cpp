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