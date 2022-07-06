

#ifndef A1_INITIALIZATION_H
#define A1_INITIALIZATION_H

#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"

GLFWwindow *initializeWindow();

glm::mat4 setInitialProjectionMatrix(int *shaderProgram);

void setCameraPosition(int *shaderProgram, glm::vec3 *cameraPosition, glm::vec3 *cameraLookAt, glm::vec3 *cameraUp);

void setDefaultWorldMatrix(int shaderProgram);

#endif //A1_INITIALIZATION_H
