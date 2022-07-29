#include "../Grid/Grid.h"
#include "glm/glm.hpp"
#include "inputs.h"

using namespace glm;
float cameraSpeed = 10.0f;

//separates concerns of keyboard and mouse inputs
void handleViewInputs(GLFWwindow *window,
                      int shaderProgram,
                      Controller *controller,
                      TranslateMatrix *translateMatrix,
                      float dt) {
    handleViewKeyboardInputs(window, shaderProgram, controller, translateMatrix, dt);
    handleViewMouseInputs(window, controller, translateMatrix, dt);
}

//maps key presses to new states
void handleViewKeyboardInputs(GLFWwindow *window,
                              int shaderProgram,
                              Controller *controller,
                              TranslateMatrix *translateMatrix,
                              float dt) {
    //close window on escape
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //reset view matrix on space press
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glm::mat4 viewMatrix = glm::mat4(1.0f);

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    //move camera left, right, forward, and back A,D,W,S
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        controller->cameraPosition.x -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        controller->cameraPosition.x += cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        controller->cameraPosition.z -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        controller->cameraPosition.z += cameraSpeed * dt;
    }
    // rotate around origin on q and e press
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        translateMatrix->setWorldRotationAngle(translateMatrix->rotationAngleYaxis + 5.0f);
    }
    //DEAD CODE
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        translateMatrix->rotationAngleXaxis -= 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        translateMatrix->rotationAngleXaxis += 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
        translateMatrix->rotationAngleZaxis -= 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
        translateMatrix->rotationAngleZaxis += 5.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        translateMatrix->setWorldRotationAngle(translateMatrix->rotationAngleYaxis - 5.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        controller->reset();
        translateMatrix->resetDefault();
    }
}

//maps mouse button presses to new states
void handleViewMouseInputs(GLFWwindow *window,
                           Controller *controller,
                           TranslateMatrix *translateMatrix,
                           float dt) {
    //start of press
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && controller->lastMouseState != "right") {
        controller->handleMouseRightClick(window);
    }
    //release
    if (controller->lastMouseState == "right" && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        controller->setCameraPositionFromMouse(window, dt);
    }
    //start of press
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS && controller->lastMouseState != "middle") {
        controller->handleMouseMiddleClick(window);
    }
    //release
    if (controller->lastMouseState == "middle" &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
        controller->handleZoom(window);
    }
}

// handles other keyboard inputs related to actions
void handleActionInputs(
        GLFWwindow *window,
        Movement *movement,
        float *olafScale,
        RenderMode *renderMode,
        bool *withTexture
) {
    //DEAD CODE
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        movement->position = vec3(Grid::getRandomGridCoordinate(), 0.0f, Grid::getRandomGridCoordinate());
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        *olafScale += 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        *olafScale -= 0.1f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        *renderMode = RenderMode::points;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        *renderMode = RenderMode::lines;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        *renderMode = RenderMode::triangles;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
        movement->incrementRotationAngle();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        movement->decrementRotationAngle();
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        *withTexture = false;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        *withTexture = true;
    }
}

void handleControllers(GLFWwindow *window,
                       Controller *activeController,
                       Controller *defaultController,
                       Controller *frontController,
                       Controller *backController) {
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        activeController = backController;
    }
}