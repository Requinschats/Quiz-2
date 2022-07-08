#include "glm/vec3.hpp"

using namespace glm;

static vec3 defaultCameraPosition = vec3(-5.6f, 10.0f, 10.0f);
static vec3 defaultCameraLookAt = vec3(0.5f, -0.5f, -1.0f);
static vec3 defaultCameraUp = vec3(0.0f, 1.0f, 0.0f);

class Controller {
public:
    Controller(int *shaderProgram);

    ~Controller();

    void reset();

    void setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp);

    vec3 cameraPosition;
    vec3 cameraLookAt;
    vec3 cameraUp;
    int *shaderProgram;
};