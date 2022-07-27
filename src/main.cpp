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
#include "WorldCube/WorldCube.h"
#include "characters/Characters.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    Shaders *shaders = new Shaders();

    Controller *defaultController = new Controller(&shaders->texturedShaderProgram);
    Controller *frontController = new Controller(&shaders->texturedShaderProgram);
    Controller *backController = new Controller(&shaders->texturedShaderProgram);
    setActiveController(defaultController);

    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    Textures *textures = new Textures(shaders->texturedShaderProgram);
    RenderMode renderMode = RenderMode::triangles;

    bool withTexture = true;

    float lastFrameTime = glfwGetTime();

    Quiz2Axis *quiz2Axis = new Quiz2Axis(textures);
    Grid *grid = new Grid(shaders->texturedShaderProgram);
    WorldCube *worldCube = new WorldCube(shaders->texturedShaderProgram);
    Characters *characters = new Characters(shaders->texturedShaderProgram, textures, 2, 0);

    while (!glfwWindowShouldClose(window)) {
        Olaf *olaf = new Olaf(shaders, activeController, textures);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shaders->useColorShaderProgram(activeController, olaf->movement->position);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        olaf->Draw(
                renderMode,
                translateMatrix,
                olafScale - 1,
                withTexture);


        glUseProgram(shaders->texturedShaderProgram);
        shaders->lighting->setParameters(shaders->texturedShaderProgram);
        activeController->setShader(&shaders->texturedShaderProgram);

        textures->loadSnowTexture();
        translateMatrix->bindTranslationMatrix(shaders->texturedShaderProgram);
        grid->Draw(translateMatrix);

        quiz2Axis->draw(translateMatrix, shaders);

        textures->loadSkyTexture();
        worldCube->Draw(translateMatrix);

        characters->Draw(translateMatrix, 0, -5);


        handleViewInputs(window,
                         shaders->texturedShaderProgram,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                olaf->movement,
                &olafScale,
                &renderMode,
                &withTexture
        );

        handleControllers(window, defaultController, frontController, backController);

        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
