#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Controller/Controller.h"

void handleViewInputs(GLFWwindow *window,
                      int shaderProgram,
                      Controller *controller,
                      TranslateMatrix *translateMatrix,
                      float dt);

void handleActionInputs(GLFWwindow *window, float *olafXPosition, float *olafZPosition, float *olafScale);