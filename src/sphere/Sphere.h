

#include "GL/glew.h"

class Sphere {
public:
    Sphere();

    ~Sphere();

    void draw();

    int cubeVertices;
    GLuint cubeVAO;
};
