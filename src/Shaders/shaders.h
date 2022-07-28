#include "../Controller/Controller.h"
#include "../lighting/Lighting.h"

#pragma once


int compileAndLinkShaders(char *vertexShaderSource, char *fragmentShaderSource);

class Shaders {
public:
    int colorShaderProgram;
    int texturedShaderProgram;
    int bindedShader;
    Lighting *main_lighting;

    Shaders();

    void bindShaderFromWithTexture(bool withTexture, Controller *controller);

    void initializeColorShaderProgram();

    void initializeTexturedShaderProgram();

    void useColorShaderProgram(Controller *controller, vec3 lightFocusCoordinate);

    Lighting *secondary_lighting;
};