#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Cube/Cube.h"
#include "../Controller/Controller.h"

void handleViewInputs(GLFWwindow *window,
                      int shaderProgram,
                      Controller *controller,
                      TranslateMatrix *translateMatrix,
                      float dt);

void handleViewKeyboardInputs(GLFWwindow *window,
                              int shaderProgram,
                              Controller *controller,
                              TranslateMatrix *translateMatrix,
                              float dt);

void handleViewMouseInputs(GLFWwindow *window, Controller *controller, TranslateMatrix *translateMatrix, float dt);

void handleActionInputs(
        GLFWwindow *window,
        float *olafXPosition,
        float *olafZPosition,
        float *olafScale,
        RenderMode *renderMode,
        float *olafRotationAngle
);