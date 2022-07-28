#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>
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
#include "./camera/Camera.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    Shaders *shaders = new Shaders();

    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    static Controller *defaultController = new Controller(&shaders->texturedShaderProgram);
    static Controller *frontController = new Controller(&shaders->texturedShaderProgram);
    static Controller *backController = new Controller(&shaders->texturedShaderProgram);

    Camera *defaultCamera = new Camera(defaultController, translateMatrix->rotationAngleYaxis);
    Camera *frontCamera = new Camera(frontController, 0);
    Camera *backCamera = new Camera(backController, 140);
    static Camera *cameras[] = {defaultCamera, frontCamera, backCamera};
    int activeControllerIndex = 0;

    Textures *textures = new Textures(shaders->texturedShaderProgram);
    RenderMode renderMode = RenderMode::triangles;

    bool withTexture = true;

    float lastFrameTime = glfwGetTime();

    Quiz2Axis *quiz2Axis = new Quiz2Axis(textures);
    Grid *grid = new Grid(shaders->texturedShaderProgram);
    WorldCube *worldCube = new WorldCube(shaders->texturedShaderProgram);
    Characters *characters = new Characters(shaders->texturedShaderProgram, textures, 2, 0);

    while (!glfwWindowShouldClose(window)) {
        Controller *activeController = cameras[activeControllerIndex]->controller;
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        if (lastFrameTime > 2) {
            //print lastFrameTime
            glfwSetTime(0);
            random_device randomDevice;
            std::mt19937 gen(randomDevice());
            std::uniform_int_distribution<> distribution(-20, 20);
            float randomNumber = distribution(gen);
            vec3 currentLightPosition = shaders->main_lighting->lightPosition;
            vec updatedLightPosition = vec3(currentLightPosition.x + randomNumber,
                                            currentLightPosition.y + randomNumber,
                                            currentLightPosition.z + randomNumber);
            shaders->main_lighting->setLightPosition(shaders->texturedShaderProgram, updatedLightPosition);
            shaders->main_lighting->setParameters(shaders->texturedShaderProgram);
        }

        shaders->secondary_lighting->setLightPosition(shaders->texturedShaderProgram, activeController->cameraPosition);
        shaders->secondary_lighting->setLightFocus(shaders->texturedShaderProgram, activeController->cameraLookAt);

        Olaf *olaf = new Olaf(shaders, cameras[activeControllerIndex]->controller, textures);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        shaders->useColorShaderProgram(cameras[activeControllerIndex]->controller, olaf->movement->position);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        olaf->Draw(
                renderMode,
                translateMatrix,
                olafScale - 1,
                withTexture);


        glUseProgram(shaders->texturedShaderProgram);
        shaders->main_lighting->setParameters(shaders->texturedShaderProgram);
        shaders->secondary_lighting->setParameters(shaders->texturedShaderProgram);
        cameras[activeControllerIndex]->controller->setShader(&shaders->texturedShaderProgram);

        textures->loadSnowTexture();
        translateMatrix->bindTranslationMatrix(shaders->texturedShaderProgram);
        grid->Draw(translateMatrix);

        quiz2Axis->draw(translateMatrix, shaders);

        textures->loadSkyTexture();
        worldCube->Draw(translateMatrix);

        characters->Draw(translateMatrix, 0, -5);


        handleViewInputs(window,
                         shaders->texturedShaderProgram,
                         cameras[activeControllerIndex]->controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                olaf->movement,
                &olafScale,
                &renderMode,
                &withTexture
        );

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 2;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->bindedShader);
            cameras[activeControllerIndex]->controller->applyController();
        }
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 1;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->texturedShaderProgram);
            cameras[activeControllerIndex]->controller->applyController();
        }
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 0;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->bindedShader);
            cameras[activeControllerIndex]->controller->applyController();
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            characters->jumpAnimation->nextFrame();
            characters->setStateFromJumpFrame();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
