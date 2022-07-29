#include "Cone.h"
#include <iostream>
#include "../objectLoader/ObjectLoader.h"

using namespace std;

// a simple objectloader class that loads the cone wavefront obj in a vao and displays the elements.
Cone::Cone() {
    //path to the asset
    string cubePath = "assets/models/cone.obj";

    int cubeVertices;
    //loader from the labs
    GLuint cubeVAO = setupModelEBO(cubePath, cubeVertices);

    this->cubeVAO = cubeVAO;
    this->cubeVertices = cubeVertices;
}

Cone::~Cone() {}

//draw call to display the vertices from the model
void Cone::draw() {
    glBindVertexArray(this->cubeVAO);
    glDrawElements(GL_TRIANGLES, cubeVertices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

