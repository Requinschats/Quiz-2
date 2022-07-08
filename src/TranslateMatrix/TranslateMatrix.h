#pragma once

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
    float rotationAngle;

    void setPosition(float x_position, float y_position, float z_position);

    void setSize(float x_size, float y_size, float z_size);

    void setRotationAngle(float rotationAngle);

    void setDefaultPosition();

    void setDefaultSize();
};
