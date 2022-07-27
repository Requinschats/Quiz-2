#include "../Controller/Controller.h"

class Camera {
public:
    Camera(Controller *controller, float worldOrientationAngle);

    Controller *controller;
    float worldOrientationAngle;
};

Camera::Camera(Controller *controller, float worldOrientationAngle) {
    this->controller = controller;
    this->worldOrientationAngle = worldOrientationAngle;
}

