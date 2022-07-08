#include "Renderer.h"
#include "GL/glew.h"
#include "glm/trigonometric.hpp"
#include "glm/ext/matrix_transform.hpp"

//using namespace glm;
//
//Renderer::Renderer() {
//    this->translateMatrix = TranslateMatrix(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
//}
//
//Renderer::bind(int shaderProgram) {
//    glm::mat4 worldMatrix = translate(mat4(1.0f), this->translate)
//                            * scale(mat4(1.0f), this->scale)
//                            * rotate(mat4(1.0f), glm::radians(this->rotateAngle), vec3(0.0f, 1.0f, 0.0f));
//    GLuint worldMatrixLocation = glGetUniformLocation(shaderProgram, "worldMatrix");
//    glUniformMatrix4fv(worldMatrixLocation, 1, GL_FALSE, &worldMatrix[0][0]);
//}
