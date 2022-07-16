#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Cube/Cube.h"
#include "../Textures/Textures.h"
#include "../Controller/Controller.h"

static float olafRotationAngle = 0.0f;

class Olaf {

public:
    Olaf(int texturedShaderProgram,int colorShaderProgram, Controller *controller, Textures *textures);

    void Draw(
            RenderMode renderMode,
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            float scale,
            float rotationAngle
    );

    int texturedShaderProgram;
    Textures *textures;
    int colorShaderProgram;
    Controller *controller;
};
