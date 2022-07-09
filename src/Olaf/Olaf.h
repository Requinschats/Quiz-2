#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Cube/Cube.h"

class Olaf {

public:
    Olaf(int shaderProgram);

    void Draw(
            RenderMode renderMode,
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            float scale
    );

    int shaderProgram;
};
