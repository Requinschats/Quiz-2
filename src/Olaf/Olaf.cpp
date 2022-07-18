#include "Olaf.h"

Olaf::Olaf(Shaders *shaders, Controller *controller, Textures *textures) {
    this->shaders = shaders;
    this->controller = controller;
    this->textures = textures;
    this->movement = new Movement(vec3(0.0f, 0.0f, 0.0f));
}

void Olaf::Draw(
        RenderMode renderMode,
        TranslateMatrix *translateMatrix,
        float scale,
        bool withTexture
) {
    float olafXPosition = movement->position.x;
    float olafZPosition = movement->position.z;

    PhysicalPosition physicalPosition = movement->getPhysicalPosition();

    shaders->bindShaderFromWithTexture(withTexture, controller);

    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, renderMode, withTexture);
    float legSize = 0.5f * scale;
    float olafYInitialPosition = 1.0f;

    this->textures->loadSnowTexture();

    //leg 1
    translateMatrix->setPosition(olafXPosition - 1.0f * scale, olafYInitialPosition, olafZPosition);
    translateMatrix->setSize(legSize, 3 * legSize, legSize);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(1, 0, 1));
    translateMatrix->setObjectXRotationAngle(physicalPosition.legRotationAngle, vec3(0, 0, 0));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //leg 2
    translateMatrix->setPosition(olafXPosition + 1.0f * scale, olafYInitialPosition, olafZPosition);
    translateMatrix->setSize(legSize, 3 * legSize, legSize);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(-1, 0, 1));
    translateMatrix->setObjectXRotationAngle(360 - physicalPosition.legRotationAngle, vec3(0, 0, 0));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //body
    float bodyWidth = 3.0f * scale;
    float bodyDepth = 1.0f * scale;
    float bodyHeight = 3.0f * scale;
    float bodyYPosition = olafYInitialPosition + 4.0f * scale;
    translateMatrix->setPosition(olafXPosition, bodyYPosition, olafZPosition);
    translateMatrix->setSize(bodyWidth, bodyHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //neck
    float neckWidth = 2.0f * scale;
    float neckHeight = 1.0f * scale;
    float neckYPosition = bodyYPosition + 4.0f * scale;
    translateMatrix->setPosition(olafXPosition, neckYPosition, olafZPosition);
    translateMatrix->setSize(neckWidth, neckHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //arms
    float armWidth = 3.0f * scale;
    float armHeight = 0.5f * scale;
    float armYPosition = 9.0f * scale;

    //left arm
    float leftArmXPosition = olafXPosition - (neckWidth * 2);
    translateMatrix->setPosition(leftArmXPosition, armYPosition, olafZPosition);
    translateMatrix->setSize(armWidth, armHeight, bodyDepth / 2);
    translateMatrix->setObjectXRotationAngle(physicalPosition.armXRotationAngle, vec3(0, 0, 0));
    translateMatrix->setObjectZRotationAngle(360 - physicalPosition.armZRotationAngle, vec3(0, 0, 0));
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(4, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //right arm
    float rightArmXPosition = olafXPosition + (neckWidth * 2);
    translateMatrix->setPosition(rightArmXPosition, armYPosition, olafZPosition);
    translateMatrix->setSize(armWidth, armHeight, bodyDepth / 2);
    translateMatrix->setObjectXRotationAngle(physicalPosition.armXRotationAngle, vec3(0, 0, 0));
    translateMatrix->setObjectZRotationAngle(physicalPosition.armZRotationAngle, vec3(0, 0, 0));
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(-4, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //head
    float headWidth = 1.5f * scale;
    float headHeight = 1.0f * scale;
    float headYPosition = neckYPosition + 2.0f * scale;
    translateMatrix->setPosition(olafXPosition, headYPosition, olafZPosition);
    translateMatrix->setSize(headWidth, headHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    cube->Draw();

    //nose
    this->textures->loadCarrotTexture();
    Cube *noseCube = new Cube(255.0f, 160.0f, 122.0f, renderMode, withTexture);
    float noseWidth = 0.25f * scale;
    float noseHeight = 0.25f * scale;
    float noseZPosition = olafZPosition + 0.5f * scale;
    float noseYPosition = headYPosition + 0.20f * scale;
    translateMatrix->setPosition(olafXPosition, noseYPosition, noseZPosition);
    translateMatrix->setSize(noseWidth, noseHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 0.5));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    noseCube->Draw();

    //eyes
    Cube *eyesCube = new Cube(100.0f, 100.0f, 100.0f, renderMode);
    float eyeWidth = 0.25f * scale;
    float eyeHeight = 0.25f * scale;
    float eyeZPosition = olafZPosition + 0.5f * scale;
    float eyeYPosition = headYPosition + 0.5f * scale;

    shaders->bindShaderFromWithTexture(false, controller);

    //eye 1
    float eye1XPosition = olafXPosition - 0.75f * scale;
    translateMatrix->setPosition(eye1XPosition, eyeYPosition, eyeZPosition);
    translateMatrix->setSize(eyeWidth, eyeHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0.75, 0, 0.5));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    eyesCube->Draw();

    //eye 2
    float eye2XPosition = olafXPosition + 0.75f * scale;
    translateMatrix->setPosition(eye2XPosition, eyeYPosition, eyeZPosition);
    translateMatrix->setSize(eyeWidth, eyeHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(-0.75, 0, 0.5));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    eyesCube->Draw();

    this->textures->loadMetalTexture();
    //hair
    Cube *hairCube = new Cube(250.0f, 240.0f, 190.5f, renderMode, withTexture);
    float hairWidth = 0.05f * scale;
    float hairHeight = 1.0f * scale;
    float hairYPosition = headYPosition + 2.0f * scale;

    shaders->bindShaderFromWithTexture(withTexture, controller);

    //hair 1
    translateMatrix->setPosition(olafXPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    hairCube->Draw();

    //hair 2
    float hair2XPosition = olafXPosition + 0.5f * scale;
    translateMatrix->setPosition(hair2XPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    hairCube->Draw();

    //hair 3
    float hair3XPosition = olafXPosition - 0.5f * scale;
    translateMatrix->setPosition(hair3XPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectYRotationAngle(movement->rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(shaders->bindedShader);
    hairCube->Draw();
}
