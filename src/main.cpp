#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Axis/Axis.h"
#include "glm/ext/matrix_transform.hpp"
#include "inputs/inputs.h"

const char *getVertexShaderSource() {
    return
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            ""
            "uniform mat4 worldMatrix;"
            ""
            "out vec3 vertexColor;"
            "void main()"
            "{"
            "   vertexColor = aColor;"
            "   gl_Position = worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
            "}";
}


const char *getFragmentShaderSource() {
    return
            "#version 330 core\n"
            "in vec3 vertexColor;"
            "out vec4 FragColor;"
            "void main()"
            "{"
            "   FragColor = vec4(1, 1, 1, 1.0f);"
            "}";
}


int compileAndLinkShaders() {
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = getVertexShaderSource();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = getFragmentShaderSource();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

// Variables to be used later in tutorial
float angle = 0;
float rotationSpeed = 50.0f;  // 180 degrees per second
float lastFrameTime = glfwGetTime();

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int shaderProgram = compileAndLinkShaders();
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // rotate frame
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;
        angle = (angle + rotationSpeed * dt);
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
        glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &rotationMatrix[0][0]);
        //

        Axis *axis = new Axis();
        axis->Draw();

        glfwSwapBuffers(window);

        glfwPollEvents();

        handleInputs(window);
    }

    glfwTerminate();

    return 0;
}
