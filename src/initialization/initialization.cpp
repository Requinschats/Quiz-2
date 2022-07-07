#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

GLFWwindow *initializeWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }
    return window;
}

glm::mat4 setInitialProjectionMatrix(int *shaderProgram) {
    glm::mat4 projectionMatrix = glm::perspective(glm::radians(80.0f),  // field of view in degrees
                                                  800.0f / 600.0f,      // aspect ratio
                                                  0.01f, 100.0f);       // near and far (near > 0)

    GLuint projectionMatrixLocation = glGetUniformLocation(*shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]);
    return projectionMatrix;
}


void setDefaultWorldMatrix(int shaderProgram) {
    mat4 defaultWorldMatrix =
            translate(mat4(1.0f), vec3(0.0f, -0.01f, 0.0f)) * scale(mat4(1.0f), vec3(1.0f, 1.0f, 1.0f));
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &defaultWorldMatrix[0][0]);
}

void setCameraPosition(int *shaderProgram, vec3 *cameraPosition, vec3 *cameraLookAt, vec3 *cameraUp) {
    mat4 viewMatrix = lookAt(*cameraPosition,
                             *cameraPosition + *cameraLookAt,  // center
                             *cameraUp); // up
    GLuint viewMatrixLocation = glGetUniformLocation(*shaderProgram, "viewMatrix");
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
}