#include "Lighting.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

Lighting::Lighting() {
    this->lightAngleOuter = 30.0;
    this->lightAngleInner = 20.0;
    this->lightPosition = vec3(15.6f, 50.0f, -20.0f);
}

void Lighting::initializeLighting(int shaderProgram) {
    SetUniform1Value(shaderProgram, "light_cutoff_inner", cos(radians(lightAngleInner)));
    SetUniform1Value(shaderProgram, "light_cutoff_outer", cos(radians(lightAngleOuter)));
    SetUniformVec3(shaderProgram, "light_color", vec3(1.0, 1.0, 1.0));
    SetUniformVec3(shaderProgram, "object_color", vec3(1.0, 1.0, 1.0));
}

void Lighting::setParameters(int shaderProgram, vec3 lightFocusCoordinates) {
    this->lightFocusCoordinates = lightFocusCoordinates;
    vec3 lightFocus(lightFocusCoordinates.x, lightFocusCoordinates.y, lightFocusCoordinates.z);
    vec3 lightDirection = normalize(lightFocus - lightPosition);

    float lightNearPlane = 20.0f;
    float lightFarPlane = 200.0f;
    mat4 lightProjectionMatrix = frustum(-1.0f, 1.0f, -1.0f, 1.0f, lightNearPlane, lightFarPlane);
    mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0.0f, 1.0f, 0.0f));
    mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

    SetUniformMat4(shaderProgram, "light_view_proj_matrix", lightSpaceMatrix);
    SetUniform1Value(shaderProgram, "light_near_plane", lightNearPlane);
    SetUniform1Value(shaderProgram, "light_far_plane", lightFarPlane);
    SetUniformVec3(shaderProgram, "light_position", lightPosition);
    SetUniformVec3(shaderProgram, "light_direction", lightDirection);
}
