#include <glm/glm.hpp>

#pragma once

using namespace glm;

class BoardMovement {
public:
    BoardMovement(vec3 position);

    vec3 position;
    int rotationAngle;

    vec3 getDirectionVector(float angle);

    void moveRight();

    void moveLeft();

    void moveBackward();

    void moveForward();
};

BoardMovement::BoardMovement(vec3 position) {
    this->position = position;
    this->rotationAngle = 0;
}

void BoardMovement::moveForward() {
    this->position.x = this->position.x + this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z + this->getDirectionVector(rotationAngle).z;
}

void BoardMovement::moveBackward() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle).z;
}

void BoardMovement::moveLeft() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle - 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle - 90).z;
}

void BoardMovement::moveRight() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle + 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle + 90).z;
}

vec3 BoardMovement::getDirectionVector(float angle) {
    float radians = angle * (M_PI / 180);
    float x = sin(radians);
    float z = cos(radians);
    return vec3(x, 0, z);

}


