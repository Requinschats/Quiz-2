#include "Olaf.h"

Olaf::Olaf(int shaderProgram) {
    this->shaderProgram = shaderProgram;
}

void Olaf::Draw(
        RenderMode renderMode,
        TranslateMatrix *translateMatrix,
        float x_position,
        float z_position,
        float scale,
        float rotationAngle
) {
    Cube *cube = new Cube(255.0f, 255.0f, 255.0f, renderMode, true);
    float legSize = 0.5f * scale;
    float olafZPosition = z_position;
    float olafXPosition = x_position;
    float olafYInitialPosition = 1.0f;

    //leg 1
    translateMatrix->setPosition(olafXPosition - 1.0f * scale, olafYInitialPosition, olafZPosition);
    translateMatrix->setSize(legSize, legSize, legSize);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(1, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //leg 2
    translateMatrix->setPosition(olafXPosition + 1.0f * scale, olafYInitialPosition, olafZPosition);
    translateMatrix->setSize(legSize, legSize, legSize);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(-1, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //body
    float bodyWidth = 3.0f * scale;
    float bodyDepth = 0.5f * scale;
    float bodyHeight = 3.0f * scale;
    float bodyYPosition = olafYInitialPosition + 3.0f * scale;
    translateMatrix->setPosition(olafXPosition, bodyYPosition, olafZPosition);
    translateMatrix->setSize(bodyWidth, bodyHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //neck
    float neckWidth = 2.0f * scale;
    float neckHeight = 1.0f * scale;
    float neckYPosition = bodyYPosition + 4.0f * scale;
    translateMatrix->setPosition(olafXPosition, neckYPosition, olafZPosition);
    translateMatrix->setSize(neckWidth, neckHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //arms
    float armWidth = 3.0f * scale;
    float armHeight = 0.5f * scale;
    float armYPosition = 9.0f * scale;

    //left arm
    float leftArmXPosition = olafXPosition - (neckWidth * 2);
    translateMatrix->setPosition(leftArmXPosition, armYPosition, olafZPosition);
    translateMatrix->setSize(armWidth, armHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(4, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //right arm
    float rightArmXPosition = olafXPosition + (neckWidth * 2);
    translateMatrix->setPosition(rightArmXPosition, armYPosition, olafZPosition);
    translateMatrix->setSize(armWidth, armHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(-4, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //head
    float headWidth = 1.5f * scale;
    float headHeight = 1.0f * scale;
    float headYPosition = neckYPosition + 2.0f * scale;
    translateMatrix->setPosition(olafXPosition, headYPosition, olafZPosition);
    translateMatrix->setSize(headWidth, headHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    cube->Draw();

    //nose
    Cube *noseCube = new Cube(255.0f, 160.0f, 122.0f, renderMode);
    float noseWidth = 0.25f * scale;
    float noseHeight = 0.25f * scale;
    float noseZPosition = olafZPosition + 0.5f * scale;
    float noseYPosition = headYPosition + 0.20f * scale;
    translateMatrix->setPosition(olafXPosition, noseYPosition, noseZPosition);
    translateMatrix->setSize(noseWidth, noseHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 0.5));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    noseCube->Draw();

    //eyes
    Cube *eyesCube = new Cube(100.0f, 100.0f, 100.0f, renderMode);
    float eyeWidth = 0.25f * scale;
    float eyeHeight = 0.25f * scale;
    float eyeZPosition = olafZPosition + 0.5f * scale;
    float eyeYPosition = headYPosition + 0.5f * scale;

    //eye 1
    float eye1XPosition = olafXPosition - 0.75f * scale;
    translateMatrix->setPosition(eye1XPosition, eyeYPosition, eyeZPosition);
    translateMatrix->setSize(eyeWidth, eyeHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0.75, 0, 0.5));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    eyesCube->Draw();

    //eye 2
    float eye2XPosition = olafXPosition + 0.75f * scale;
    translateMatrix->setPosition(eye2XPosition, eyeYPosition, eyeZPosition);
    translateMatrix->setSize(eyeWidth, eyeHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(-0.75, 0, 0.5));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    eyesCube->Draw();

    //hair
    Cube *hairCube = new Cube(250.0f, 240.0f, 190.5f, renderMode);
    float hairWidth = 0.05f * scale;
    float hairHeight = 1.0f * scale;
    float hairYPosition = headYPosition + 2.0f * scale;

    //hair 1
    translateMatrix->setPosition(olafXPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    hairCube->Draw();

    //hair 2
    float hair2XPosition = olafXPosition + 0.5f * scale;
    translateMatrix->setPosition(hair2XPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    hairCube->Draw();

    //hair 3
    float hair3XPosition = olafXPosition - 0.5f * scale;
    translateMatrix->setPosition(hair3XPosition, hairYPosition, olafZPosition);
    translateMatrix->setSize(hairWidth, hairHeight, bodyDepth);
    translateMatrix->setObjectRotationAngle(rotationAngle, vec3(0, 0, 1));
    translateMatrix->bindTranslationMatrix(this->shaderProgram, true);
    hairCube->Draw();
}
