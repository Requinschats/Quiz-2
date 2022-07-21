#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "fstream"
#include <string>
#include <sstream>
#include "../lighting/Lighting.h"
#include "shaders.h"

static string getShaderSourceFromPath(string path) {
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(path, std::ios::in);
    std::stringstream sstr;
    sstr << VertexShaderStream.rdbuf();
    VertexShaderCode = sstr.str();
    VertexShaderStream.close();
    return VertexShaderCode;
}

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

void Shaders::initializeColorShaderProgram() {
    string colorVertexShaderCode = getShaderSourceFromPath("resources/generalShader/generalShaderVertex.glsl");
    char *VertexSourcePointer = const_cast<char *>((colorVertexShaderCode).c_str());
    string colorFragmentShaderCode = getShaderSourceFromPath("resources/generalShader/generalShaderFragment.glsl");
    char *FragmentSourcePointer = const_cast<char *>((colorFragmentShaderCode).c_str());
    this->colorShaderProgram = compileAndLinkShaders(VertexSourcePointer, FragmentSourcePointer);
}

void Shaders::initializeTexturedShaderProgram() {
    string texturedVertexShaderCode = getShaderSourceFromPath("resources/texturedShader/texturedShaderVertex.glsl");
    char *texturedVertexSourcePointer = const_cast<char *>((texturedVertexShaderCode).c_str());
    string texturedFragmentShaderCode = getShaderSourceFromPath("resources/texturedShader/texturedShaderFragment.glsl");
    char *texturedFragmentSourcePointer = const_cast<char *>((texturedFragmentShaderCode).c_str());
    this->texturedShaderProgram = compileAndLinkShaders(texturedVertexSourcePointer, texturedFragmentSourcePointer);
}

Shaders::Shaders() {
    initializeColorShaderProgram();
    initializeTexturedShaderProgram();
    this->bindedShader = colorShaderProgram;
    this->lighting = new Lighting();
    lighting->initializeLighting(colorShaderProgram);
}

void Shaders::bindShaderFromWithTexture(bool withTexture, Controller *controller) {
    if (withTexture) {
        glUseProgram(texturedShaderProgram);
        controller->setShader(&texturedShaderProgram);
        this->bindedShader = texturedShaderProgram;
    } else {
        glUseProgram(colorShaderProgram);
        controller->setShader(&colorShaderProgram);
        this->bindedShader = colorShaderProgram;
    }
}

void Shaders::useColorShaderProgram(Controller *controller, vec3 lightFocusCoordinate) {
    glUseProgram(colorShaderProgram);
    lighting->setParameters(colorShaderProgram, lightFocusCoordinate);
    controller->setCameraPosition();
    this->bindedShader = colorShaderProgram;
}