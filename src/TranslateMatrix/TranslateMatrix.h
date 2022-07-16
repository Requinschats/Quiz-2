#pragma once
#include "glm/vec3.hpp"

using namespace glm;


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

    void bindTranslationMatrix(int shaderProgram, bool shouldRotateObject=false);

    Position position;
    Size size;
    float rotationAngle;
    vec3 pathToRotationMatrix;
    float objectRotationAngle;

    void resetObjectRotationAngle();

    void setPosition(float x_position, float y_position, float z_position);

    void setSize(float x_size, float y_size, float z_size);

    void setWorldRotationAngle(float rotationAngle);

    void setObjectRotationAngle(float rotationAngle, vec3 pathToRotationAxis = vec3(0, 0, 0));

    void setDefaultPosition();

    void setDefaultSize();

    void setDefaultRotationAngle();

    void resetDefault();

    void setPathToRotationMatrix(vec3 pathToRotationAxis);
};
