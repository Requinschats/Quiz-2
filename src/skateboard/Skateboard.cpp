#include "Skateboard.h"
#include "../CubeModel/CubeModel.h"
#include "../sphere/Sphere.h"

// constructor that sets the default values
Skateboard::Skateboard(int shaderProgram, Textures *textures, float currentHeight, float rotationAngle) {
    this->shaderProgram = shaderProgram;
    this->textures = textures;
    this->height = 1.0f;
    //keeps track of the height during the jump animation
    this->currentHeight = currentHeight;
    this->rotationAngle = rotationAngle;
}

// draws the skateboard. The process can be resumed as followed for every cube or part of the object.
// 1. instantiate the cube object
// 2. apply modifications to the translation matrix wrapper like setting the position, size, etc.
// 3. bind the updated translation matrix to the state machine
// 4. call the cube's draw method
void Skateboard::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    vec3 rotationCenter = vec3(x_position, this->currentHeight, z_position);

    //the cube has been replaced by a sphere, for esthetics reasons.
    Sphere *wheelCube = new Sphere();

    //values likes theses are shared between the draw calls to be able to move the object has a hole, i.e. that all parts move together.
    const float boardWidth = 3.0f;
    const float boardLength = 25.0f;
    const float frontFaceZPosition = z_position + 1.0f;
    const float backFaceZPosition = z_position - 1.0f;

    this->textures->loadGlossyTexture();
    //wheels
    float wheelSize = 1.5f;
    //wheel 1
    translateMatrix->setPosition(x_position, currentHeight + wheelSize, backFaceZPosition);

    //function added for the animation that allows finding the center of rotation from the center of the object without having to provide a path to rotationMatrix
    translateMatrix->setObjectZRotationFromObjectCenter(rotationAngle, rotationCenter);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 2
    translateMatrix->setPosition(x_position, currentHeight + wheelSize, frontFaceZPosition);
    //function added for the animation that allows finding the center of rotation from the center of the object without having to provide a path to rotationMatrix
    translateMatrix->setObjectZRotationFromObjectCenter(rotationAngle, rotationCenter);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 3
    translateMatrix->setPosition(x_position + boardLength, currentHeight + wheelSize, frontFaceZPosition);
    //function added for the animation that allows finding the center of rotation from the center of the object without having to provide a path to rotationMatrix
    translateMatrix->setObjectZRotationFromObjectCenter(rotationAngle, rotationCenter);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //wheel 4
    translateMatrix->setPosition(x_position + boardLength, currentHeight + wheelSize, backFaceZPosition);
    //function added for the animation that allows finding the center of rotation from the center of the object without having to provide a path to rotationMatrix
    translateMatrix->setObjectZRotationFromObjectCenter(rotationAngle, rotationCenter);
    translateMatrix->setSize(wheelSize, wheelSize + 0.25, wheelSize);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    wheelCube->draw();

    //board plank
    this->textures->loadMetalTexture();
    CubeModel *boardCube = new CubeModel();
    float plankLength = boardLength + 2 * wheelSize;
    float plankHeight = 0.25f;
    float plankYPosition = wheelSize + 0.75 + plankHeight;
    translateMatrix->setPosition(x_position + plankLength / 2 - wheelSize, currentHeight + plankYPosition, z_position);
    translateMatrix->setSize(plankLength, plankHeight, boardWidth * 1.25);
    //function added for the animation that allows finding the center of rotation from the center of the object without having to provide a path to rotationMatrix
    translateMatrix->setObjectZRotationFromObjectCenter(rotationAngle, rotationCenter);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    boardCube->Draw();
}
