#pragma once
#include "ofMain.h"
#include "pitch.h"
#include "helper_math.h"
#include <vector>

enum Side {
    ATTACK,
    DEFENSE
};

namespace FootballShape {
    glm::vec2 RaycastScan(glm::vec2 origin, Pitch* pitch, std::vector<glm::vec2> positions, float angle, float radius);
    glm::vec2 RaycastTo(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float radius);
    std::vector<glm::vec2> RaycastToMany(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float radius, int max = 0);
    std::vector<glm::vec2> TrianglePivots(std::vector<glm::vec2> PositionPair);
    void Pairs(std::vector<glm::vec2> Positions, std::vector<std::vector<glm::vec2>> &groupList);
    glm::vec2 getClosestPositionFromSelection(std::vector<glm::vec2> options, glm::vec2 target);
} 