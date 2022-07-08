#include "Grid.h"
#include "../TranslateMatrix/TranslateMatrix.h"
#include "random"

using namespace std;

const GLfloat vertices[] = {
        0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        -0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, 0.5f, 0.75f, 1.0f, 0.5f, 1.0f,
        0.5f, 0.0f, -0.5f, 0.75f, 1.0f, 0.5f, 1.0f
};

Grid::Grid(int *shaderProgram) {
    this->shaderProgram = shaderProgram;
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->gridVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->gridVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);
}

void Grid::Draw() {
    for (int i = -50; i < 50; i++) {
        for (int j = -50; j < 50; j++) {
            TranslateMatrix *gridTranslateMatrix = new TranslateMatrix(i,
                                                                       0.0f,
                                                                       j,
                                                                       1.0f,
                                                                       1.0f,
                                                                       1.0f);
            gridTranslateMatrix->bindTranslationMatrix(this->shaderProgram);

            glBindVertexArray(this->gridVAO_);
            glLineWidth(6.0f);
            glDrawArrays(GL_LINES, 0, 8);
            glBindVertexArray(0);
        }
    }
}

int Grid::getRandomGridCoordinate() {
    random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distribution(-50, 50);
    return distribution(gen);
}

