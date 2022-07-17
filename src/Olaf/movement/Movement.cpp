#include "Movement.h"

Movement::Movement(vec3 position) {
    this->position = position;
    this->physicalPositionIndex = 1;
}

void Movement::nextMovement() {
    this->physicalPositionIndex++;
    if (physicalPositionIndex == (sizeof physicalPositions / sizeof physicalPositions[0])) {
        this->physicalPositionIndex = 0;
    }
}

PhysicalPosition Movement::getPhysicalPosition() {
    return physicalPositions[physicalPositionIndex];
}

void Movement::moveForward() {
    this->position.z += 1.0f;
    nextMovement();
}

void Movement::moveBackward() {
    this->position.z -= 1.0f;
    nextMovement();
}

void Movement::moveLeft() {
    this->position.x -= 1.0f;
    nextMovement();
}

void Movement::moveRight() {
    this->position.x += 1.0f;
    nextMovement();
}



