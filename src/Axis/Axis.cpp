#include "GL/glew.h"
#include "Axis.h"

const GLfloat vertices[] =
        {
                0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                4.5f, 0.0f, 0.2f, 1.0f, 0.0f, 0.0f, 1.0f,
                5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                4.5f, 0.0f, -0.2f, 1.0f, 0.0f, 0.0f, 1.0f,

                0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                -0.2f, 4.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

                0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
                0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                -0.2f, 0.0f, 4.5f, 0.0f, 0.0f, 1.0f, 1.0f,
        };

Axis::Axis() {
    GLuint VertexBufferObject;

    glGenVertexArrays(1, &this->axisVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->axisVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

Axis::~Axis() {}

void Axis::Draw() {
    glBindVertexArray(this->axisVAO_);

    glEnable(GL_LINE_SMOOTH);
    glLineWidth(4.0f);
    glDrawArrays(GL_LINES, 0, 3 * 2);
    glDrawArrays(GL_LINES, 6, 3 * 2);
    glDrawArrays(GL_LINES, 12, 3 * 2);
    glLineWidth(0.5f);

    glBindVertexArray(0);
}