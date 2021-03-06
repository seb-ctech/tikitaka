#pragma once
#include "ofMain.h"
#include "system_units.h"
#include "pitch.h"

/* This is an Agent class.
Agents are Entities that have a basic Locomotion loop and implement seeking behavior, 
a force that adds to velocity to steer it to a target location.
Conceptually this is the bridge between higher concepts such as "Players" and the representation inside of openFrameworks. */

class Agent {

public:
	Agent();
	Agent(glm::vec2 pos);
	virtual void Update();
	glm::vec2 getPos(){ return position; };

protected:
	void steer(glm::vec2 force);

	glm::vec2 acceleration;
	glm::vec2 velocity;
	glm::vec2 position;
	ofTrueTypeFont infoFont;
	float maxAcc = 0.006;
	float speed = 0.05; // Max-Value that velocity can reach, can vary over time;
	float speedLimit = 0.1; // Value that limits speed
	float speedMin = 0.01;
	float accFactor = 0.01;

private:
	void Init();
 	void InitLocomotion();
	void Locomotion();
	void StartOnRandomPosition(glm::vec2 bounds);
};

