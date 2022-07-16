#include "shaders.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "../sources/generalShader/GeneralShader.h"

int compileAndLinkShaders(char *vertexShaderSource, char *fragmentShaderSource) {
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

Shaders::Shaders() {
    this->colorShaderProgram = compileAndLinkShaders(getVertexShaderSource(), getFragmentShaderSource());
    this->texturedShaderProgram = compileAndLinkShaders(getTexturedVertexShaderSource(),
                                                      getTexturedFragmentShaderSource());
    this->bindedShader = colorShaderProgram;
}

void Shaders::bindShaderFromWithTexture(bool withTexture, Controller *controller){
    if(withTexture){
        glUseProgram(texturedShaderProgram);
        controller->setShader(&texturedShaderProgram);
        this->bindedShader = texturedShaderProgram;
    } else {
        glUseProgram(colorShaderProgram);
        controller->setShader(&colorShaderProgram);
        this->bindedShader = colorShaderProgram;
    }
}

