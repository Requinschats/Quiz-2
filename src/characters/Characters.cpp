#include "Characters.h"
#include "../skateboard/Skateboard.h"
#include "random"
#include "../CubeModel/CubeModel.h"

using namespace std;

//Note on the drawing logic (the same in each class):
// draws the skateboard. The process can be resumed as followed for every cube or part of the object.
// 1. instantiate the cube object
// 2. apply modifications to the translation matrix wrapper like setting the position, size, etc.
// 3. bind the updated translation matrix to the state machine
// 4. call the cube's draw method

//constructor that sets the default values
Characters::Characters(int shaderProgram, Textures *textures, float baseHeight, int selectedCharacterIndex) {
    this->shaderProgram = shaderProgram;
    this->textures = textures;
    //letters shared format. Decided arbitrarily.
    this->letterHeight = 8.0f;
    this->letterWidth = 3.0f;
    this->letterSpacing = 3.0f;
    this->lineWidth = 1.0f;
    this->letterIndex = 0;
    //skateboard height
    this->baseHeight = baseHeight;
    this->currentHeight = baseHeight;
    //allows changing the state of the character if selected by keyboard inputs
    this->selectedCharacterIndex = selectedCharacterIndex;
    this->jumpAnimation = new Jump();
}

// calculates the x-axis space between the letters
float Characters::getLetterXPosition(float x_position) {
    return x_position + (letterWidth + letterSpacing) * letterIndex;
}

int Characters::getRandomLightRGBValue() {
    random_device randomDevice;
    std::mt19937 gen(randomDevice());
    //[0,100] matches the range of light colors
    std::uniform_int_distribution<> distribution(0, 100);
    return distribution(gen);
}

// returns a different color if the character is selected by keyboard inputs
vec3 Characters::getColorFromState(int characterIndex) {
    if (this->selectedCharacterIndex == characterIndex) {
        return {240, 128, 128};
    }
    return {getRandomLightRGBValue(), getRandomLightRGBValue(), getRandomLightRGBValue()};
}

// returns if character is the one selected
bool Characters::isSelectedCharacter(int characterIndex) {
    return this->selectedCharacterIndex == characterIndex;
}

//Draw call for my last name's first 8 letters
//Each character is assigned an index to be able to change the state of the character if selected by keyboard inputs
//Position if passed down from the getLetterXPosition utility
void Characters::Draw(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    translateMatrix->setObjectZRotationAngle(jumpAnimation->activeFrame.boardRotationAngle);
    this->letterIndex = 0;
    this->textures->loadCarrotTexture();
    this->DrawF(translateMatrix, getLetterXPosition(x_position), z_position, 1);
    this->textures->loadGreenTexture();
    this->DrawA(translateMatrix, getLetterXPosition(x_position), z_position, 2);
    this->DrawTwo(translateMatrix, getLetterXPosition(x_position), z_position);
    this->DrawFour(translateMatrix, getLetterXPosition(x_position), z_position);
    (new Skateboard(shaderProgram, textures, currentHeight - baseHeight))->Draw(translateMatrix, x_position,
                                                                                z_position);
}

//Draw logic is explained at the top of this file
//Note again that simple calculations are made based on shared values for the positions and sizes.
void Characters::DrawF(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    CubeModel *cube = new CubeModel();
    translateMatrix->setPosition(x_position, currentHeight + this->letterHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, currentHeight + this->letterHeight / 2 + 1,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, currentHeight + this->letterHeight / 2 + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

//Draw logic is explained at the top of this file
void Characters::DrawA(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    CubeModel *cube = new CubeModel();

    //left column
    translateMatrix->setPosition(x_position, currentHeight + this->letterHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth, currentHeight + this->letterHeight / 2,
                                 z_position);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, currentHeight + this->letterHeight / 2 + 1,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, currentHeight + this->letterHeight / 2 + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawTwo(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    float characterXPosition = x_position + 2;
    this->textures->loadBlueTexture();
    CubeModel *cube = new CubeModel();

    //right column top
    translateMatrix->setPosition(characterXPosition, currentHeight + this->letterHeight - lineWidth, z_position);
    translateMatrix->setSize(this->lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //left column bottom
    int bottomLeftColumnHeight = this->letterHeight - 4 * lineWidth;
    translateMatrix->setPosition(characterXPosition, currentHeight + bottomLeftColumnHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, bottomLeftColumnHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right column bottom
    int bottomRightColumnHeight = this->letterHeight - 4 * lineWidth;
    translateMatrix->setPosition(characterXPosition + letterWidth, currentHeight + letterHeight - 1.5 * lineWidth,
                                 z_position);
    translateMatrix->setSize(this->lineWidth, bottomRightColumnHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(characterXPosition + lineWidth, currentHeight + this->letterHeight, z_position);
    translateMatrix->setSize(this->letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(characterXPosition + letterWidth / 2, currentHeight + letterHeight / 2 + lineWidth / 2,
                                 z_position);
    translateMatrix->setSize(this->letterWidth + lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //bottom bar
    translateMatrix->setPosition(characterXPosition + letterWidth / 2, currentHeight + lineWidth, z_position);
    translateMatrix->setSize(this->letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::DrawFour(TranslateMatrix *translateMatrix, float x_position, float z_position) {
    this->textures->loadGlossyTexture();
    float characterXPosition = x_position + 2;
    CubeModel *cube = new CubeModel();

    //right column
    translateMatrix->setPosition(characterXPosition + letterWidth, currentHeight + this->letterHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //left column
    translateMatrix->setPosition(characterXPosition, currentHeight + this->letterHeight - 2 * lineWidth, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight / 2, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(characterXPosition + letterWidth / 2, currentHeight + letterHeight / 2 + lineWidth / 2,
                                 z_position);
    translateMatrix->setSize(this->letterWidth + lineWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    this->letterIndex++;
}

void Characters::setStateFromJumpFrame() {
    this->currentHeight += jumpAnimation->activeFrame.boardHeightIncrement;
}