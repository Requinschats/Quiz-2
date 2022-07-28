#include "GL/glew.h"

class Cone {
public:
    Cone();

    ~Cone();

    void draw();

    int cubeVertices;
    GLuint cubeVAO;
};
