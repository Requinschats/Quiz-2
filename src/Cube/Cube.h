#include "GL/glew.h"
#include "../TranslateMatrix/TranslateMatrix.h"

class Cube {
public:
    Cube();

    ~Cube();

    void Draw(int *shaderProgram, TranslateMatrix translateMatrix);

private:
    GLuint cubeVAO_;
    GLuint cubeEAO_;
};