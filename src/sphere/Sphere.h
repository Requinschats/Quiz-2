

#include "GL/glew.h"

void renderSphere();

class Sphere {
public:
    Sphere();

    ~Sphere();

    void draw();

    int cubeVertices;
    GLuint cubeVAO;
};
