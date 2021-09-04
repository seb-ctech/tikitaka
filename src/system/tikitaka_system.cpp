#include "tikitaka_system.h"

#define PPTM 10

Tikitaka::Tikitaka(){
    nAttacking = PPTM;
    nDefending = PPTM;
    playerAmount = nAttacking + nDefending;
    pitchSize = glm::vec2(100.0, 100.0);
    pitch = Pitch(pitchSize.x, pitchSize.y);
    units = SystemUnits(pitchSize);
}

void Tikitaka::init(){

    std::vector<glm::vec2> attpos = positions_4_3_3(ATTACK, 1.0, 1.0);
    std::vector<glm::vec2> defpos = positions_4_3_3(DEFENSE, 2.0, 3.0);
    for (int i = 0; i < nAttacking; i++){
        OffensivePlayer* newPlayer = new OffensivePlayer(attpos[i], pitch, i);
        players.push_back(newPlayer);
        attackers.push_back(newPlayer);
    }

    for (int i = 0; i < nDefending; i++){
        DefensivePlayer* newPlayer = new DefensivePlayer(defpos[i], pitch, PPTM + i);
        players.push_back(newPlayer);
        defenders.push_back(newPlayer);
    }
    for (Player* p : players){
        std::vector<Player*> attackingPlayers;
        std::vector<Player*> defendingPlayers;
        for (OffensivePlayer* op : attackers){
            attackingPlayers.push_back(op);
        }
        for (DefensivePlayer* dp : defenders){
            defendingPlayers.push_back(dp);
        }
        p->setMatch(attackingPlayers, defendingPlayers);
    }

    attackers[0]->ReceiveBall();

}

void Tikitaka::display(){
    ofSetBackgroundColor(3, 5, 5);
    for (int i = 0; i < playerAmount; i++){
        players[i]->display(units);
    }
}


void Tikitaka::update(){
    OffensivePlayer* BallCarry = getPlayerInPossession();
    for (Player* p : players){
        p->update(BallCarry);
    }
}

Players Tikitaka::getPlayerPositions(){
    Players player_positions;
    glm::vec2 attacking_players[PPTM];
    glm::vec2 defending_players[PPTM];
    player_positions.attacking = attacking_players;
    player_positions.defending = defending_players;
    player_positions.ballcarry = glm::vec2(20.0, 20.0);
    return player_positions;
}

std::vector<glm::vec2> Tikitaka::positions_4_3_3(Side side, float narrow, float compressed){
    std::vector<glm::vec2> positions;
    positions.reserve(10);
    float padding = 10.0;
    float width = pitch.getSize().y;
    float length = pitch.getSize().x;
    float w_spacing = width / (4.0 + narrow);
    float l_spacing = length * 0.5 / (3.0 + compressed);

    if(side == ATTACK){
        padding *= -1.0;
        l_spacing *= -1.0;
    }
            
    positions[0] = glm::vec2( 
        (length / 2.0) + padding,
        (width / 2.0)
    );
    positions[1] = glm::vec2( 
        (length / 2.0) + padding,
        (width / 2.0) - w_spacing
    );
    positions[2] = glm::vec2( 
        (length / 2.0) + padding,
        (width / 2.0) + w_spacing
    );
    // Second row
    positions[3] = glm::vec2( 
        positions[0].x + l_spacing,
        (width / 2.0)
    );
    positions[4] = glm::vec2( 
        positions[0].x + l_spacing,
        (width / 2.0) - w_spacing
    );
    positions[5] = glm::vec2( 
        positions[0].x + l_spacing,
        (width / 2.0) + w_spacing
    );
    // Third row
    positions[6] = glm::vec2( 
        positions[4].x + l_spacing,
        (width / 2.0) - (w_spacing / 2.0)
    );
    positions[7] = glm::vec2( 
        positions[4].x + l_spacing,
        positions[6].y - w_spacing
    );
    positions[8] = glm::vec2( 
        positions[4].x + l_spacing,
        (width / 2.0) + (w_spacing / 2.0)
    );
    positions[9] = glm::vec2( 
        positions[4].x + l_spacing,
        positions[8].y + w_spacing
    );

    return positions;
}

OffensivePlayer* Tikitaka::getPlayerInPossession(){
    for (OffensivePlayer* op : attackers){
        if (op->hasBall()){
            return op;
        }
    }
    return nullptr;
}