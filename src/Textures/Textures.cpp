#include "Textures.h"
#include <iostream>

#define GLEW_STATIC 1

#include <GL/glew.h>
#include <glm/common.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

GLuint loadTexture(const char *filename) {
    // Step1 Create and bind textures
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    assert(textureId != 0);


    glBindTexture(GL_TEXTURE_2D, textureId);

    // Step2 Set filter parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Step3 Load Textures with dimension data
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Error::Texture could not load texture file:" << filename << std::endl;
        return 0;
    }

    // Step4 Upload the texture to the PU
    GLenum format = 0;
    if (nrChannels == 1)
        format = GL_RED;
    else if (nrChannels == 3)
        format = GL_RGB;
    else if (nrChannels == 4)
        format = GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height,
                 0, format, GL_UNSIGNED_BYTE, data);

    // Step5 Free resources
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return textureId;
}

Textures::Textures(int texturedShaderProgram) {
    this->texturedShaderProgram = texturedShaderProgram;
    this->brickTextureID = loadTexture("assets/textures/brick.jpg");
}

void Textures::loadBrickTexture(){
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, brickTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, brickTextureID);
    glUniform1i(textureLocation, 0);
}