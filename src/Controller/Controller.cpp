#include "Controller.h"
#include "../initialization/initialization.h"
#include "GLFW/glfw3.h"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/matrix_clip_space.hpp"

const vec3 defaultCameraPosition = vec3(-15.6f, 10.0f, 10.0f);
const vec3 defaultCameraLookAt = vec3(0.5f, 0.0f, -1.0f);
const vec3 defaultCameraUp = vec3(0.0f, 1.0f, 0.0f);

Controller::Controller(int *shaderProgram) {
    this->shaderProgram = *shaderProgram;
    this->lastMouseState = "";
    this->setCameraPosition(defaultCameraPosition, defaultCameraLookAt, defaultCameraUp);
    this->setDefaultLookAt();
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

void Controller::setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp) {
    this->cameraPosition = cameraPosition;
    this->cameraLookAt = cameraLookAt;
    this->cameraUp = cameraUp;

    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Controller::setCameraPosition() {
    mat4 viewMatrix = lookAt(this->cameraPosition,
                             this->cameraPosition + this->cameraLookAt,  // center
                             this->cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(this->shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}

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

void Controller::setMousePosition(GLFWwindow *window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    this->mousePosition.x = xpos;
    this->mousePosition.y = ypos;
}

void Controller::handleMouseRightClick(GLFWwindow *window) {
    this->setMousePosition(window);
    this->lastMouseState = "right";
}

void Controller::handleMouseMiddleClick(GLFWwindow *window) {
    this->setMousePosition(window);
    this->lastMouseState = "middle";
}

void Controller::normalizeCameraHorizontalAngle() {
    if (this->cameraHorizontalAngle > 360) {
        this->cameraHorizontalAngle -= 360;
    } else if (cameraHorizontalAngle < -360) {
        this->cameraHorizontalAngle += 360;
    }
}

void Controller::setDefaultLookAt() {
    this->cameraHorizontalAngle = 30.0f;
    this->cameraVerticalAngle = 0.0f;

    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);
    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    this->cameraPosition -= cameraSideVector * 1.0f;
    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);
}

void Controller::setCameraPositionFromMouse(GLFWwindow *window, float dt) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    double dx = mousePosX - this->mousePosition.x;
    double dy = mousePosY - this->mousePosition.y;

    const float cameraAngularSpeed = 6.0f;

    this->cameraHorizontalAngle -= dx * cameraAngularSpeed * dt;
    this->cameraVerticalAngle -= dy * cameraAngularSpeed * dt;

    this->cameraVerticalAngle = std::max(-85.0f, std::min(85.0f, this->cameraVerticalAngle));
    this->normalizeCameraHorizontalAngle();

    float theta = radians(this->cameraHorizontalAngle);
    float phi = radians(this->cameraVerticalAngle);

    this->cameraLookAt = vec3(cosf(phi) * cosf(theta), sinf(phi), -cosf(phi) * sinf(theta));
    vec3 cameraSideVector = glm::cross(this->cameraLookAt, vec3(0.0f, 1.0f, 0.0f));
    glm::normalize(cameraSideVector);

    this->cameraPosition -= cameraSideVector * 1.0f * dt;

    this->setCameraPosition(this->cameraPosition, this->cameraLookAt, this->cameraUp);

    this->mousePosition.x = mousePosX;
    this->mousePosition.y = mousePosY;
    this->lastMouseState = "";
}

void Controller::handleZoom(GLFWwindow *window) {
    double mousePosX, mousePosY;
    glfwGetCursorPos(window, &mousePosX, &mousePosY);
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