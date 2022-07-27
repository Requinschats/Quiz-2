#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Cube/Cube.h"
#include "../Controller/Controller.h"
#include "../Olaf/movement/Movement.h"
#include "../TranslateMatrix/TranslateMatrix.h"

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
        Movement *movement,
        float *olafScale,
        RenderMode *renderMode,
        bool *withTexture
);

void handleControllers(GLFWwindow *window,
                       Controller *activeController,
                       Controller *defaultController,
                       Controller *frontController,
                       Controller *backController);