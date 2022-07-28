#include "Lighting.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>

using namespace glm;
using namespace std;

Lighting::Lighting(int lightId, vec3 lightPosition) {
    this->lightAngleOuter = 30.0;
    this->lightAngleInner = 20.0;
    this->lightPosition = lightPosition;
    this->lightId = lightId;
    this->lightFocus = vec3(0, 10, 0);

}

void Lighting::initializeLighting(int shaderProgram) {
    SetUniform1Value(shaderProgram, "light_cutoff_inner", cos(radians(lightAngleInner)));
    SetUniform1Value(shaderProgram, "light_cutoff_outer", cos(radians(lightAngleOuter)));
    SetUniformVec3(shaderProgram, "light_color", vec3(1.0, 1.0, 0.9));
    setObjectColor(shaderProgram, vec3(0.5, 0.7, 1.0));
}


std::string getIndexedUniform(string uniformName, int lightId) {
    std::string indexedUniform = uniformName + "_" + to_string(lightId);
    return indexedUniform;
}

void Lighting::setParameters(int shaderProgram) {
    vec3 lightDirection = normalize(lightFocus - lightPosition);
    float lightNearPlane = 40.0f;
    float lightFarPlane = 500.0f;
    mat4 lightProjectionMatrix = frustum(-10.0f, 10.0f, -10.0f, 10.0f, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0.0f, 1.0f, 0.0f));
    mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

    SetUniformMat4(shaderProgram, getIndexedUniform("light_view_proj_matrix", lightId).c_str(), lightSpaceMatrix);
    SetUniform1Value(shaderProgram, getIndexedUniform("light_near_plane", lightId).c_str(), lightNearPlane);
    SetUniform1Value(shaderProgram, getIndexedUniform("light_far_plane", lightId).c_str(), lightFarPlane);
    SetUniformVec3(shaderProgram, getIndexedUniform("light_position", lightId).c_str(), lightPosition);
    SetUniformVec3(shaderProgram, getIndexedUniform("light_direction", lightId).c_str(), lightDirection);
}

void Lighting::setObjectColor(int shaderProgram, vec3 objectColor) {
    SetUniformVec3(shaderProgram, "object_color", objectColor);
}

void Lighting::setLightPosition(int shaderProgram, vec3 newLightPosition) {
    this->lightPosition = newLightPosition;
    SetUniformVec3(shaderProgram, getIndexedUniform("light_position", lightId).c_str(), lightPosition);
}

void Lighting::setLightFocus(int shaderProgram, vec3 newLightFocus) {
    this->lightFocus = newLightFocus;
    SetUniformVec3(shaderProgram, getIndexedUniform("light_direction", lightId).c_str(),
                   normalize(lightFocus - lightPosition));
}
