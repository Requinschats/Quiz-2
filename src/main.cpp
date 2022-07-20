#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "./initialization/initialization.h"
#include "Cube/Cube.h"
#include "Olaf/Olaf.h"
#include "ArrowAxis/ArrowAxis.h"
#include "Grid/Grid.h"
#include "inputs/inputs.h"

#include "./objectLoader/ObjectLoader.h"
#include "./sphere/Sphere.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    Shaders *shaders = new Shaders();

    Controller *controller = new Controller(&shaders->colorShaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    Textures *textures = new Textures(shaders->texturedShaderProgram);
    RenderMode renderMode = RenderMode::triangles;

    bool withTexture = true;

    float lastFrameTime = glfwGetTime();

    ArrowAxis *arrowAxis = new ArrowAxis();
    Olaf *olaf = new Olaf(shaders, controller, textures);
    Grid *grid = new Grid(shaders->texturedShaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(shaders->colorShaderProgram);

        controller->setCameraPosition();

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        glClearColor(0.5, 0.5, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        arrowAxis->Draw(translateMatrix, shaders->colorShaderProgram);

        olaf->Draw(
                renderMode,
                translateMatrix,
                olafScale,
                withTexture);

        glUseProgram(shaders->texturedShaderProgram);
        controller->setShader(&shaders->texturedShaderProgram);
        textures->loadSnowTexture();

        glDepthMask(GL_FALSE);
        grid->Draw(translateMatrix);
        glDepthMask(GL_TRUE);

        handleViewInputs(window,
                         shaders->texturedShaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                olaf->movement,
                &olafScale,
                &renderMode,
                &withTexture
        );
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
