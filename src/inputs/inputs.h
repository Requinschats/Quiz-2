#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "../Cube/Cube.h"
#include "../Controller/Controller.h"
#include "../Olaf/movement/Movement.h"
#include "../TranslateMatrix/TranslateMatrix.h"

static void handleViewInputs(GLFWwindow *window,
                             int shaderProgram,
                             TranslateMatrix *translateMatrix,
                             float dt);

static void handleViewKeyboardInputs(GLFWwindow *window,
                                     int shaderProgram,
                                     TranslateMatrix *translateMatrix,
                                     float dt);

static void handleViewMouseInputs(GLFWwindow *window, TranslateMatrix *translateMatrix, float dt);

static void handleActionInputs(
        GLFWwindow *window,
        Movement *movement,
        float *olafScale,
        RenderMode *renderMode,
        bool *withTexture
);

static void handleControllers(GLFWwindow *window,
                              Controller *defaultController,
                              Controller *frontController,
                              Controller *backController);