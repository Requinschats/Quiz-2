#include "Controller.h"
#include "../initialization/initialization.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

const vec3 defaultCameraPosition = vec3(5.6f, 10.0f, 40.0f);
const vec3 defaultCameraLookAt = vec3(0, 0.0f, 0);
const vec3 defaultCameraUp = vec3(0.0f, 1.0f, 0.0f);

// Constructor that sets the camera position, look at, up vectors and projection matrix to default values.
Controller::Controller(int *shaderProgram) {
    this->shaderProgram = *shaderProgram;
    //required to trigger mouse click action once
    this->lastMouseState = "";
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
    this->setDefaultLookAt();
    //set projection matrix to default values
    setInitialProjectionMatrix(this->shaderProgram);
}

void Controller::setShader(int *shaderProgram) {
    this->shaderProgram = *shaderProgram;
    this->setCameraPosition();
    setProjectionMatrix(this->shaderProgram, projectionMatrixViewField);
}

void Controller::setInitialProjectionMatrix(int shaderProgram) {
    this->projectionMatrixViewField = 90;
    mat4 projectionMatrix = glm::perspective(glm::radians(projectionMatrixViewField),  // field of view in degrees
                                             800.0f / 600.0f,      // aspect ratio
                                             0.01f, 500.0f);       // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Controller::setProjectionMatrix(int shaderProgram, float projectionViewField) {
    mat4 projectionMatrix = glm::perspective(glm::radians(projectionViewField),  // field of view in degrees
                                             800.0f / 600.0f,      // aspect ratio
                                             0.01f, 500.0f);       // near and far (near > 0)
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
}

// Wrapper that sets the camera position, look at, up vectors and projection matrix.
void Controller::setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp) {
    this->cameraPosition = cameraPosition;
    this->cameraLookAt = cameraLookAt;
    this->cameraUp = cameraUp;
//position of the camera is the eye position
    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    //sets the corresponding uniform (viewMatrix) variable in the shader program
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

//binds the controller to the screen
void Controller::setCameraPosition() {
    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    //sets the corresponding uniform (viewMatrix) variable in the shader program
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

// resets the camera position, look at, up vectors to default values.
void Controller::reset() {
    this->cameraPosition = defaultCameraPosition;
    this->setDefaultLookAt();
    this->cameraUp = defaultCameraUp;
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
}

glm::mat4 Controller::rotateYAxis(float degreeOfRotation) {
    return glm::rotate(glm::mat4(1.0f),
                       glm::radians(degreeOfRotation),
                       glm::vec3(0, 1, 0));
}

// sets mouse position to passed in values.
void Controller::setMousePosition(GLFWwindow *window) {
    double xpos, ypos;
    //gl utility that gets the mouse position x and y coordinates
    glfwGetCursorPos(window, &xpos, &ypos);
    this->mousePosition.x = xpos;
    this->mousePosition.y = ypos;
}

//called when the mouse right button is pressed. Sets the state for the release of the button
void Controller::handleMouseRightClick(GLFWwindow *window) {
    this->setMousePosition(window);
    //right refers to mouse right button
    this->lastMouseState = "right";
}

//called when the mouse left button is pressed. Sets the state for the release of the button
void Controller::handleMouseMiddleClick(GLFWwindow *window) {
    this->setMousePosition(window);
    //middle refers to mouse middle button
    this->lastMouseState = "middle";
}

// keeps the horizontal angle between 0 and 360 degrees.
void Controller::normalizeCameraHorizontalAngle() {
    if (this->cameraHorizontalAngle > 360) {
        this->cameraHorizontalAngle -= 360;
    } else if (cameraHorizontalAngle < -360) {
        this->cameraHorizontalAngle += 360;
    }
}

// from lab 3, it converts camera horizontal angle to a rotation matrix.
void Controller::setDefaultLookAt() {
    // default values in degrees
    this->cameraHorizontalAngle = 70.0f;
    this->cameraVerticalAngle = 0.0f;

    // clamp the vertical angle to -85 to 85 degrees
    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    // conversion to radians
    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);
    //conversion to spherical coordinates
    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    //sets the controller state base on the new values.
    this->cameraPosition -= cameraSideVector * 1.0f;
    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);
}

// similar to setDefaultLookAt, but uses the delta vector of the mouse to rotate the camera.
void Controller::setCameraPositionFromMouse(GLFWwindow *window, float dt) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    // calculate the change in mouse position
    double dx = mousePosX - this->mousePosition.x;
    double dy = mousePosY - this->mousePosition.y;

    //rotation speed, I prefer a lower speed
    const float cameraAngularSpeed = 6.0f;
//set new angles from the delta vector of the mouse
    this->cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    this->cameraVerticalAngle -= dy * cameraAngularSpeed * dt;
// clamp the vertical angle to [-85, 85] degrees
    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    // convert to radians
    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);

    //conversion to spherical coordinates
    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    this->cameraPosition -= cameraSideVector * 1.0f * dt;

    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);
//sets new state after rotation
    this->mousePosition.x = mousePosX;
    this->mousePosition.y = mousePosY;
    this->lastMouseState = "";
}

//zoom in and out after releasing the scroll wheel and moving the mouse.
void Controller::handleZoom(GLFWwindow *window) {
    double mousePosX, mousePosY;
    //opengl utility that gets the mouse position x and y coordinates
    glfwGetCursorPos(window, &mousePosX, &mousePosY);
    // y mouse movement delta * sensitivity. Again, I prefer a lower sensitivity.
    double dy = mousePosY - this->mousePosition.y;
    if (dy > 0) {
        zoomOutFromMouse(window);
    } else if (dy < 0) {
        zoomInFromMouse(window);
    }
    this->lastMouseState = "";
}

void Controller::zoomOutFromMouse(GLFWwindow *window) {
    bool hasReachedMaxViewField = this->projectionMatrixViewField > 160;
    if (!hasReachedMaxViewField) {
        this->projectionMatrixViewField += 10;
        setProjectionMatrix(this->shaderProgram, projectionMatrixViewField);
    }
}

void Controller::zoomInFromMouse(GLFWwindow *window) {
    bool hasReachedMinViewField = this->projectionMatrixViewField < 10;
    if (!hasReachedMinViewField) {
        this->projectionMatrixViewField -= 10;
        setProjectionMatrix(this->shaderProgram, projectionMatrixViewField);
    }
}

Controller::~Controller() {

}

void Controller::applyController() {
//    shaders
    setCameraPosition();
}
