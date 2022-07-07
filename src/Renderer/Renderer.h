#include "GL/glew.h"
#include "../TranslateMatrix/TranslateMatrix.h"

class Renderer {
    static void setTranslationMatrix(int *shaderProgram, TranslateMatrix translateMatrix);
};
