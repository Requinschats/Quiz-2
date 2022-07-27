#include "Skateboard.h"
#include "../Cube/Cube.h"
#include "../CubeModel/CubeModel.h"
#include "../sphere/Sphere.h"

// constructor that sets the default values
Skateboard::Skateboard(int shaderProgram, Textures *textures) {
    this->shaderProgram = shaderProgram;
    this->textures = textures;
    this->height = 1.0f;
}

// draws the skateboard. The process can be resumed as followed for every cube or part of the object.
// 1. instantiate the cube object
// 2. apply modifications to the translation matrix wrapper like setting the position, size, etc.
// 3. bind the updated translation matrix to the state machine
// 4. call the cube's draw method
void Skateboard::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    Sphere *wheelCube = new Sphere();

    //values likes theses are shared between the draw calls to be able to move the object has a hole, i.e. that all parts move together.
    const float boardWidth = 3.0f;
    const float boardLength = 14.0f;
    const float frontFaceZPosition = z_position + 1.0f;
    const float backFaceZPosition = z_position - 1.0f;

    this->textures->loadGlossyTexture();
    //wheels
    float wheelSize = 1.5f;
    //wheel 1
    translateMatrix->setPosition(x_position, wheelSize, backFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 2
    translateMatrix->setPosition(x_position, wheelSize, frontFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 3
    translateMatrix->setPosition(x_position + boardLength, wheelSize, frontFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 4
    translateMatrix->setPosition(x_position + boardLength, wheelSize, backFaceZPosition);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //board plank
    this->textures->loadMetalTexture();
    CubeModel *boardCube = new CubeModel();
    float plankLength = boardLength + 2 * wheelSize;
    float plankHeight = 0.25f;
    float plankYPosition = wheelSize + 0.75 + plankHeight;
    translateMatrix->setPosition(x_position + plankLength / 2 - wheelSize, plankYPosition, z_position);
    translateMatrix->setSize(plankLength, plankHeight, boardWidth * 1.25);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    boardCube->Draw();
}
