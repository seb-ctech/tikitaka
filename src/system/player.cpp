#include "player.h"

Player::Player() : Agent(){

};


Player::Player(glm::vec2 _pos, Pitch _pitch) : Agent(_pos){
  pitch = _pitch;
  targetPos = RandomLocation();
};

void Player::update(Player* ballcarry){
  BallCarry = ballcarry;
  MoveToTarget();
  AvoidOutOfBounds();
  Agent::update();
};

void Player::display(SystemUnits su){

};

void Player::setMatch(std::vector<Player*> Attackers, std::vector<Player*> Defenders){
  AllPlayers.clear();
  for (Player* p : Attackers) {
    AllPlayers.push_back(p);
  }
  for (Player* p : Defenders) {
    AllPlayers.push_back(p);
  }
};

std::vector<Player*> Player::getClosestPlayersInArea(Team team){
  std::vector<Player*> SorroundingPlayers;
  std::vector<Player*> SamplePlayers;
  switch (team) {
        case ALL: SamplePlayers = AllPlayers;
        case OWN: SamplePlayers = OwnTeam;
        case OPP: SamplePlayers = OpponentTeam;
  }
  return SorroundingPlayers;
};

std::vector<Player*> Player::getAllPlayersInRange(Team team, float Range){
    std::vector<Player*> closestPlayers;
    std::vector<Player*> SamplePlayers;
    switch (team) {
        case ALL: SamplePlayers = AllPlayers;
        case OWN: SamplePlayers = OwnTeam;
        case OPP: SamplePlayers = OpponentTeam;
    }
    for (Player* a : SamplePlayers){
        float distance = glm::distance(position, a->position);
        if (distance <= Range){
            closestPlayers.push_back(a);
        }
    }
    return closestPlayers;
};

//TODO: Implement combined logic for moving to target and steering based on rules
glm::vec2 Player::nextMove(){
    glm::vec2 move = RandomLocation();
    return move;
};

void Player::AvoidOutOfBounds(){
    glm::vec2 nextPos = position + velocity;
    glm::vec2 pitchSize = pitch.getSize();
    if (nextPos.x >= pitchSize.x
     || nextPos.x <= 0 
     || nextPos.y >= pitchSize.y 
     || nextPos.y <= 0){
      velocity *= -1.0;
      acceleration *= 0.0;
    }
};

// TODO: Implement as steering behavior?
// Maybe change TargetPosition more often?
void Player::MoveToTarget(){
  if(glm::length((targetPos - position)) <= 2.0){     
        targetPos = nextMove();
				float speedVariation = 0.02;
        maxSpeed = 0.06 + ofRandom(speedVariation * -1, speedVariation);
    } else {
        steer(glm::normalize(targetPos - position) * 0.01 * (1 - 1 / glm::distance(targetPos, position))) ;
    }
};

glm::vec2 Player::keepCohesion(){
    std::vector<Player*> closeTeamMates =  getAllPlayersInRange(OWN, 30.0);
    std::vector<glm::vec2> positions;
    for(Player* p : closeTeamMates){
        positions.push_back(p->getPos());
    }
    glm::vec2 center = FootballShape::center(position, positions);
    return center;
};


glm::vec2 Player::RandomLocation(){
  glm::vec2 pitchSize = pitch.getSize();
  glm::vec2 location = glm::vec2(ofRandom(0.0, pitchSize.x), ofRandom(0.0, pitchSize.y));
  return location;
}