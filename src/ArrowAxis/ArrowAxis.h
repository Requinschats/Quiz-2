#include "GL/glew.h"

class ArrowAxis {
public:
    ArrowAxis();

    void Draw();

private:
    GLuint arrowAxisVAO_;
};
