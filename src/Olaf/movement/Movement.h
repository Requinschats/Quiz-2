#include <glm/glm.hpp>
#pragma once

using namespace glm;

struct PhysicalPosition {
    float legRotationAngle;
    float armRotationAngle;
};

static PhysicalPosition physicalPositions[3] = {
    {120, 120},
    {240, 240},
    {360, 360}
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
};
