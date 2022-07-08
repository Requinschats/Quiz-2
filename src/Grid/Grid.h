#include "GL/glew.h"

class Grid {
public:
    Grid(int *shaderProgram);

    void Draw();

    static int getRandomGridCoordinate();

private:
    GLuint gridVAO_;
    int *shaderProgram;
};

