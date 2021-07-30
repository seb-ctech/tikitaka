#include "tikitaka_system.h"

#define PPTM 11

Tikitaka::Tikitaka(){
    nAttacking = PPTM;
    nDefending = PPTM;
    playerAmount = nAttacking + nDefending;
    players = new Agent[playerAmount];
    pitchSize = glm::vec2(100.0, 100.0);
    pitch = Pitch(pitchSize.x, pitchSize.y);
    units = SystemUnits(pitchSize);
}

void Tikitaka::init(){
    TestPlayer = Agent(pitch);
    for (int i = 0; i < nAttacking; i++){
        players[i] = OffensivePlayer(pitch);
    }

    for (int i = 0; i < nDefending; i++){
        players[nAttacking + i] = DefensivePlayer(pitch);
    }

}

void Tikitaka::display(){
    TestPlayer.display(units);
    for (int i = 0; i < playerAmount; i++){
        players[i].display(units);
    }
}


void Tikitaka::update(){
    TestPlayer.update();
    for (int i = 0; i < playerAmount; i++){
        players[i].update();
    }
}

Players Tikitaka::getPlayerPositions(){
    Players player_positions;
    glm::vec2 attacking_players[PPTM];
    glm::vec2 defending_players[PPTM];
    player_positions.attacking = attacking_players;
    player_positions.defending = defending_players;
    player_positions.playerWithBall = glm::vec2(20.0, 20.0);
    return player_positions;
}