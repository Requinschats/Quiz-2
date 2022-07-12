#include "GL/glew.h"
#include "../Cube/Cube.h"

#pragma once

class TexturedCube {
public:
    TexturedCube(
            float rgb1 = 255.0f,
            float rgb2 = 255.0f,
            float rgb3 = 255.0f,
            RenderMode renderMode = RenderMode::triangles
    );

    ~TexturedCube();

    int getGLRenderMode();

    void Draw();

private:
    GLuint cubeVAO_;
    RenderMode renderMode_;
};
