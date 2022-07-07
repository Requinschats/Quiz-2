#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

TranslateMatrix::TranslateMatrix(float x_position,
                                 float y_position,
                                 float z_position,
                                 float x_size,
                                 float y_size,
                                 float z_size) {
    position.x = x_position;
    position.y = y_position;
    position.z = z_position;
    size.x = x_size;
    size.y = y_size;
    size.z = z_size;
}

void TranslateMatrix::bindTranslationMatrix(int *shaderProgram) {
    glm::mat4 translationMatrix =
            translate(mat4(1.0f),
                      vec3(position.x,
                           position.y,
                           position.z)) * scale(
                    mat4(1.0f),
                    vec3(size.x,
                         size.y,
                         size.z));
    GLuint worldMatrixLocation = glGetUniformLocation(*shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);
}
