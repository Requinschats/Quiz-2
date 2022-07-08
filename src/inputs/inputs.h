#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

void handleViewInputs(GLFWwindow *window, int shaderProgram, glm::vec3 *cameraPosition, glm::vec3 *cameraLookAt,
                      glm::vec3 *cameraUp, float dt);

void handleActionInputs(GLFWwindow *window, float *olafXPosition, float *olafZPosition);