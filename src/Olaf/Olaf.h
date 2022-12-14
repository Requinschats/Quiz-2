#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Cube/Cube.h"
#include "../Textures/Textures.h"
#include "../Controller/Controller.h"
#include "../Shaders/shaders.h"
#include "movement/Movement.h"

static float olafScale = 1.0f;

class Olaf {

public:
    Olaf(Shaders *shaders, Controller *controller, Textures *textures);

    void Draw(
            RenderMode renderMode,
            TranslateMatrix *translateMatrix,
            float scale,
            bool withTexture
    );

    Textures *textures;
    Controller *controller;
    Shaders *shaders;
    Movement *movement;
};
