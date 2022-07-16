#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Cube/Cube.h"
#include "../Textures/Textures.h"

static float olafRotationAngle = 0.0f;

class Olaf {

public:
    Olaf(int shaderProgram, Textures *textures);

    void Draw(
            RenderMode renderMode,
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            float scale,
            float rotationAngle
    );

    int shaderProgram;
    Textures *textures;
};
