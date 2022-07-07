#include "GL/glew.h"

class Cube {
public:
    Cube();

    ~Cube();

    void Draw();

private:
    GLuint cubeVAO_;
};