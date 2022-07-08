#include "glm/vec3.hpp"
#include "glm/fwd.hpp"

using namespace glm;

class Controller {
public:
    Controller(int *shaderProgram);

    ~Controller();

    void reset();

    void setCameraPosition(vec3 cameraPosition, vec3 cameraLookAt, vec3 cameraUp);

    mat4 rotateYAxis(float degreeOfRotation);

    void setCameraPosition();

    vec3 cameraPosition;
    vec3 cameraLookAt;
    vec3 cameraUp;
    int shaderProgram;
};