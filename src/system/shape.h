#pragma once
#include "ofMain.h"
#include "pitch.h"
#include <vector>

enum Side {
    ATTACK,
    DEFENSE
};

namespace FootballShape {
    // TODO: Raycasting
    // TODO: glm::vec2 trianglePivots(std::vector<glm::vec2> Positions); // Get all possible Triangle pivot positons
    // https://math.stackexchange.com/questions/543961/determine-third-point-of-triangle-when-two-points-and-all-sides-are-known
    //TODO: glm::vec2 trios(std::vector<glm::vec2> Positions); // Get all possible trio positions of a group
    glm::vec2 center(glm::vec2 Origin, std::vector<glm::vec2> Positions); // Get the center between the Positions
    //float spaceArea(std::vector<glm::vec2> Positions); // Get the Area of the Space between the Positions. With Square area
} 