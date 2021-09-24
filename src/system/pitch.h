#pragma once
#include "ofMain.h"
#include <vector>

class Space;

class Pitch {

	public: 
		Pitch();
		Pitch(float x, float y);
		Space GetSpace(glm::vec2 location, std::vector<glm::vec2> sorrounding);
		float closestDistanceToBounds(glm::vec2 position, glm::vec2 location);
		glm::vec2 getClosestBound(glm::vec2 position);
		glm::vec2 RandomPosition();
		glm::vec2 getSize(){
				return size;
		}
		glm::vec2 getClosestInBoundPosition(glm::vec2 position, glm::vec2 targetPosition);
	private:
		glm::vec2 size;
		glm::vec2 castToBound(glm::vec2 Bound, glm::vec2 Position, glm::vec2 Target);
};