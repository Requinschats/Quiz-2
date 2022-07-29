#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

//constructor that sets all the state, such as the position and the size to default values
TranslateMatrix::TranslateMatrix(float x_position,
                                 float y_position,
                                 float z_position,
                                 float x_size,
                                 float y_size,
                                 float z_size) {
    this->setPosition(x_position, y_position, z_position);
    this->setSize(x_size, y_size, z_size);
    this->setWorldRotationAngle(0.0f);
    this->setObjectYRotationAngle(0);
}

// rotating the object around its center which is defined by pathToRotationMatrix. Again, my approach is to translate to the pathToRotationMatrix, rotate around the resulting point and then translate back to the original point for the rendering. This allows the letters to rotate on themselves for instance.
glm::mat4 TranslateMatrix::getRotatedObjectMatrix(glm::mat4 translationMatrix) {
    if (objectRotation.yAxisRotation.objectRotationAngle != 0) {
        translationMatrix = getSingleAxisRotatedObjectMatrix(translationMatrix,
                                                             objectRotation.yAxisRotation.objectRotationAngle,
                                                             this->objectRotation.yAxisRotation.pathToRotationMatrix,
                                                             RotationAxis::y);
    }
    if (objectRotation.xAxisRotation.objectRotationAngle != 0) {
        translationMatrix = getSingleAxisRotatedObjectMatrix(translationMatrix,
                                                             objectRotation.xAxisRotation.objectRotationAngle,
                                                             this->objectRotation.xAxisRotation.pathToRotationMatrix,
                                                             RotationAxis::x);
    }
    if (objectRotation.zAxisRotation.objectRotationAngle != 0) {
        translationMatrix = getSingleAxisRotatedObjectMatrix(translationMatrix,
                                                             objectRotation.zAxisRotation.objectRotationAngle,
                                                             this->objectRotation.zAxisRotation.pathToRotationMatrix,
                                                             RotationAxis::z);
    }
    return translationMatrix;
}

// calculates the new translation matrix passed to the shaders from the current state and binds the state so that it is used for render
void TranslateMatrix::bindTranslationMatrix(int shaderProgram) {
    // changing the world center position allows rotating around another axis the (0,0,0). My approach is to translate to the world center position, rotate around the world center position and then translate back to the original point for the rendering
    // translating the object from origin to its position
    glm::mat4 translationMatrix =
            rotate(mat4(1.0f), radians(this->rotationAngleYaxis), vec3(0.0f, 1.0f, 0.0f))
            * rotate(mat4(1.0f), radians(this->rotationAngleXaxis), vec3(1.0f, 0, 0.0f))
            * rotate(mat4(1.0f), radians(this->rotationAngleZaxis), vec3(0.0f, 0.0f, 1.0f))
            * translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    translationMatrix = getRotatedObjectMatrix(translationMatrix);

    // scaling the object from the size state
    translationMatrix = translationMatrix * scale(mat4(5.0f), vec3(size.x, size.y, size.z));
    //sets the corresponding uniform (worldMatrix) variable in the shader program
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);

    //resets the object's rotation angle after the bind in order to prevent the object from rotating twice when it is drawn again

    resetObjectRotation();
}

//reset object rotation
void TranslateMatrix::resetObjectRotation() {
    this->objectRotation.xAxisRotation.objectRotationAngle = 0;
    this->objectRotation.yAxisRotation.objectRotationAngle = 0;
    this->objectRotation.zAxisRotation.objectRotationAngle = 0;
}


//setter for rotation on the x axis
void TranslateMatrix::setObjectXRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.xAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.xAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

//setter for rotation on the y axis
void TranslateMatrix::setObjectYRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.yAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.yAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

//setter for rotation on the z axis
void TranslateMatrix::setObjectZRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.zAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.zAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

//sets the rotation on the z axis but determines the center of rotation by providing the object center instead of the path to the rotation axis
void TranslateMatrix::setObjectZRotationFromObjectCenter(float rotationAngle, vec3 objectCenter) {
    this->objectRotation.zAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.zAxisRotation.pathToRotationMatrix = vec3(-position.x + objectCenter.x,
                                                                   -position.y + objectCenter.y,
                                                                   -position.z + objectCenter.z);
}

//setter for position
void TranslateMatrix::setPosition(float x_position, float y_position, float z_position) {
    this->position.x = x_position;
    this->position.y = y_position;
    this->position.z = z_position;
}

//setter for size
//note that size maps to scale in the matrix multiplication
void TranslateMatrix::setSize(float x_size, float y_size, float z_size) {
    this->size.x = x_size;
    this->size.y = y_size;
    this->size.z = z_size;
}

//setter for rotation angle on the x axis
void TranslateMatrix::setWorldRotationAngle(float rotationAngle) {
    this->rotationAngleYaxis = rotationAngle;
}

//default setter
void TranslateMatrix::setDefaultRotationAngle() {
    this->rotationAngleYaxis = 0.0f;
    this->rotationAngleXaxis = 0.0f;
    this->rotationAngleZaxis = 0.0f;
}

//default setter
void TranslateMatrix::setDefaultPosition() {
    this->setPosition(0.0f, 0.0f, 0.0f);
}

//default setter
void TranslateMatrix::setDefaultSize() {
    this->setSize(1.0f, 1.0f, 1.0f);
}

//reset the entire state of the translation matrix to default values
void TranslateMatrix::resetDefault() {
    this->setDefaultSize();
    this->setDefaultPosition();
    this->setDefaultRotationAngle();
}