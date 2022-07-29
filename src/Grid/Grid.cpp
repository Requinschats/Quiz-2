#include "Grid.h"
#include "random"
#include "glm/glm.hpp"

using namespace std;
using namespace glm;

// [0,2]: position, [3,5]: normals, [6,8]: UV coordinates. Larger than 1 to repeat the texture 20 times per square.
const GLfloat vertices[] = {
        //bottom
        -0.5f, 0.0f, -0.5f, 0, 1.0f, 0, 0, 0,
        -0.5f, 0.0f, 0.5f, 0, 1.0f, 0, 0, 20,
        0.5f, 0.0f, 0.5f, 0, 1.0f, 0, 20, 20,

        0.5f, 0.0f, 0.5f, 0, 1.0f, 0, 20, 20,
        0.5f, 0.0f, -0.5f, 0, 1.0f, 0, 20, 0,
        -0.5f, 0.0f, -0.5f, 0, 1.0f, 0, 0, 0
};

Grid::Grid(int shaderProgram) {
    // Generate a buffer object to store the vertex data on the GPU
    this->shaderProgram = shaderProgram;
    GLuint VertexBufferObject;
    glGenVertexArrays(1, &this->gridVAO_);
    glGenBuffers(1, &VertexBufferObject);

    glBindVertexArray(this->gridVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// Dictates the layout of the vertex data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,                            // attribute 2 matches aUV in Vertex Shader
                          2,
                          GL_FLOAT,
                          GL_FALSE,
                          8 * sizeof(float),
                          (void *) (6 *
                                    sizeof(float)));      // uv is offseted by 2 vec3 (comes after position and color)



    glBindVertexArray(0);
}

void Grid::Draw(TranslateMatrix *translateMatrix) {
    float color[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    for (int i = -2; i < 2; i++) {
        for (int j = -2; j < 2; j++) {
            translateMatrix->setPosition(i, 0.0f, j);
            //larger size to properly see the texture
            translateMatrix->setSize(220.0f, 0.5, 220.0f);
            translateMatrix->bindTranslationMatrix(this->shaderProgram);

            glBindVertexArray(this->gridVAO_);
            glLineWidth(0.0f);
            // Draw what is stored in the buffer with lines
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
}

//DEAD CODE
int Grid::getRandomGridCoordinate() {
    random_device randomDevice;
    std::mt19937 gen(randomDevice());
    //[-50,50] matches the range of the grid, look at range in Draw()
    std::uniform_int_distribution<> distribution(-50, 50);
    return distribution(gen);
}

