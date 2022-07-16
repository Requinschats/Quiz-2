#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Cube/Cube.h"
#include "Shaders/shaders.h"
#include "sources/generalShader/GeneralShader.h"
#include "Olaf/Olaf.h"
#include "ArrowAxis/ArrowAxis.h"
#include "Grid/Grid.h"
#include "inputs/inputs.h"
#include "./Textures/Textures.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int colorShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    int texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(),
                                                      getTexturedFragmentShaderSource());
    glUseProgram(colorShaderProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Controller *controller = new Controller(&colorShaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    RenderMode renderMode = RenderMode::triangles;

    float olafXPosition = 0.0f;
    float olafZPosition = 0.0f;
    float olafScale = 1.0f;

    float lastFrameTime = glfwGetTime();

    Textures *textures = new Textures(texturedShaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glUseProgram(colorShaderProgram);
        controller->setCameraPosition();
        glClearColor(0.5, 0.5, 1, 1.0);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (new ArrowAxis())->Draw(translateMatrix, colorShaderProgram);

        glUseProgram(texturedShaderProgram);
        textures->loadBrickTexture();
        controller->setShader(&texturedShaderProgram);

        (new Olaf(texturedShaderProgram))->Draw(
                renderMode,
                translateMatrix,
                olafXPosition,
                olafZPosition,
                olafScale,
                olafRotationAngle);


        glUseProgram(colorShaderProgram);
        controller->setShader(&colorShaderProgram);

        (new Grid(colorShaderProgram))->Draw(translateMatrix);

        handleViewInputs(window,
                         texturedShaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                &olafXPosition,
                &olafZPosition,
                &olafScale,
                &renderMode,
                &olafRotationAngle
        );
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
