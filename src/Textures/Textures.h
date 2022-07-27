#include "GL/glew.h"

#pragma once

GLuint loadTexture(const char *fileName);

class Textures {
public:
    Textures(int texturedShaderProgram);

    ~Textures();

    void loadSnowTexture();

    void loadCarrotTexture();

    GLuint snowTextureID;
    int texturedShaderProgram;
    GLuint metalTextureID;
    GLuint carrotTextureID;

    void loadMetalTexture();

    GLuint blueTextureID;
    GLuint greenTextureID;

    void loadBlueTexture();

    void loadGreenTexture();

    GLuint skyTextureID;

    void loadSkyTexture();

    GLuint woodTextureID;

    void loadWoodTexture();

    void loadGlossyTexture();

    GLuint glossyTextureID;
};