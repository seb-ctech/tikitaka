#pragma once
#include "ofMain.h"
#include "pitch.h"
#include <vector>

enum Side {
    ATTACK,
    DEFENSE
};

namespace FootballShape {
    void triangles();
    glm::vec2 center(glm::vec2 Origin, std::vector<glm::vec2> Positions);
} 