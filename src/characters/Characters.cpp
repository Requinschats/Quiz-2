#include "Characters.h"
#include "../Cube/Cube.h"
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
Characters::Characters(int shaderProgram, float baseHeight, int selectedCharacterIndex) {
    this->shaderProgram = shaderProgram;
    //letters shared format. Decided arbitrarily.
    this->letterHeight = 8.0f;
    this->letterWidth = 3.0f;
    this->letterSpacing = 3.0f;
    this->lineWidth = 1.0f;
    this->letterIndex = 0;
    //skateboard height
    this->baseHeight = 1;
    //allows changing the state of the character if selected by keyboard inputs
    this->selectedCharacterIndex = selectedCharacterIndex;
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
    this->letterIndex = 0;
    this->DrawF(translateMatrix, getLetterXPosition(x_position), z_position, 1);
    this->DrawA(translateMatrix, getLetterXPosition(x_position), z_position, 3);
//    this->DrawD(translateMatrix, getLetterXPosition(x_position), z_position, 4);
//    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position, 5);
//    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position, 6);
//    this->DrawT(translateMatrix, getLetterXPosition(x_position), z_position, 7);
//    this->DrawE(translateMatrix, getLetterXPosition(x_position), z_position, 8);
}

//Draw logic is explained at the top of this file
//Note again that simple calculations are made based on shared values for the positions and sizes.
void Characters::DrawF(TranslateMatrix *translateMatrix, float x_position, float z_position, int characterIndex) {
    bool isSelected = isSelectedCharacter(characterIndex);
    vec3 color = getColorFromState(characterIndex);

    CubeModel *cube = new CubeModel();
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight / 2 + 1,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight / 2 + 3.5f,
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
    translateMatrix->setPosition(x_position, baseHeight + this->letterHeight / 2, z_position);
    translateMatrix->setSize(this->lineWidth, this->letterHeight, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right column
    translateMatrix->setPosition(x_position + letterWidth + lineWidth, baseHeight + this->letterHeight / 2,
                                 z_position);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //middle bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight / 2 + 1,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //top bar
    translateMatrix->setPosition(x_position + letterWidth - lineWidth, baseHeight + this->letterHeight / 2 + 3.5f,
                                 z_position);
    translateMatrix->setSize(letterWidth, this->lineWidth, this->lineWidth);
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    (new Skateboard(shaderProgram))->Draw(translateMatrix, x_position, z_position);
}