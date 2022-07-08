#include "../TranslateMatrix/TranslateMatrix.h"

class Olaf {
public:
    Olaf(int shaderProgram);

    void Draw(TranslateMatrix *translateMatrix, float x_position, float z_position, float scale);

    int shaderProgram;
};
