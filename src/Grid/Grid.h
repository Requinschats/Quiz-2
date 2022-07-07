#include "GL/glew.h"

class Grid {
public:
    Grid(int *shaderProgram);

    void Draw();

private:
    GLuint gridVAO_;
    int *shaderProgram;
};

