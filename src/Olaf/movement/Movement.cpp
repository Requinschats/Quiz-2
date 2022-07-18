#include <cstdio>
#include "Movement.h"

Movement::Movement(vec3 position) {
    this->position = position;
    this->physicalPositionIndex = 0;
    this->rotationAngle = 0;
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
    this->position.x = this->position.x + this->getDirectionVector(this->rotationAngle).x;
    this->position.z = this->position.z + this->getDirectionVector(this->rotationAngle).z;
    nextMovement();
}

void Movement::moveBackward() {
    this->position.x = this->position.x - this->getDirectionVector(this->rotationAngle).x;
    this->position.z = this->position.z - this->getDirectionVector(this->rotationAngle).z;
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

vec3 Movement::getDirectionVector(float angle) {
    float radians = angle * (M_PI / 180);
    float x = cos(radians);
    float z = sin(radians);
    return vec3(x, 0, z);

}

