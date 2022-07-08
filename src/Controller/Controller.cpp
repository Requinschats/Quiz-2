#include "Controller.h"
#include "../initialization/initialization.h"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

Controller::Controller(int *shaderProgram) {
    this->shaderProgram = shaderProgram;
    glm::mat4 initialProjectionMatrix = setInitialProjectionMatrix(this->shaderProgram);
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}

void Controller::setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp) {
    this->cameraPosition = cameraPosition;
    this->cameraLookAt = cameraLookAt;
    this->cameraUp = cameraUp;

    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(*this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Controller::reset() {
    this->cameraPosition = defaultCameraPosition;
    this->cameraLookAt = defaultCameraLookAt;
    this->cameraUp = defaultCameraUp;
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}
