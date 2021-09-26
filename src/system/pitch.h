#pragma once

#include "ofMain.h"
#include <vector>

class Space;

/* This is the Pitch class.
It defines the boundaries of the Pitch in systemUnits
a provides positioning functions in relation to its bounds*/

class Pitch {

public: 
	Pitch();
	Pitch(float x, float y);
	glm::vec2 getRandomPosition();
	Space getSpace(glm::vec2 location, std::vector<glm::vec2> sorrounding);
	float getClosestDistanceToBounds(glm::vec2 position, glm::vec2 location);
	glm::vec2 getClosestBound(glm::vec2 position);
	glm::vec2 getSize(){ return size; };
	glm::vec2 getClosestInBoundPosition(glm::vec2 position, glm::vec2 targetPosition);
	bool checkInBound(glm::vec2 bound, glm::vec2 target);
	bool checkInBounds(glm::vec2 target);

private:
	glm::vec2 getNextApproximatedBound(glm::vec2 Bound, glm::vec2 Position, glm::vec2 Target);
	
	glm::vec2 size;
};