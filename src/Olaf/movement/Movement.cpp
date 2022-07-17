#include "Movement.h"

Movement::Movement(vec3 position) {
    this->position = position;
    this->physicalPositionIndex = 1;
}

void Movement::nextMovement() {
    this->physicalPositionIndex++;
    if(physicalPositionIndex == (sizeof physicalPositions / sizeof physicalPositions[0])) {
        this->physicalPositionIndex = 0;
    }
}
