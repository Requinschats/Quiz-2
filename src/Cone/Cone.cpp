#include "Cone.h"
#include <iostream>
#include "../objectLoader/ObjectLoader.h"

using namespace std;

Cone::Cone() {
    string cubePath = "assets/models/cone.obj";

    int cubeVertices;
    GLuint cubeVAO = setupModelEBO(cubePath, cubeVertices);

    this->cubeVAO = cubeVAO;
    this->cubeVertices = cubeVertices;
}

Cone::~Cone() {}

void Cone::draw() {
    glBindVertexArray(this->cubeVAO);
    glDrawElements(GL_TRIANGLES, cubeVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

