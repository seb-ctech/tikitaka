#pragma once
#include "player.h"
#include "ofMain.h"
#include "offense.h"


/* This is the class for Player with Defensive Role.
If close to the Ball Carrier he will close him down, It will try to close spaces with it's team mates and hold formation.
*/

class DefensivePlayer : public Player {

public:
	DefensivePlayer();
	DefensivePlayer(glm::vec2 pos, Pitch* pitch, int index);
	void Display(SystemUnits* su) override;
	virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* ball);
	void setPressure(float delta){pressStrength = glm::min(glm::max(0.0f, pressStrength + delta * 10.0f / 100.0f), 10.0f);};
	float getPressure(){return pressStrength;};

private:
	virtual void DecideNextPosition();
	glm::vec2 MoveTowardsBallCarrier();
	float coverRange = 15.0;
	float pressStrength = 6.0;
};