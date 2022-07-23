#include <string>
#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "GLFW/glfw3.h"
#include "glm/detail/type_mat4x4.hpp"

#pragma once


using namespace glm;
using namespace std;

class Controller {
public:
    Controller(int *shaderProgram);

    ~Controller();

    void reset();

    void setShader(int *shaderProgram);

    void setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp);

    mat4 rotateYAxis(float degreeOfRotation);

    void setCameraPosition();

    void setCameraPositionFromMouse(GLFWwindow *window, float dt);

    void setMousePosition(GLFWwindow *window);

    void handleMouseRightClick(GLFWwindow *window);

    void handleMouseMiddleClick(GLFWwindow *window);

    void zoomOutFromMouse(GLFWwindow *window);

    void setInitialProjectionMatrix(int shaderProgram);

    vec3 cameraPosition;
    vec3 cameraLookAt;
    string lastMouseState;
    vec3 cameraUp;
    vec3 mousePosition;
    float cameraHorizontalAngle;
    float cameraVerticalAngle;
    int shaderProgram;
    float projectionMatrixViewField;

    void handleZoom(GLFWwindow *window);

private:
    void setDefaultLookAt();

    void normalizeCameraHorizontalAngle();

    void setProjectionMatrix(int shaderProgram, float projectionMatrix);

    void zoomInFromMouse(GLFWwindow *window);

};