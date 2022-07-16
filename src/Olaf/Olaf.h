#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Cube/Cube.h"
#include "../Textures/Textures.h"
#include "../Controller/Controller.h"
#include "../Shaders/shaders.h"

static float olafRotationAngle = 0.0f;
static float olafXPosition = 0.0f;
static float olafZPosition = 0.0f;
static float olafScale = 1.0f;

class Olaf {

public:
    Olaf(Shaders *shaders, Controller *controller, Textures *textures);

    void Draw(
            RenderMode renderMode,
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            float scale,
            float rotationAngle,
            bool withTexture
    );

    Textures *textures;
    Controller *controller;
    Shaders *shaders;
};
