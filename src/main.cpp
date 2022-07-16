#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Cube/Cube.h"
#include "sources/generalShader/GeneralShader.h"
#include "Olaf/Olaf.h"
#include "ArrowAxis/ArrowAxis.h"
#include "Grid/Grid.h"
#include "inputs/inputs.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    Shaders *shaders = new Shaders();

    Controller *controller = new Controller(&shaders->colorShaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    Textures *textures = new Textures(shaders->texturedShaderProgram);
    RenderMode renderMode = RenderMode::triangles;

    float olafXPosition = 0.0f;
    float olafZPosition = 0.0f;
    float olafScale = 1.0f;
    bool withTexture = true;

    float lastFrameTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        glUseProgram(shaders->colorShaderProgram);

        controller->setCameraPosition();

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        glClearColor(0.5, 0.5, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (new ArrowAxis())->Draw(translateMatrix, shaders->colorShaderProgram);

        Olaf *olaf = new Olaf(shaders, controller, textures);
        olaf->Draw(
                renderMode,
                translateMatrix,
                olafXPosition,
                olafZPosition,
                olafScale,
                olafRotationAngle,
                withTexture);

        glUseProgram(shaders->texturedShaderProgram);
        controller->setShader(&shaders->texturedShaderProgram);
        textures->loadSnowTexture();
        (new Grid(shaders->texturedShaderProgram))->Draw(translateMatrix);

        handleViewInputs(window,
                         shaders->texturedShaderProgram,
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
