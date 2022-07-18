#include "../Controller/Controller.h"

int compileAndLinkShaders(char *vertexShaderSource, char *fragmentShaderSource);

class Shaders {
public:
    int colorShaderProgram;
    int texturedShaderProgram;

    Shaders();

    void bindShaderFromWithTexture(bool withTexture, Controller *controller);

    int bindedShader;

    void initializeColorShaderProgram();

    void initializeTexturedShaderProgram();
};