#include "GL/glew.h"

class Axis {
public:
    Axis();

    ~Axis();

    void Draw();

private:
    GLuint axisVAO_;
};
