#include <glm/glm.hpp>

#pragma once

using namespace glm;

struct PhysicalPosition {
    float legRotationAngle;
    float armXRotationAngle;
    float armZRotationAngle;
};

static PhysicalPosition physicalPositions[4] = {
        {0,   0,   0},
        {120, 120, 60},
        {0,   0,   0},
        {240, 240, 320}
};


class Movement {
public:
    vec3 position;
    int physicalPositionIndex;

    void nextMovement();

    Movement(vec3 position);

    void moveForward();

    void moveBackward();

    void moveLeft();

    void moveRight();

    PhysicalPosition getPhysicalPosition();
};
