#include "../Controller/Controller.h"

//since I had no abstraction for a Camera, but rather two entities: the translationMatrix and the Controllers that partially played the role of the camera,
//I decided to create a Camera class that it regroups the camera-attributes of both entities.
//these attributes are the controller ad the world orientation of the translationMatrix.
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

