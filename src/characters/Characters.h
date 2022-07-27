#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Textures/Textures.h"

class Characters {
public:
    Characters(int shaderProgram, Textures *textures, float baseHeight, int selectedCharacterIndex);

    void Draw(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position
    );

    int shaderProgram;

private:
    float letterHeight;
    float letterWidth;
    float lineWidth;
    float letterSpacing;
    float letterIndex;
    int selectedCharacterIndex;

    float getLetterXPosition(float x_position);

    void DrawF(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    void DrawA(
            TranslateMatrix *translateMatrix,
            float x_position,
            float z_position,
            int letterIndex
    );

    float baseHeight;

    vec3 getColorFromState(int characterIndex);

    bool isSelectedCharacter(int characterIndex);

    int getRandomLightRGBValue();

    Textures *textures;
};