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
#include "./quiz2-axis/Quiz2Axis.h"

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
    Quiz2Axis *quiz2Axis = new Quiz2Axis();
    Olaf *olaf = new Olaf(shaders, controller, textures);
    Grid *grid = new Grid(shaders->texturedShaderProgram);

    while (!glfwWindowShouldClose(window)) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shaders->useColorShaderProgram(controller, olaf->movement->position);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        glClearColor(0.5, 0.5, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Sphere *sphere = new Sphere();
        translateMatrix->setPosition(shaders->lighting->lightPosition.x, shaders->lighting->lightPosition.y,
                                     shaders->lighting->lightPosition.z);
        translateMatrix->bindTranslationMatrix(shaders->colorShaderProgram);
        sphere->draw();

        arrowAxis->Draw(translateMatrix, shaders->colorShaderProgram);
        quiz2Axis->draw(translateMatrix, shaders);


        olaf->Draw(
                renderMode,
                translateMatrix,
                olafScale - 1,
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
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
