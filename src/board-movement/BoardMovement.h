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

//initialize the board movement to default values

BoardMovement::BoardMovement(vec3 position) {
    this->position = position;
    this->rotationAngle = 0;
}

//DEAD CODE

void BoardMovement::moveForward() {
    this->position.x = this->position.x + this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z + this->getDirectionVector(rotationAngle).z;
}

void BoardMovement::moveBackward() {
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle).z;
}

//update positions based on the computed direction vector and the rotation angle

void BoardMovement::moveLeft() {
    //-90 degrees is the angle of the left side of the board
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle - 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle - 90).z;
}

void BoardMovement::moveRight() {
    //90 degrees is the angle of the right side of the board
    this->position.x = this->position.x - this->getDirectionVector(rotationAngle + 90).x;
    this->position.z = this->position.z - this->getDirectionVector(rotationAngle + 90).z;
}

//computes the direction vector for the given angle and allows moving in the sense of the skateboard
vec3 BoardMovement::getDirectionVector(float angle) {
    float radians = angle * (M_PI / 180);
    //find each component of the direction vector
    float x = sin(radians);
    float z = cos(radians);
    return vec3(x, 0, z);

}


