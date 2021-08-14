#pragma once
#include "ofMain.h"
#include "system_units.h"
#include "pitch.h"

// This is an Agent class.
// Agents are Entities that have a basic locomotion loop and an intrinsic drive.

class Agent {

public:
	Agent();
	Agent(glm::vec2 pos);
	virtual void update();
	glm::vec2 getPos(){ return position; };

protected:
	void steer(glm::vec2 force);

	glm::vec2 acceleration;
	glm::vec2 velocity;
	glm::vec2 position;
	float maxAcc = 0.006;
	float maxSpeed = 0.1;

private:
	void init_locomotion();
	void locomotion();
	void StartOnRandomPosition(glm::vec2 bounds);
};

