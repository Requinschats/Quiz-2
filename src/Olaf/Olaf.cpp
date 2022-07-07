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
    float neckYPosition = 8.0f;
    TranslateMatrix *neckTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               neckYPosition,
                                                               olafZPosition,
                                                               neckWidth,
                                                               neckHeight,
                                                               bodyDepth);
    neckTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();

    //head
    float headWidth = 1.5f;
    float headHeight = 1.5f;
    float headYPosition = 10.5f;
    TranslateMatrix *headTranslateMatrix = new TranslateMatrix(olafXPosition,
                                                               headYPosition,
                                                               olafZPosition,
                                                               headWidth,
                                                               headHeight,
                                                               bodyDepth);
    headTranslateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();
}
