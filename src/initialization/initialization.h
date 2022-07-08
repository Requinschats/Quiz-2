#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"

GLFWwindow *initializeWindow();

glm::mat4 setInitialProjectionMatrix(int shaderProgram);

void setDefaultWorldMatrix(int shaderProgram);
