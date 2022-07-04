#include "inputs.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"

void handleInputs(GLFWwindow *window, int shaderProgram) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // by default, camera is centered at the origin and look towards negative z-axis
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glm::mat4 viewMatrix = glm::mat4(1.0f);

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }

    // shift camera to the left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // shift camera to the left
    {
        glm::mat4 viewMatrix = glm::lookAt(glm::vec3(-0.5f, 0.0f, 0.0f),  // eye
                                           glm::vec3(-0.5f, 0.0f, -1.0f),  // center
                                           glm::vec3(0.0f, 1.0f, 0.0f));// up

        GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]);
    }
}
