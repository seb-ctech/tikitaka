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
    glm::vec2 RaycastScan(glm::vec2 origin, glm::vec2 to, std::vector<glm::vec2> positions, float angle, float radius);
    // TODO: glm::vec2 trianglePivots(std::vector<glm::vec2> Positions); // Get all possible Triangle pivot positons
    // https://math.stackexchange.com/questions/543961/determine-third-point-of-triangle-when-two-points-and-all-sides-are-known
    //TODO: glm::vec2 trios(std::vector<glm::vec2> Positions); // Get all possible trio positions of a group
    //float spaceArea(std::vector<glm::vec2> Positions); // Get the Area of the Space between the Positions. With Square area
    std::vector<glm::vec2> ScanSpace(glm::vec2 origin, Pitch pitch, std::vector<glm::vec2> positions);
} 