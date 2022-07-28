#include "Sphere.h"
#include <iostream>
#include "../objectLoader/ObjectLoader.h"

using namespace std;

Sphere::Sphere() {
    string cubePath = "assets/models/sphere.obj";

    int cubeVertices;
    GLuint cubeVAO = setupModelEBO(cubePath, cubeVertices);

    this->cubeVAO = cubeVAO;
    this->cubeVertices = cubeVertices;
}

Sphere::~Sphere() {
}

void Sphere::draw() {
    glBindVertexArray(this->cubeVAO);
    glDrawElements(GL_TRIANGLES, cubeVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

