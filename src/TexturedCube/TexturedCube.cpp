#include "TexturedCube.h"

#include <array>
#include <GL/glew.h>

using namespace std;

static array<GLfloat, 36> getTexturedColorBufferData(float rgb1, float rgb2, float rgb3) {
    return {
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3,
            rgb1, rgb2, rgb3
    };
}

GLfloat textured_vertices[] = {
        // front
        -1.0, -1.0, 1.0,
        1.0, -1.0, 1.0,
        1.0, 1.0, 1.0,
        -1.0, 1.0, 1.0,
        // back
        -1.0, -1.0, -1.0,
        1.0, -1.0, -1.0,
        1.0, 1.0, -1.0,
        -1.0, 1.0, -1.0
};

GLuint textured_elements[] = {
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

TexturedCube::TexturedCube(float rgb1, float rgb2, float rgb3, RenderMode renderMode) {
    this->renderMode_ = renderMode;
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->cubeVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->cubeVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textured_vertices), textured_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

    //color buffer
    GLuint colorBuffer;
    array<float, 36> colorBufferData = getTexturedColorBufferData(rgb1 / 255, rgb2 / 255, rgb3 / 255);
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBufferData), &colorBufferData, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    GLuint indexBufferObject;
    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textured_elements), textured_elements, GL_STATIC_DRAW);

    glBindVertexArray(0);

}

TexturedCube::~TexturedCube() {}

void TexturedCube::Draw() {
    glBindVertexArray(this->cubeVAO_);
    glLineWidth(4.0f);
    glDrawElements(getGLRenderMode(), 36, GL_UNSIGNED_INT, 0);
}

int TexturedCube::getGLRenderMode() {
    switch (this->renderMode_) {
        case RenderMode::points:
            return GL_POINTS;
        case RenderMode::lines:
            return GL_LINES;
        case RenderMode::triangles:
            return GL_TRIANGLES;
    }
}
