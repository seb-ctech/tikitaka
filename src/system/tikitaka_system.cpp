#include "tikitaka_system.h"
#define PPTM 11

Tikitaka::Tikitaka(){
    int playerAmount = 10; 
    int nAttacking = glm::round(playerAmount/2);
    int nDefending = glm::round(playerAmount/2);
}

void Tikitaka::init(){
    TestPlayer = Agent();
}

void Tikitaka::display(){
    TestPlayer.display();
}


void Tikitaka::update(){
    TestPlayer.update();
}

Players Tikitaka::getPlayerPositions(){
    Players player_positions;
    glm::vec2 attacking_players[5];
    glm::vec2 defending_players[5];
    player_positions.attacking = attacking_players;
    player_positions.defending = defending_players;
    player_positions.playerWithBall = glm::vec2(20.0, 20.0);
    return player_positions;
}