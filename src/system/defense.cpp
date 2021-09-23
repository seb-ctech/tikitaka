#include "defense.h"
#include "shape.h"

//TODO: Replace Randomness -> ofRandom() with Decision Making and Algorithms

DefensivePlayer::DefensivePlayer() : Player(){

}

DefensivePlayer::DefensivePlayer(glm::vec2 pos, Pitch* pitch, int index) : Player(pos, pitch, index) {

}

void DefensivePlayer::display(SystemUnits* su){
	Player::display(su);
	ofSetColor(40, 80, 200);
	ofFill();
	ofDrawPlane(su->getXPosOnScreen(position.x), 
							su->getYPosOnScreen(position.y), 
							su->getSizeOnScreen(size) * 2.0, 
							su->getSizeOnScreen(size) * 2.0);	
}

void DefensivePlayer::InitMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
	OwnTeam = Defenders;
	OpponentTeam = Attackers;
	Player::InitMatch(Attackers, Defenders);
}


// TODO: Implement Closing Spaces and Keep Formation
void DefensivePlayer::NewTargetSpace(){
	targetSpace = pitch->GetSpace(MoveTowardsBallCarrier(), getOtherPlayersPosition(OpponentTeam));
}

// TODO: Reevaluate Space
void DefensivePlayer::CourseCorrection(){
	Player::CourseCorrection();
}

// TODO: Hold Position, Press the Ball Carrier
glm::vec2 DefensivePlayer::MoveAdjustments(glm::vec2 nextMove){
	glm::vec2 finalMove = nextMove;
	finalMove += MoveTowardsBallCarrier() * 0.2;
	return finalMove;
}

glm::vec2 DefensivePlayer::MoveTowardsBallCarrier(){
	float range = 40.0;
	float distance = glm::distance(BallCarry->getPos(), position);
	if(distance <= range){
		float influence = 1.0 - distance / range;
		return glm::normalize(BallCarry->getPos() - position) * accFactor * influence * 2;
	} else {
		return glm::vec2(0,0);
	}
}