#include "GL/glew.h"
#include "../TranslateMatrix/TranslateMatrix.h"

class Grid {
public:
    Grid(int shaderProgram);

    void Draw(TranslateMatrix *translateMatrix);

    static int getRandomGridCoordinate();

private:
    GLuint gridVAO_;
    int shaderProgram;
};

