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
#include "./TexturedCube/TexturedCube.h"

using namespace glm;

int main(int argc, char *argv[]) {

    GLFWwindow *window = initializeWindow();

    int shaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    int texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(),
                                                      getTexturedFragmentShaderSource());
    glUseProgram(shaderProgram);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Controller *controller = new Controller(&shaderProgram);
    TranslateMatrix *translateMatrix = new TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
    RenderMode renderMode = RenderMode::triangles;

    float olafXPosition = 0.0f;
    float olafZPosition = 0.0f;
    float olafScale = 1.0f;

    float lastFrameTime = glfwGetTime();

    GLuint brickTextureID = loadTexture("assets/textures/brick.jpg");

    while (!glfwWindowShouldClose(window)) {
        glUseProgram(shaderProgram);
        controller->setCameraPosition();
        glClearColor(0.5, 0.5, 1, 1.0);

        float dt = glfwGetTime() - lastFrameTime;
        lastFrameTime += dt;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        (new ArrowAxis())->Draw(translateMatrix, shaderProgram);
        (new Olaf(shaderProgram))->Draw(
                renderMode,
                translateMatrix,
                olafXPosition,
                olafZPosition,
                olafScale);

        (new Grid(shaderProgram))->Draw(translateMatrix);

        glUseProgram(texturedShaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, brickTextureID);
        GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
        glBindTexture(GL_TEXTURE_2D, brickTextureID);
        glUniform1i(textureLocation, 0);
        TexturedCube *texturedCube = new TexturedCube(255.0f, 255.0f, 255.0f, renderMode);
        translateMatrix->setPosition(olafXPosition - 1.0f * 5, 3, olafZPosition);
        translateMatrix->setSize(24.0f, 25.0f, 24.0f);
        translateMatrix->bindTranslationMatrix(texturedShaderProgram);
        texturedCube->Draw();


        handleViewInputs(window,
                         shaderProgram,
                         controller,
                         translateMatrix,
                         dt);
        handleActionInputs(
                window,
                &olafXPosition,
                &olafZPosition,
                &olafScale,
                &renderMode
        );
        glfwSwapBuffers(window);
        glfwWaitEvents();
    }

    glfwTerminate();

    return 0;
}
