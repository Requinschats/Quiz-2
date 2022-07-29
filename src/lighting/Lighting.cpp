#include "Lighting.h"
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <iostream>

using namespace glm;
using namespace std;

Lighting::Lighting(int lightId, vec3 lightPosition) {
    //set default lighting values
    // light outer angle sets the outer angle of the light cone
    this->lightAngleOuter = 30.0;
    // light inner angle sets the inner angle of the light cone
    this->lightAngleInner = 20.0;
    //where is located the light
    this->lightPosition = lightPosition;
    //id for the shader
    this->lightId = lightId;
    //where it is pointing at
    this->lightFocus = vec3(0, 10, 0);

}

void Lighting::initializeLighting(int shaderProgram) {
    //set the matching uniforms in the shader
    SetUniform1Value(shaderProgram, "light_cutoff_inner", cos(radians(lightAngleInner)));
    SetUniform1Value(shaderProgram, "light_cutoff_outer", cos(radians(lightAngleOuter)));
    SetUniformVec3(shaderProgram, "light_color", vec3(1.0, 1.0, 0.9));
    setObjectColor(shaderProgram, vec3(0.5, 0.7, 1.0));
}

//helper method to suffix the uniform name with the light id
std::string getIndexedUniform(string uniformName, int lightId) {
    std::string indexedUniform = uniformName + "_" + to_string(lightId);
    return indexedUniform;
}

//sets the other attributes of the light
void Lighting::setParameters(int shaderProgram) {
    //where the light looks at
    vec3 lightDirection = normalize(lightFocus - lightPosition);
    //uses the frustum model. Changes how wide the main light ray hits objects
    float lightNearPlane = 40.0f;
    float lightFarPlane = 500.0f;
    //frustum sets how the light spreads onto the surface as it gets away from the light planes
    mat4 lightProjectionMatrix = frustum(-10.0f, 10.0f, -10.0f, 10.0f, lightNearPlane, lightFarPlane);
    //applies the direction
    mat4 lightViewMatrix = lookAt(lightPosition, lightFocus, vec3(0.0f, 1.0f, 0.0f));
    mat4 lightSpaceMatrix = lightProjectionMatrix * lightViewMatrix;

    //sets the corresponding uniforms in the shader
    SetUniformMat4(shaderProgram, getIndexedUniform("light_view_proj_matrix", lightId).c_str(), lightSpaceMatrix);
    SetUniform1Value(shaderProgram, getIndexedUniform("light_near_plane", lightId).c_str(), lightNearPlane);
    SetUniform1Value(shaderProgram, getIndexedUniform("light_far_plane", lightId).c_str(), lightFarPlane);
    SetUniformVec3(shaderProgram, getIndexedUniform("light_position", lightId).c_str(), lightPosition);
    SetUniformVec3(shaderProgram, getIndexedUniform("light_direction", lightId).c_str(), lightDirection);
}

void Lighting::setObjectColor(int shaderProgram, vec3 objectColor) {
    //sets the object color uniform in the shader
    SetUniformVec3(shaderProgram, "object_color", objectColor);
}

//setter
void Lighting::setLightPosition(int shaderProgram, vec3 newLightPosition) {
    this->lightPosition = newLightPosition;
    SetUniformVec3(shaderProgram, getIndexedUniform("light_position", lightId).c_str(), lightPosition);
}

//setter with normalization
void Lighting::setLightFocus(int shaderProgram, vec3 newLightFocus) {
    this->lightFocus = newLightFocus;
    SetUniformVec3(shaderProgram, getIndexedUniform("light_direction", lightId).c_str(),
                   normalize(lightFocus - lightPosition));
}
