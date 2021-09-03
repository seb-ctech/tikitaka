#include "defense.h"
#include "shape.h"

//TODO: Replace Randomness -> ofRandom() with Decision Making and Algorithms

DefensivePlayer::DefensivePlayer() : Player(){

}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch pitch) : Player(pos, pitch) {

}

void DefensivePlayer::display(SystemUnits su){
	Player::display(su);
	ofSetColor(40, 80, 200);
	ofFill();
	ofDrawPlane(su.getXPosOnScreen(position.x), 
							su.getYPosOnScreen(position.y), 
							su.getSizeOnScreen(size) * 2.0, 
							su.getSizeOnScreen(size) * 2.0);	
}

void DefensivePlayer::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
	Player::setMatch(Attackers, Defenders);
	OwnTeam = Attackers;
	OpponentTeam = Defenders;
}


// TODO: Implement Closing Spaces and Keep Formation
glm::vec2 DefensivePlayer::NextTargetSpace(){
	return Player::NextTargetSpace();
}

// TODO: Reevaluate Space
glm::vec2 DefensivePlayer::CourseCorrection(glm::vec2 currentTargetSpace){
	return Player::CourseCorrection(currentTargetSpace);
}

// TODO: Hold Position, Press the Ball Carrier
glm::vec2 DefensivePlayer::MoveAdjustments(glm::vec2 nextMove){
	glm::vec2 finalMove = nextMove;
	finalMove += MoveTowardsBallCarrier();
	return finalMove;
}

glm::vec2 DefensivePlayer::MoveTowardsBallCarrier(){
	float range = 60.0;
	float distance = glm::distance(BallCarry->getPos(), position);
	if(distance <= range){
		float influence = 1.0 - distance / range;
		return glm::normalize(BallCarry->getPos() - position) * accFactor * influence;
	} else {
		return glm::vec2(0,0);
	}
}