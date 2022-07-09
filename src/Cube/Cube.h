#include "GL/glew.h"

#pragma once

enum RenderMode {
    points, lines, triangles
};

class Cube {
public:
    Cube(
            float rgb1 = 255.0f,
            float rgb2 = 255.0f,
            float rgb3 = 255.0f,
            RenderMode renderMode = RenderMode::triangles
    );

    ~Cube();

    int getGLRenderMode();

    void Draw();

private:
    GLuint cubeVAO_;
    RenderMode renderMode_;
};