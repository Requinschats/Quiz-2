#include "GL/glew.h"

class Cube {
public:
    Cube(float rgb1 = 255.0f, float rgb2 = 255.0f, float rgb3 = 255.0f);

    ~Cube();

    void Draw();

private:
    GLuint cubeVAO_;
};