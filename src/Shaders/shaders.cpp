#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "fstream"
#include <string>
#include <sstream>
#include "../lighting/Lighting.h"
#include "shaders.h"

//opens and parses the content of the shader located at the given path (.glsl)
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
    //compile vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    //sets success state
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if compilation failed, print error message
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //compile fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // sets success state
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // if compilation failed, print error message
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //create shader program and attach shaders to the program
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // sets success state
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if linking failed, print error message
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //delete shaders as they are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

//parses the fragment and vertex shader sources and returns the compiled shader program
void Shaders::initializeColorShaderProgram() {
    string colorVertexShaderCode = getShaderSourceFromPath("resources/generalShader/generalShaderVertex.glsl");
    char *VertexSourcePointer = const_cast<char *>((colorVertexShaderCode).c_str());
    string colorFragmentShaderCode = getShaderSourceFromPath("resources/generalShader/generalShaderFragment.glsl");
    char *FragmentSourcePointer = const_cast<char *>((colorFragmentShaderCode).c_str());
    this->colorShaderProgram = compileAndLinkShaders(VertexSourcePointer, FragmentSourcePointer);
}

//parses the fragment and vertex shader sources and returns the compiled shader program
void Shaders::initializeTexturedShaderProgram() {
    string texturedVertexShaderCode = getShaderSourceFromPath("resources/texturedShader/texturedShaderVertex.glsl");
    char *texturedVertexSourcePointer = const_cast<char *>((texturedVertexShaderCode).c_str());
    string texturedFragmentShaderCode = getShaderSourceFromPath("resources/texturedShader/texturedShaderFragment.glsl");
    char *texturedFragmentSourcePointer = const_cast<char *>((texturedFragmentShaderCode).c_str());
    this->texturedShaderProgram = compileAndLinkShaders(texturedVertexSourcePointer, texturedFragmentSourcePointer);
}

//wrapper class that handles the state of shaders
Shaders::Shaders() {
    initializeColorShaderProgram();
    initializeTexturedShaderProgram();
    //keeps track of which shader is currently bound
    this->bindedShader = colorShaderProgram;

    //initialize the two light sources from the wrapper classes
    this->main_lighting = new Lighting(0, vec3(0.6f, 40.0f, 5.0f));
    main_lighting->initializeLighting(colorShaderProgram);
    main_lighting->initializeLighting(texturedShaderProgram);

    this->secondary_lighting = new Lighting(1, vec3(0.6f, 4.0f, 5.0f));
    secondary_lighting->initializeLighting(texturedShaderProgram);

}

//"directional" function that binds the color or textured shader program depending on the given boolean
//lighting is also bound to the shader program after binding the shader program
void Shaders::bindShaderFromWithTexture(bool withTexture, Controller *controller) {
    if (withTexture) {
        glUseProgram(texturedShaderProgram);
        main_lighting->setParameters(texturedShaderProgram);
        secondary_lighting->setParameters(texturedShaderProgram);
        controller->setShader(&texturedShaderProgram);
        this->bindedShader = texturedShaderProgram;
    } else {
        glUseProgram(colorShaderProgram);
        main_lighting->setParameters(colorShaderProgram);
        controller->setShader(&colorShaderProgram);
        this->bindedShader = colorShaderProgram;
    }
}

//wraps the logic to switch from the textured shader program to the color shader program
void Shaders::useColorShaderProgram(Controller *controller, vec3 lightFocusCoordinate) {
    glUseProgram(colorShaderProgram);
    main_lighting->setParameters(colorShaderProgram);
    controller->setCameraPosition();
    this->bindedShader = colorShaderProgram;
}