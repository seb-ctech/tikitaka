#pragma once
#include "player.h"
#include "ofMain.h"

class OffensivePlayer; // Forward Declaration


/* This is the class for Player with Defensive Role.
If close to the Ball Carrier he will close him down, It will try to close spaces with it's team mates and hold formation.
*/

class DefensivePlayer : public Player {

public:
	DefensivePlayer();
	DefensivePlayer(glm::vec2 pos, Pitch pitch);
	void display(SystemUnits su) override;
	virtual void setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders);

private:
	virtual void NewTargetSpace();
	virtual glm::vec2 CourseCorrection(glm::vec2 currentTargetSpace);
	virtual glm::vec2 MoveAdjustments(glm::vec2 nextMove);
	glm::vec2 MoveTowardsBallCarrier();
	// Approach closest opposing Player
	// Move towards ball carrier
	// keep cohesion with team
};