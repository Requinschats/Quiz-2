#include "GL/glew.h"
#include "Quiz2Axis.h"
#include "../CubeModel/CubeModel.h"
#include "../Cone/Cone.h"


using namespace glm;

Quiz2Axis::Quiz2Axis(Textures *textures) {
    this->textures = textures;
}

void Quiz2Axis::draw(TranslateMatrix *translateMatrix, Shaders *shaders) {
    CubeModel *cube = new CubeModel(vec3(2, 2, 2));
    Cone *cone = new Cone();

    float axisLength = 5.0f;
    float axisWidth = 0.35f;
    float axisHeight = 0.35f;

    //axis x
    this->textures->loadCarrotTexture();
    translateMatrix->setPosition(axisLength, 0.25f, 0.0f);
    translateMatrix->setSize(axisLength, axisWidth, axisHeight);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    translateMatrix->setObjectZRotationAngle(270.0f, vec3(4.0f, 0.0f, 0.0f));
    translateMatrix->setPosition(axisLength + 0.5, -0.5f, 1.5f);
    translateMatrix->setSize(0.5, 0.5, 0.5);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cone->draw();

    //axis y
    this->textures->loadGreenTexture();
    translateMatrix->setPosition(0.0f, axisLength, 0.0f);
    translateMatrix->setSize(axisWidth, axisLength, axisHeight);
    translateMatrix->setObjectYRotationAngle(90.0f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    translateMatrix->setSize(0.5, 0.5, 0.5);
    translateMatrix->setPosition(-3.225, axisLength * 2 - 0.5, 1.5f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cone->draw();

    //axis z
    this->textures->loadBlueTexture();
    translateMatrix->setPosition(0.0f, 0.25f, axisLength);
    translateMatrix->setSize(axisWidth, axisHeight, axisLength);
    translateMatrix->setObjectZRotationAngle(90.0f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();
    translateMatrix->setSize(0.5, 0.5, 0.5);
    translateMatrix->setPosition(-axisLength / 2 - 0.75, -1.25f, axisLength * 2 - 0.4);
    translateMatrix->setObjectXRotationAngle(90.0f);
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cone->draw();
}
