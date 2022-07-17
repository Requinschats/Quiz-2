#include <glm/glm.hpp>
#pragma once

using namespace glm;

struct PhysicalPosition {
    float legRotationAngle;
    float armRotationAngle;
};

static PhysicalPosition physicalPositions[3] = {
    {-1, 0.0f},
    {1, 0.0f},
        {1, 0.0f}
};


class Movement {
public:
    vec3 position;
    int physicalPositionIndex;
    void nextMovement();
    Movement(vec3 position);
};
