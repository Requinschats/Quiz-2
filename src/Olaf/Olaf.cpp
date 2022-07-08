#include "Olaf.h"
#include "../Cube/Cube.h"
#include "../TranslateMatrix/TranslateMatrix.h"

Olaf::Olaf(int *shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void Olaf::Draw(float x_position, float z_position, float scale) {
    Cube *cube = new Cube();
    float legSize = 0.5f * scale;
    float olafZPosition = z_position * scale;
    float olafXPosition = x_position * scale;
    float olafYInitialPosition = 1.0f * scale;

    //leg 1
    TranslateMatrix *leg1TranslateMatrix = new TranslateMatrix(olafXPosition - 1.0f * scale,
                                                               olafYInitialPosition,
                                                               olafZPosition,
                                                               legSize,
                                                               legSize,
                                                               legSize);
    leg1TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //leg 2
    TranslateMatrix *leg2TranslateMatrix = new TranslateMatrix(olafXPosition + 1.0f * scale,
                                                               olafYInitialPosition,
                                                               olafZPosition,
                                                               legSize,
                                                               legSize,
                                                               legSize);
    leg2TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //body
    float bodyWidth = 3.0f * scale;
    float bodyDepth = 0.5f * scale;
    float bodyHeight = 3.0f * scale;
    float bodyYPosition = olafYInitialPosition + 3.0f * scale;
    TranslateMatrix *bodyTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               bodyYPosition,
                                                               olafZPosition,
                                                               bodyWidth,
                                                               bodyHeight,
                                                               bodyDepth);
    bodyTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //neck
    float neckWidth = 2.0f * scale;
    float neckHeight = 1.0f * scale;
    float neckYPosition = bodyYPosition + 4.0f * scale;
    TranslateMatrix *neckTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               neckYPosition,
                                                               olafZPosition,
                                                               neckWidth,
                                                               neckHeight,
                                                               bodyDepth);
    neckTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //arms
    float armWidth = 3.0f * scale;
    float armHeight = 0.5f * scale;
    float armYPosition = 9.0f * scale;

    //left arm
    float leftArmXPosition = olafXPosition - (neckWidth * 2);
    TranslateMatrix *leftArmTranslateMatrix = new TranslateMatrix(leftArmXPosition,
                                                                  armYPosition,
                                                                  olafZPosition,
                                                                  armWidth,
                                                                  armHeight,
                                                                  bodyDepth);
    leftArmTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //right arm
    float rightArmXPosition = olafXPosition + (neckWidth * 2);
    TranslateMatrix *rightArmTranslateMatrix = new TranslateMatrix(rightArmXPosition,
                                                                   armYPosition,
                                                                   olafZPosition,
                                                                   armWidth,
                                                                   armHeight,
                                                                   bodyDepth);
    rightArmTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //head
    float headWidth = 1.5f * scale;
    float headHeight = 1.0f * scale;
    float headYPosition = neckYPosition + 2.0f * scale;
    TranslateMatrix *headTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               headYPosition,
                                                               olafZPosition,
                                                               headWidth,
                                                               headHeight,
                                                               bodyDepth);
    headTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //nose
    Cube *noseCube = new Cube(255.0f, 160.0f, 122.0f);
    float noseWidth = 0.25f * scale;
    float noseHeight = 0.25f * scale;
    float noseZPosition = olafZPosition + 0.5f * scale;
    float noseYPosition = headYPosition + 0.20f * scale;
//    float nose1XPosition = olafXPosition - 0.75f;
    TranslateMatrix *noseTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               noseYPosition,
                                                               noseZPosition,
                                                               noseWidth,
                                                               noseHeight,
                                                               bodyDepth);
    noseTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    noseCube->Draw();

    //eyes
    Cube *eyesCube = new Cube(100.0f, 100.0f, 100.0f);
    float eyeWidth = 0.25f * scale;
    float eyeHeight = 0.25f * scale;
    float eyeZPosition = olafZPosition + 0.5f * scale;
    float eyeYPosition = headYPosition + 0.5f * scale;

    //eye 1
    float eye1XPosition = olafXPosition - 0.75f * scale;
    TranslateMatrix *eye1TranslateMatrix = new TranslateMatrix(eye1XPosition,
                                                               eyeYPosition,
                                                               eyeZPosition,
                                                               eyeWidth,
                                                               eyeHeight,
                                                               bodyDepth);
    eye1TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    eyesCube->Draw();

    //eye 2
    float eye2XPosition = olafXPosition + 0.75f * scale;
    TranslateMatrix *eye2TranslateMatrix = new TranslateMatrix(eye2XPosition,
                                                               eyeYPosition,
                                                               eyeZPosition,
                                                               eyeWidth,
                                                               eyeHeight,
                                                               bodyDepth);
    eye2TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    eyesCube->Draw();

    //hair
    Cube *hairCube = new Cube(250.0f, 240.0f, 190.5f);
    float hairWidth = 0.05f * scale;
    float hairHeight = 1.0f * scale;
    float hairYPosition = headYPosition + 2.0f * scale;

    //hair 1
    TranslateMatrix *hairTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               hairYPosition,
                                                               olafZPosition,
                                                               hairWidth * scale,
                                                               hairHeight * scale,
                                                               bodyDepth * scale);
    hairTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();

    //hair 2
    float hair2XPosition = olafXPosition + 0.5f * scale;
    TranslateMatrix *hairTranslateMatrix2 = new TranslateMatrix(hair2XPosition,
                                                                hairYPosition,
                                                                olafZPosition,
                                                                hairWidth,
                                                                hairHeight,
                                                                bodyDepth);
    hairTranslateMatrix2->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();

    //hair 3
    float hair3XPosition = olafXPosition - 0.5f * scale;
    TranslateMatrix *hairTranslateMatrix3 = new TranslateMatrix(hair3XPosition,
                                                                hairYPosition,
                                                                olafZPosition,
                                                                hairWidth,
                                                                hairHeight,
                                                                bodyDepth);
    hairTranslateMatrix3->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();
}
