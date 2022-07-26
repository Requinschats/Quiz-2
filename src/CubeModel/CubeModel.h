#include "glm/vec3.hpp"

class CubeModel {
public:
    CubeModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f));

    void Draw();

    unsigned int mVAO;
    unsigned int mVBO;
};