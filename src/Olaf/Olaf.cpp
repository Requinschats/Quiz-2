#include "Olaf.h"
#include "../Cube/Cube.h"
#include "../TranslateMatrix/TranslateMatrix.h"

Olaf::Olaf(int *shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void Olaf::Draw(float x_position, float z_position) {
    Cube *cube = new Cube();
    float legSize = 0.5f;
    float olafZPosition = z_position;
    float olafXPosition = x_position;

    //leg 1
    TranslateMatrix *leg1TranslateMatrix = new TranslateMatrix(olafXPosition - 1.0f,
                                                               1.0f,
                                                               olafZPosition,
                                                               legSize,
                                                               legSize,
                                                               legSize);
    leg1TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //leg 2
    TranslateMatrix *leg2TranslateMatrix = new TranslateMatrix(olafXPosition + 1.0f,
                                                               1.0f,
                                                               olafZPosition,
                                                               legSize,
                                                               legSize,
                                                               legSize);
    leg2TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //body
    float bodyWidth = 3.0f;
    float bodyDepth = 0.5f;
    float bodyHeight = 3.0f;
    float bodyYPosition = 4.0f;
    TranslateMatrix *bodyTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               bodyYPosition,
                                                               olafZPosition,
                                                               bodyWidth,
                                                               bodyHeight,
                                                               bodyDepth);
    bodyTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //neck
    float neckWidth = 2.0f;
    float neckHeight = 1.0f;
    float neckYPosition = bodyYPosition + 4.0f;
    TranslateMatrix *neckTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               neckYPosition,
                                                               olafZPosition,
                                                               neckWidth,
                                                               neckHeight,
                                                               bodyDepth);
    neckTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //arms
    float armWidth = 3.0f;
    float armHeight = 0.5f;
    float armYPosition = 9.0f;

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
    float headWidth = 1.5f;
    float headHeight = 1.0f;
    float headYPosition = neckYPosition + 2.0f;
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
    float noseWidth = 0.25f;
    float noseHeight = 0.25f;
    float noseZPosition = olafZPosition + 0.5f;
    float noseYPosition = headYPosition + 0.20f;
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
    float eyeWidth = 0.25f;
    float eyeHeight = 0.25f;
    float eyeZPosition = olafZPosition + 0.5f;
    float eyeYPosition = headYPosition + 0.5f;

    //eye 1
    float eye1XPosition = olafXPosition - 0.75f;
    TranslateMatrix *eye1TranslateMatrix = new TranslateMatrix(eye1XPosition,
                                                               eyeYPosition,
                                                               eyeZPosition,
                                                               eyeWidth,
                                                               eyeHeight,
                                                               bodyDepth);
    eye1TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    eyesCube->Draw();

    //eye 2
    float eye2XPosition = olafXPosition + 0.75f;
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
    float hairWidth = 0.05f;
    float hairHeight = 1.0f;
    float hairYPosition = headYPosition + 2.0f;
    TranslateMatrix *hairTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               hairYPosition,
                                                               olafZPosition,
                                                               hairWidth,
                                                               hairHeight,
                                                               bodyDepth);
    hairTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();
    TranslateMatrix *hairTranslateMatrix2 = new TranslateMatrix(olafXPosition + 0.5,
                                                                hairYPosition,
                                                                olafZPosition,
                                                                hairWidth,
                                                                hairHeight,
                                                                bodyDepth);
    hairTranslateMatrix2->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();
    TranslateMatrix *hairTranslateMatrix3 = new TranslateMatrix(olafXPosition - 0.5,
                                                                hairYPosition,
                                                                olafZPosition,
                                                                hairWidth,
                                                                hairHeight,
                                                                bodyDepth);
    hairTranslateMatrix3->bindTranslationMatrix(this->shaderProgram);
    hairCube->Draw();
}
