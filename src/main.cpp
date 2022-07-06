#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Axis/Axis.h"
#include "inputs/inputs.h"
#include "Cube/Cube.h"
#include "Shaders/shaders.h"
#include "sources/generalShader/GeneralShader.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    glUseProgram(shaderProgram);
//    glEnable(GL_CULL_FACE);

    vec3 cameraPosition(0.6f, 1.0f, 10.0f);
    vec3 cameraLookAt(0.0f, 0.0f, -1.0f);
    vec3 cameraUp(0.0f, 1.0f, 0.0f);

    glm::mat4 initialProjectionMatrix = setInitialProjectionMatrix(&shaderProgram);
    setCameraPosition(&shaderProgram, &cameraPosition, &cameraLookAt, &cameraUp);

    float lastFrameTime = glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        setCameraPosition(&shaderProgram, &cameraPosition, &cameraLookAt, &cameraUp);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;


        glClear(GL_COLOR_BUFFER_BIT);

        setDefaultWorldMatrix(shaderProgram);

        Axis *axis = new Axis();
        axis->Draw();

        Cube *cube = new Cube();
        cube->Draw();

        glfwSwapBuffers(window);

        glfwPollEvents();

        handleInputs(window, shaderProgram, &cameraPosition, &cameraLookAt, &cameraUp, dt);
    }

    glfwTerminate();

    return 0;
}
