#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Textures/Textures.h"

class Skateboard {
public:
    Skateboard(int shaderProgram, Textures *textures, float currentHeight);

    void Draw(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );

    int shaderProgram;
    float height;
    Textures *textures;
    float currentHeight;
};