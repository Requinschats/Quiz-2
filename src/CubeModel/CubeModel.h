#include "glm/vec3.hpp"

class CubeModel {
public:
    CubeModel(glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), float alpha = 1);

    void Draw();

    unsigned int mVAO;
    unsigned int mVBO;
};