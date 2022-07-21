#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#pragma once

using namespace glm;

class Lighting {
public:
    Lighting();

    double lightAngleOuter;
    double lightAngleInner;
    vec3 lightPosition;

    void initializeLighting(int shaderProgram);

    void setParameters(int shaderProgram, vec3 lightFocusCoordinates);

    vec3 lightFocusCoordinates;
};


static void SetUniformMat4(GLuint shader_id, const char *uniform_name, mat4 uniform_value) {
    glUseProgram(shader_id);
    glUniformMatrix4fv(glGetUniformLocation(shader_id, uniform_name), 1, GL_FALSE, &uniform_value[0][0]);
}

static void SetUniformVec3(GLuint shader_id, const char *uniform_name, vec3 uniform_value) {
    glUseProgram(shader_id);
    glUniform3fv(glGetUniformLocation(shader_id, uniform_name), 1, value_ptr(uniform_value));
}

template<class T>
static void SetUniform1Value(GLuint shader_id, const char *uniform_name, T uniform_value) {
    glUseProgram(shader_id);
    glUniform1i(glGetUniformLocation(shader_id, uniform_name), uniform_value);
    glUseProgram(0);
}
