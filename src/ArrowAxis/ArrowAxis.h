#include "GL/glew.h"
#include "../TranslateMatrix/TranslateMatrix.h"

////DEAD CODE//////

class ArrowAxis {
public:
    ArrowAxis();

    void Draw(TranslateMatrix *translateMatrix, GLuint shaderProgram);

private:
    GLuint arrowAxisVAO_;
};
