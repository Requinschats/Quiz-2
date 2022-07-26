#include "Lighting.h"
#include "glm/glm.hpp"
#include "../Cube/Cube.h"
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Lighting::Lighting() {
    this->lightAngleOuter = 30.0;
    this->lightAngleInner = 20.0;
    this->lightPosition = vec3(0.6f, 40.0f, 5.0f);
}

void Lighting::initializeLighting(int shaderProgram) {
    SetUniform1Value(shaderProgram, "light_cutoff_inner", cos(radians(lightAngleInner)));
    SetUniform1Value(shaderProgram, "light_cutoff_outer", cos(radians(lightAngleOuter)));
    SetUniformVec3(shaderProgram, "light_color", vec3(1.0, 1.0, 0.9));
    setObjectColor(shaderProgram, vec3(0.5, 0.7, 1.0));
}

void Lighting::setParameters(int shaderProgram) {
    vec3 lightFocus(0, 10, 0);
    vec3 lightDirection = normalize(lightFocus - lightPosition);
    float lightNearPlane = 40.0f;
    float lightFarPlane = 500.0f;
    mat4 lightProjectionMatrix = frustum(-10.0f, 10.0f, -10.0f, 10.0f, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0.0f, 1.0f, 0.0f));
    mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

    SetUniformMat4(shaderProgram, "light_view_proj_matrix", lightSpaceMatrix);
    SetUniform1Value(shaderProgram, "light_near_plane", lightNearPlane);
    SetUniform1Value(shaderProgram, "light_far_plane", lightFarPlane);
    SetUniformVec3(shaderProgram, "light_position", lightPosition);
    SetUniformVec3(shaderProgram, "light_direction", lightDirection);
}

void Lighting::setObjectColor(int shaderProgram, vec3 objectColor) {
    SetUniformVec3(shaderProgram, "object_color", objectColor);
}