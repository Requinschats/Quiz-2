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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    float borderColor[] = {0.9f, 0, 0.0, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


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
    this->snowTextureID = loadTexture("assets/textures/snow.jpeg");
    this->carrotTextureID = loadTexture("assets/textures/carrot.jpeg");
    this->metalTextureID = loadTexture("assets/textures/metal.jpeg");
    this->blueTextureID = loadTexture("assets/textures/blue.jpeg");
    this->greenTextureID = loadTexture("assets/textures/green.jpeg");
    this->skyTextureID = loadTexture("assets/textures/sky.jpeg");

}

void Textures::loadSnowTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, snowTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, snowTextureID);
    glUniform1i(textureLocation, 0);
}

void Textures::loadCarrotTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, carrotTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, carrotTextureID);
    glUniform1i(textureLocation, 0);
}

void Textures::loadMetalTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, metalTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, metalTextureID);
    glUniform1i(textureLocation, 0);
}

void Textures::loadBlueTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, blueTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, blueTextureID);
    glUniform1i(textureLocation, 0);
}

void Textures::loadGreenTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, greenTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, greenTextureID);
    glUniform1i(textureLocation, 0);
}

void Textures::loadSkyTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, skyTextureID);
    GLuint textureLocation = glGetUniformLocation(texturedShaderProgram, "textureSampler");
    glBindTexture(GL_TEXTURE_2D, skyTextureID);
    glUniform1i(textureLocation, 0);
}
