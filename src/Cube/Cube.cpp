#include "Cube.h"
#include "glm/ext/matrix_transform.hpp"
#include <array>
#include <glm/vec3.hpp>

////DEADCODE////

using namespace glm;
using namespace std;

static array<vec3, 12> getColorBufferData(float rgb1, float rgb2, float rgb3) {
    return {
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3),
            vec3(rgb1, rgb2, rgb3)
    };
}

static array<vec3, 8> vertices[] = {
        // front
        vec3(-1.0, -1.0, 1.0),
        vec3(1.0, -1.0, 1.0),
        vec3(1.0, 1.0, 1.0),
        vec3(-1.0, 1.0, 1.0),
        // back
        vec3(-1.0, -1.0, -1.0),
        vec3(1.0, -1.0, -1.0),
        vec3(1.0, 1.0, -1.0),
        vec3(-1.0, 1.0, -1.0)
};

GLuint elements[] = {
        // front
        0, 1, 2,
        2, 3, 0,
        // right
        1, 5, 6,
        6, 2, 1,
        // back
        7, 6, 5,
        5, 4, 7,
        // left
        4, 0, 3,
        3, 7, 4,
        // bottom
        4, 5, 1,
        1, 0, 4,
        // top
        3, 2, 6,
        6, 7, 3
};

static array<GLfloat, 36> getTexturesBufferData() {
    return {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
    };
}

Cube::Cube(float rgb1, float rgb2, float rgb3, RenderMode renderMode, bool isTextured) {
    this->renderMode_ = renderMode;
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->cubeVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->cubeVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices->front(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    //color buffer
    GLuint colorBuffer;
    array<vec3, 12> colorBufferData = getColorBufferData(rgb1 / 255, rgb2 / 255, rgb3 / 255);
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), &colorBufferData.front(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    if (isTextured) {
        GLuint aUVBuffer;
        array<float, 36> uvBufferData = getTexturesBufferData();
        glGenBuffers(1, &aUVBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, aUVBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uvBufferData), &uvBufferData, GL_STATIC_DRAW);
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, aUVBuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);
    }

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glBindVertexArray(0);

}

Cube::~Cube() {}

void Cube::Draw() {
    glBindVertexArray(this->cubeVAO_);
    glLineWidth(4.0f);
    glDrawElements(getGLRenderMode(), 36, GL_UNSIGNED_INT, 0);
}

int Cube::getGLRenderMode() {
    switch (this->renderMode_) {
        case RenderMode::points:
            return GL_POINTS;
        case RenderMode::lines:
            return GL_LINES;
        case RenderMode::triangles:
            return GL_TRIANGLES;
    }
}
