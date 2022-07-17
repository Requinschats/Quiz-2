#include "TranslateMatrix.h"
#include "GL/glew.h"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

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

glm::mat4 TranslateMatrix::getRotatedObjectMatrix(glm::mat4 translationMatrix) {
    if (objectRotation.yAxisRotation.objectRotationAngle != 0) {
        translationMatrix = getSingleAxisRotatedObjectMatrix(translationMatrix,
                                                             objectRotation.yAxisRotation.objectRotationAngle,
                                                             this->objectRotation.yAxisRotation.pathToRotationMatrix,
                                                             RotationAxis::y);
    }
    return translationMatrix;
}

void TranslateMatrix::bindTranslationMatrix(int shaderProgram) {
    glm::mat4 translationMatrix =
            rotate(mat4(1.0f), radians(this->rotationAngle), vec3(0.0f, 1.0f, 0.0f))
            * translate(mat4(1.0f), vec3(position.x, position.y, position.z));

    translationMatrix = getRotatedObjectMatrix(translationMatrix);

    translationMatrix = translationMatrix * scale(mat4(5.0f), vec3(size.x, size.y, size.z));
    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &translationMatrix[0][0]);

    resetObjectRotation();
}

void TranslateMatrix::resetObjectRotation() {
    this->objectRotation.xAxisRotation.objectRotationAngle = 0;
    this->objectRotation.yAxisRotation.objectRotationAngle = 0;
    this->objectRotation.zAxisRotation.objectRotationAngle = 0;
}

void TranslateMatrix::setObjectXRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.xAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.xAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

void TranslateMatrix::setObjectYRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.yAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.yAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

void TranslateMatrix::setObjectZRotationAngle(float rotationAngle, vec3 pathToRotationAxis) {
    this->objectRotation.zAxisRotation.objectRotationAngle = rotationAngle;
    this->objectRotation.zAxisRotation.pathToRotationMatrix = pathToRotationAxis;
}

void TranslateMatrix::setPosition(float x_position, float y_position, float z_position) {
    this->position.x = x_position;
    this->position.y = y_position;
    this->position.z = z_position;
}

void TranslateMatrix::setSize(float x_size, float y_size, float z_size) {
    this->size.x = x_size;
    this->size.y = y_size;
    this->size.z = z_size;
}

void TranslateMatrix::setWorldRotationAngle(float rotationAngle) {
    this->rotationAngle = rotationAngle;
}

void TranslateMatrix::setDefaultRotationAngle() {
    this->rotationAngle = 0.0f;
}

void TranslateMatrix::setDefaultPosition() {
    this->setPosition(0.0f, 0.0f, 0.0f);
}

void TranslateMatrix::setDefaultSize() {
    this->setSize(1.0f, 1.0f, 1.0f);
}

void TranslateMatrix::resetDefault() {
    this->setDefaultSize();
    this->setDefaultPosition();
    this->setDefaultRotationAngle();
}