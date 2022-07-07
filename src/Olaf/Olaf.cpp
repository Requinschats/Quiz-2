#include "Olaf.h"
#include "../Cube/Cube.h"
#include "../TranslateMatrix/TranslateMatrix.h"

Olaf::Olaf(int *shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void Olaf::Draw() {
    Cube *cube = new Cube();
    float legSize = 0.5f;
    float olafZPosition = -10.0f;
    float olafXPosition = 2.0f;

    //leg 1
    TranslateMatrix *leg1TranslateMatrix = new TranslateMatrix(1.0f, 1.0f, olafZPosition, legSize, legSize,
                                                               legSize);
    leg1TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //leg 2
    TranslateMatrix *leg2TranslateMatrix = new TranslateMatrix(3.0f, 1.0f, olafZPosition, legSize, legSize,
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

    //eyes
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
    cube->Draw();

    //eye 2
    float eye2XPosition = olafXPosition + 0.75f;
    TranslateMatrix *eye2TranslateMatrix = new TranslateMatrix(eye2XPosition,
                                                               eyeYPosition,
                                                               eyeZPosition,
                                                               eyeWidth,
                                                               eyeHeight,
                                                               bodyDepth);
    eye2TranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();
}
