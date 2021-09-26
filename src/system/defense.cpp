#include "defense.h"
#include "shape.h"

DefensivePlayer::DefensivePlayer() : Player(){

}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch* pitch, int index) : Player(pos, pitch, index) {

}

void DefensivePlayer::Display(SystemUnits* su){
	Player::Display(su);
	ofSetColor(40, 80, 200);
	ofFill();
	ofDrawPlane(su->getXPosOnScreen(position.x), 
							su->getYPosOnScreen(position.y), 
							su->getSizeOnScreen(size) * 2.0, 
							su->getSizeOnScreen(size) * 2.0);	
}

void DefensivePlayer::InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders, Ball* ball){
	OwnTeam = Defenders;
	OpponentTeam = Attackers;
	Player::InitMatch(Attackers, Defenders, ball);
}

void DefensivePlayer::DecideNextPosition(){
	float distance = glm::distance(BallCarry->getPos(), position);
	if(distance < coverRange){
		targetPosition = MoveTowardsBallCarrier();
		AdjustWalkingSpeed();
	} else {
		targetPosition = KeepCohesion();
	}
}

glm::vec2 DefensivePlayer::MoveTowardsBallCarrier(){
	float pressStrength = 3.0;
	glm::vec2 direction = glm::normalize(BallCarry->getPos() - position);
	return position + direction * pressStrength;
}