#include "GL/glew.h"

GLuint loadTexture(const char *fileName);

class Textures {
public:
    Textures(int texturedShaderProgram);

    ~Textures();

    void loadBrickTexture();

    GLuint snowTextureID;
    int texturedShaderProgram;
};