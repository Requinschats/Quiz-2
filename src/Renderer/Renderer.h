#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "../TranslateMatrix/TranslateMatrix.h"

using namespace glm;

class Renderer {
public:
    Renderer();

    ~Renderer();

    TranslateMatrix translateMatrix;
};
