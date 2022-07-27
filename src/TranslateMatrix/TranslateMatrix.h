#pragma once

#include "glm/vec3.hpp"
#include "glm/fwd.hpp"
#include "glm/ext/matrix_transform.hpp"

using namespace glm;

enum RotationAxis {
    x, y, z
};

static vec3 getRotationVectorFromRotationAxis(RotationAxis axis) {
    if (axis == RotationAxis::y) {
        return vec3(0, 1, 0);
    }
    if (axis == RotationAxis::x) {
        return vec3(1, 0, 0);
    }
    return vec3(0, 0, 1);
}

static glm::mat4 getSingleAxisRotatedObjectMatrix(
        glm::mat4 translationMatrix,
        float rotationAngle,
        vec3 pathToRotationMatrix,
        RotationAxis axis
) {
    vec3 rotationVector = getRotationVectorFromRotationAxis(axis);
    translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix);
    translationMatrix = translationMatrix * rotate(mat4(1.0f), radians(rotationAngle), rotationVector);
    translationMatrix = translationMatrix * translate(mat4(1.0f), pathToRotationMatrix * -1.0f);
    return translationMatrix;
}

struct AxisRotation {
    vec3 pathToRotationMatrix;
    float objectRotationAngle;
};

struct ObjectRotation {
    AxisRotation xAxisRotation;
    AxisRotation yAxisRotation;
    AxisRotation zAxisRotation;
};

class TranslateMatrix {
    struct Size {
        float x;
        float y;
        float z;
    };

    struct Position {
        float x;
        float y;
        float z;
    };
public:
    TranslateMatrix(float x_position,
                    float y_position,
                    float z_position,
                    float x_size,
                    float y_size,
                    float z_size);

    void bindTranslationMatrix(int shaderProgram);

    Position position;
    Size size;

    float rotationAngleYaxis;
    float rotationAngleXaxis;
    float rotationAngleZaxis;

    ObjectRotation objectRotation;

    void resetObjectRotation();

    void setPosition(float x_position, float y_position, float z_position);

    void setSize(float x_size, float y_size, float z_size);

    void setWorldRotationAngle(float rotationAngle);

    void setObjectYRotationAngle(float rotationAngle, vec3 pathToRotationAxis = vec3(0, 0, 0));

    void setObjectXRotationAngle(float rotationAngle, vec3 pathToRotationAxis = vec3(0, 0, 0));

    void setObjectZRotationAngle(float rotationAngle, vec3 pathToRotationAxis = vec3(0, 0, 0));

    void setDefaultPosition();

    void setDefaultSize();

    void setDefaultRotationAngle();

    void resetDefault();

    mat4 getRotatedObjectMatrix(mat4 translationMatrix);
};
