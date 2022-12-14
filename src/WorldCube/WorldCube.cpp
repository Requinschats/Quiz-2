#include "WorldCube.h"
#include "../Cube/Cube.h"
#include "../CubeModel/CubeModel.h"

WorldCube::WorldCube(int shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void WorldCube::Draw(TranslateMatrix *translateMatrix) {
    glEnable(GL_CULL_FACE);
    //culling the front actually draws the back which is essential for the world cube
    glCullFace(GL_FRONT);
    //sky color is passed
    CubeModel *cube = new CubeModel(vec3(3.0f, 3.0f, 3.0f), 1);
    //world center is (0,0,0)
    translateMatrix->setPosition(0, 0, 0);
    //same size as the grid
    translateMatrix->setSize(200, 200, 200);
    //binds the translation matrix to the shader program
    translateMatrix->bindTranslationMatrix(this->shaderProgram);
    cube->Draw();
    glCullFace(GL_BACK);
}