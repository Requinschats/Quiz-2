#include "GL/glew.h"
#include "Quiz2Axis.h"
#include "../CubeModel/CubeModel.h"

using namespace glm;

Quiz2Axis::Quiz2Axis() {}

void Quiz2Axis::draw(TranslateMatrix *translateMatrix, Shaders *shaders) {
    CubeModel *cube = new CubeModel(vec3(2, 2, 2));
    float axisLength = 5.0f;
    float axisWidth = 0.25f;
    float axisHeight = 0.25f;

    //axis x
    translateMatrix->setPosition(axisLength, 0.0f, 0.0f);
    translateMatrix->setSize(axisLength, axisWidth, axisHeight);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //axis y
    translateMatrix->setPosition(0.0f, axisLength, 0.0f);
    translateMatrix->setSize(axisWidth, axisLength, axisHeight);
    translateMatrix->setObjectYRotationAngle(90.0f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //axis z
    translateMatrix->setPosition(0.0f, 0.0f, axisLength);
    translateMatrix->setSize(axisWidth, axisHeight, axisLength);
    translateMatrix->setObjectZRotationAngle(90.0f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();
}
