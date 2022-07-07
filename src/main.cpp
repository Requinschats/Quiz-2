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
#include "TranslateMatrix/TranslateMatrix.h"

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
        float legSize = 0.5f;
        float olafZPosition = -10.0f;
        float olafXPosition = 2.0f;

        //leg 1
        TranslateMatrix *leg1TranslateMatrix = new TranslateMatrix(1.0f, 1.0f, olafZPosition, legSize, legSize,
                                                                   legSize);
        leg1TranslateMatrix->bindTranslationMatrix(&shaderProgram);
        cube->Draw();

        //leg 2
        TranslateMatrix *leg2TranslateMatrix = new TranslateMatrix(3.0f, 1.0f, olafZPosition, legSize, legSize,
                                                                   legSize);
        leg2TranslateMatrix->bindTranslationMatrix(&shaderProgram);
        cube->Draw();

        //body
        float bodyWidth = 2.0f;
        float bodyDepth = 0.5f;
        float bodyHeight = 3.0f;
        TranslateMatrix *bodyTranslateMatrix = new TranslateMatrix(olafXPosition, bodyHeight, olafZPosition, bodyWidth,
                                                                   bodyWidth,
                                                                   bodyDepth);
        bodyTranslateMatrix->bindTranslationMatrix(&shaderProgram);
        cube->Draw();

        //neck

        glfwSwapBuffers(window);

        glfwPollEvents();

        handleInputs(window, shaderProgram, &cameraPosition, &cameraLookAt, &cameraUp, dt);
    }

    glfwTerminate();

    return 0;
}
