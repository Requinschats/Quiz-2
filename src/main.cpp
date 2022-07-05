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


int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    glEnable(GL_CULL_FACE);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        setInitialDistance(&shaderProgram);
        rotateFrame(shaderProgram);

        Axis *axis = new Axis();
        axis->Draw();

        Cube *cube = new Cube();
        cube->Draw();

        glfwSwapBuffers(window);

        glfwPollEvents();

        handleInputs(window, shaderProgram);
    }

    glfwTerminate();

    return 0;
}
