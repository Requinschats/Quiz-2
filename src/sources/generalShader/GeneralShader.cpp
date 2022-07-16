#include "GeneralShader.h"

char *getVertexShaderSource() {
    return
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            ""
            "uniform mat4 worldMatrix;"
            "uniform mat4 viewMatrix = mat4(1.0f);"
            "uniform mat4 projectionMatrix = mat4(1.0f);"
            ""
            "out vec3 vertexColor;"
            "void main()"
            "{"
            "   vertexColor = aColor;"
            "   gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
            "}";
}

char *getTexturedVertexShaderSource() {
    return
            "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;"
            "layout (location = 1) in vec3 aColor;"
            "layout (location = 2) in vec2 aUV;"
            ""
            "uniform mat4 worldMatrix;"
            "uniform mat4 viewMatrix = mat4(1.0);"
            "uniform mat4 projectionMatrix = mat4(1.0);"
            ""
            "out vec3 vertexColor;"
            "out vec2 vertexUV;"
            ""
            "void main()"
            "{"
            "   vertexColor = aColor;"
            "   mat4 modelViewProjection = projectionMatrix * viewMatrix * worldMatrix;"
            "   gl_Position = modelViewProjection * vec4(aPos.x, aPos.y, aPos.z, 1.0);"
            "   vertexUV = aUV;"
            "}";
}


char *getFragmentShaderSource() {
    return
            "#version 330 core\n"
            "in vec3 vertexColor;"
            "out vec4 FragColor;"
            "void main()"
            "{"
            "   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);"
            "}";
}

char *getTexturedFragmentShaderSource() {
    return
            "#version 330 core\n"
            "in vec3 vertexColor;"
            "in vec2 vertexUV;"
            "uniform sampler2D textureSampler;"
            ""
            "out vec4 FragColor;"
            "void main()"
            "{"
            "   vec4 textureColor = texture( textureSampler, vertexUV );"
            "   FragColor = textureColor;"
            "}";
}
