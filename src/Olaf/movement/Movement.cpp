#include <cstdio>
#include "Movement.h"

Movement::Movement(vec3 position) {
    this->position = position;
    this->physicalPositionIndex = 0;
    this->rotationAngle = 0;
}

void Movement::incrementRotationAngle() {
    rotationAngle += 10.0f;
    if (rotationAngle > 360.0f) {
        rotationAngle = 0.0f;
    }
}

void Movement::decrementRotationAngle() {
    this->rotationAngle -= 10.0f;
    if (this->rotationAngle < 0.0f) {
        this->rotationAngle = 360.0f;
    }
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
    this->position.x = this->position.x + this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z + this->getDirectionVector(rotationAngle).z;
    nextMovement();
}

void Movement::moveBackward() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle).z;
    nextMovement();
}

void Movement::moveLeft() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle - 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle - 90).z;
    nextMovement();
}

void Movement::moveRight() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle + 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle + 90).z;
    nextMovement();
}

vec3 Movement::getDirectionVector(float angle) {
    float radians = angle * (M_PI / 180);
    float x = sin(radians);
    float z = cos(radians);
    return vec3(x, 0, z);

}

