#pragma once
#include "ofMain.h"
#include "system_units.h"
#include "pitch.h"

/* This is an Agent class.
Agents are Entities that have a basic locomotion loop and implement seeking behavior, 
a force that adds to velocity to steer it to a target location.
Conceptually this is the bridge between higher concepts such as "Players" and the representation inside of openFrameworks. */

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
	float accFactor = 0.0001;

private:
	void init();
 	void init_locomotion();
	void locomotion();
	void StartOnRandomPosition(glm::vec2 bounds);
	ofFont infoFont;
};

