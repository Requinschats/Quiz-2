#include "../TranslateMatrix/TranslateMatrix.h"
#include "../Shaders/shaders.h"
#include "../Textures/Textures.h"

class Quiz2Axis {
public:

    Quiz2Axis(Textures *textures);

    void draw(TranslateMatrix *translateMatrix, Shaders *shaders);

    Textures *textures;
};