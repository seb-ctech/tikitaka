#pragma once
#include "ofMain.h"
#include "pitch.h"
#include <vector>

enum Side {
    ATTACK,
    DEFENSE
};

namespace FootballShape {
    //glm::vec2 trianglePivots(std::vector<glm::vec2> Positions); // Get all possible Triangle pivot positons
    //glm::vec2 trios(std::vector<glm::vec2> Positions); // Get all possible trio positions
    glm::vec2 center(glm::vec2 Origin, std::vector<glm::vec2> Positions); // Get the center between the Positions
    //float spaceArea(std::vector<glm::vec2> Positions); // Get the Area of the Space between the Positions
} 