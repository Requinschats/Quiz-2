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
#include "board-movement/BoardMovement.h"

using namespace glm;

int main(int argc, char *argv[]) {

    //window initialization
    GLFWwindow *window = initializeWindow();

    //initialize shaders
    Shaders *shaders = new Shaders();

    //initialize transformation matrix
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);

    //initialize three controllers. Each is associated with a different camera.
    static Controller *defaultController = new Controller(&shaders->texturedShaderProgram);
    static Controller *frontController = new Controller(&shaders->texturedShaderProgram);
    static Controller *backController = new Controller(&shaders->texturedShaderProgram);

    //create a camera object for each controller
    Camera *defaultCamera = new Camera(defaultController, translateMatrix->rotationAngleYaxis);
    Camera *frontCamera = new Camera(frontController, 0);
    Camera *backCamera = new Camera(backController, 140);
    //store the camera objects
    static Camera *cameras[] = {defaultCamera, frontCamera, backCamera};
    int activeControllerIndex = 0;

    //Texture wrapper class that abstracts the task of loading applying textures to objects.
    Textures *textures = new Textures(shaders->texturedShaderProgram);
    //We will only use triangles for this assignment.
    RenderMode renderMode = RenderMode::triangles;

    //will always be true for this assignment.
    bool withTexture = true;

    float lastFrameTime = glfwGetTime();

    //grid axis specific for quiz 2
    Quiz2Axis *quiz2Axis = new Quiz2Axis(textures);
    //The floor
    Grid *grid = new Grid(shaders->texturedShaderProgram);
    //The world cube
    WorldCube *worldCube = new WorldCube(shaders->texturedShaderProgram);
    //The letters and numbers and the skateboard
    Characters *characters = new Characters(shaders->texturedShaderProgram, textures, 2, 0);
    //Keeps track of the board's position
    BoardMovement *boardMovement = new BoardMovement(vec3(0, 0, -5));
    //eases access to active camera
    Controller *activeController = cameras[activeControllerIndex]->controller;
    // to calculate the time difference between frames
    float referenceTime = 0;
    while (!glfwWindowShouldClose(window)) {
        //time between frames
        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;

        //set the camera to a random position within the -20 to 20 range every 2 seconds
        if (lastFrameTime - referenceTime > 2) {
            referenceTime = lastFrameTime;
            //access the computer random number service
            random_device randomDevice;
            std::mt19937 gen(randomDevice());
            //setting the distribution to be between -20 and 20
            std::uniform_int_distribution<> distribution(-20, 20);
            float randomNumber = distribution(gen);
            vec3 currentLightPosition = shaders->main_lighting->lightPosition;
            //update the position from the random number
            vec updatedLightPosition = vec3(currentLightPosition.x + randomNumber,
                                            currentLightPosition.y + randomNumber,
                                            currentLightPosition.z + randomNumber);
            //apply the new position to the light
            shaders->main_lighting->setLightPosition(shaders->texturedShaderProgram, updatedLightPosition);
            //display the change to the screen
            shaders->main_lighting->setParameters(shaders->texturedShaderProgram);
        }

        //set the secondary light to the same position as the main camera
        shaders->secondary_lighting->setLightPosition(shaders->texturedShaderProgram, activeController->cameraPosition);
        shaders->secondary_lighting->setLightFocus(shaders->texturedShaderProgram, activeController->cameraLookAt);

        //dead code
        Olaf *olaf = new Olaf(shaders, cameras[activeControllerIndex]->controller, textures);

        //to blend between textures. More dead code.
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //switch to the color shader program
        shaders->useColorShaderProgram(cameras[activeControllerIndex]->controller, olaf->movement->position);

        //reset buffers every frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //dead code
        olaf->Draw(
                renderMode,
                translateMatrix,
                olafScale - 1,
                withTexture);

        //switch back to the textured shader program and reset its lighting parameters
        glUseProgram(shaders->texturedShaderProgram);
        shaders->main_lighting->setParameters(shaders->texturedShaderProgram);
        shaders->secondary_lighting->setParameters(shaders->texturedShaderProgram);
        cameras[activeControllerIndex]->controller->setShader(&shaders->texturedShaderProgram);

        //load the snow texture before rendering the grid
        textures->loadSnowTexture();
        //bind the state of the translationMatrix to the state machine
        translateMatrix->bindTranslationMatrix(shaders->texturedShaderProgram);
        grid->Draw(translateMatrix);

        //draw the axis specified for quiz 2
        quiz2Axis->draw(translateMatrix, shaders);

        //load the sky texture before rendering the world cube
        textures->loadSkyTexture();
        worldCube->Draw(translateMatrix);

        //draw call for the characters and the skateboard
        characters->Draw(translateMatrix, boardMovement->position.x, boardMovement->position.z);


        //handle view inputs
        handleViewInputs(window,
                         shaders->texturedShaderProgram,
                         cameras[activeControllerIndex]->controller,
                         translateMatrix,
                         dt);
        //handle action inputs
        handleActionInputs(
                window,
                olaf->movement,
                &olafScale,
                &renderMode,
                &withTexture
        );

        //more inputs

        //switch to the back camera
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 2;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->bindedShader);
            cameras[activeControllerIndex]->controller->applyController();
        }

        //switch to the front camera
        if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 1;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->texturedShaderProgram);
            cameras[activeControllerIndex]->controller->applyController();
        }

        //switch to the default camera
        if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
            cameras[activeControllerIndex]->worldOrientationAngle = translateMatrix->rotationAngleYaxis;
            activeControllerIndex = 0;
            translateMatrix->setWorldRotationAngle(cameras[activeControllerIndex]->worldOrientationAngle);
            translateMatrix->bindTranslationMatrix(shaders->bindedShader);
            cameras[activeControllerIndex]->controller->applyController();
        }
        //make the skateboard do a willy
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            //call the next frame and bind its state
            characters->jumpAnimation->nextFrame();
            characters->setStateFromJumpFrame();
        }
        //move the skateboard leftward
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
            (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)) {
            if (characters->jumpAnimation->activeFrame.boardHeightIncrement != 0) {
                //call the next frame and bind its state
                characters->jumpAnimation->nextFrame();
                characters->setStateFromJumpFrame();
            }
            boardMovement->moveLeft();
        }
        //move the skateboard rightward
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            boardMovement->moveRight();
        }

        //double buffer support
        glfwSwapBuffers(window);

        //wait for events instead of polling for performance reasons
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
