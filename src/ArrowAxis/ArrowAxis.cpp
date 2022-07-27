#include "GL/glew.h"
#include "ArrowAxis.h"
#include "../initialization/initialization.h"

const GLfloat axisVertices[] = {
        0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //position, color
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, //arrow
        4.5f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
        5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        4.5f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //line
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, //arrow
        0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, //line
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f, //arrow
        0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
};

ArrowAxis::ArrowAxis() {
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->arrowAxisVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->arrowAxisVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

void ArrowAxis::Draw(TranslateMatrix *translateMatrix, GLuint shaderProgram) {
    translateMatrix->setPosition(-5.0f, 0.0f, -5.0f);
    translateMatrix->setDefaultSize();
    translateMatrix->bindTranslationMatrix(shaderProgram);
    glBindVertexArray(this->arrowAxisVAO_);
    glDrawArrays(GL_LINES, 0, 18);
    glBindVertexArray(0);
}