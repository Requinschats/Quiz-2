#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

void window_size_callback(GLFWwindow *window, int width, int height) {
    glfwSetWindowAspectRatio(window, width, height);
}

GLFWwindow *initializeWindow() {
    glfwInit();

    // Set all the required options for GLFW including versions and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow(1024, 768, "Comp371 - Assignment 1", NULL, NULL);
    //error handling
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

    //enable depth testing to avoid z-fighting
    glEnable(GL_DEPTH_TEST);

    //hide hidden faces (backface culling)
    glEnable(GL_CULL_FACE);

    //force resize to be in a given aspect ratio
    glfwSetWindowSizeCallback(window, window_size_callback);

    return window;
}