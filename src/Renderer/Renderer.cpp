#include "Renderer.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

void Renderer::setTranslationMatrix(int *shaderProgram, TranslateMatrix translateMatrix) {
    GLuint worldMatrixLocation = glGetUniformLocation(*shaderProgram, "worldMatrix");
    mat4 translationMatrix =
            translate(mat4(1.0f),
                      vec3(5.0f,// x position
                           10.0f, //y position
                           1.0f)) * scale( // z position
                    mat4(1.0f),
                    vec3(1.0f, //x scale
                         1.0f, //y scale
                         1.0f) //z scale
            );
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);
}
