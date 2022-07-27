#include "../Grid/Grid.h"
#include "inputs.h"

#include <iostream>

using namespace glm;
float cameraSpeed = 5.0f;

static void handleViewInputs(GLFWwindow *window,
                             int shaderProgram,
                             TranslateMatrix *translateMatrix,
                             float dt) {
    handleViewKeyboardInputs(window, shaderProgram, translateMatrix, dt);
    handleViewMouseInputs(window, translateMatrix, dt);
}

static void handleViewKeyboardInputs(GLFWwindow *window,
                                     int shaderProgram,
                                     TranslateMatrix *translateMatrix,
                                     float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glm::mat4 viewMatrix = glm::mat4(1.0f);

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        activeController->cameraPosition.x -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        activeController->cameraPosition.x += cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        activeController->cameraPosition.z -= cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        activeController->cameraPosition.z += cameraSpeed * dt;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        translateMatrix->setWorldRotationAngle(translateMatrix->rotationAngleYaxis + 5.0f);
    }
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
        activeController->reset();
        translateMatrix->resetDefault();
    }
}

static void handleViewMouseInputs(GLFWwindow *window,
                                  TranslateMatrix *translateMatrix,
                                  float dt) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
        activeController->lastMouseState != "right") {
        activeController->handleMouseRightClick(window);
    }
    if (activeController->lastMouseState == "right" &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        activeController->setCameraPositionFromMouse(window, dt);
    }
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS &&
        activeController->lastMouseState != "middle") {
        activeController->handleMouseMiddleClick(window);
    }
    if (activeController->lastMouseState == "middle" &&
        glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE) {
        activeController->handleZoom(window);
    }
}

static void handleActionInputs(
        GLFWwindow *window,
        Movement *movement,
        float *olafScale,
        RenderMode *renderMode,
        bool *withTexture
) {
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
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        movement->moveForward();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        movement->moveBackward();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        movement->moveLeft();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        movement->moveRight();
    }
}

static void handleControllers(GLFWwindow *window,
                              Controller *defaultController,
                              Controller *frontController,
                              Controller *backController) {
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        //print to screen "back"
        std::cout << "back" << std::endl;
        setActiveController(backController);
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
        setActiveController(frontController);
    }
    if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS) {
        setActiveController(defaultController);
    }
}