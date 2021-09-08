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
	void display(SystemUnits su) override;
	virtual void InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);

private:
	virtual void NewTargetSpace();
	virtual void CourseCorrection();
	virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
	glm::vec2 MoveTowardsBallCarrier();
	// Approach closest opposing Player
	// Move towards ball carrier
	// keep cohesion with team
};