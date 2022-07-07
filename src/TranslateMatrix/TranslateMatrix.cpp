#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

TranslateMatrix::TranslateMatrix(float x_position,
                                 float y_position,
                                 float z_position,
                                 float x_scale,
                                 float y_scale,
                                 float z_scale) {
    position.x = x_position;
    position.y = y_position;
    position.z = z_position;
    scale.x = x_scale;
    scale.y = y_scale;
    scale.z = z_scale;
}

void TranslateMatrix::bindTranslationMatrix() {
    glm::mat4 translationMatrix =
            translate(mat4(1.0f),
                      vec3(position.x,
                           position.y,
                           position.z)) * scale(
                    mat4(1.0f),
                    vec3(scale.x,
                         scale.y,
                         scale.z));
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);
}
