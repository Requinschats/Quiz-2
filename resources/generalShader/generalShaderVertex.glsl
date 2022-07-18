#version 330 core

layout (location = 0) in vec3 aPos;

layout (location = 1) in vec3 aColor;

uniform mat4 worldMatrix;

uniform mat4 viewMatrix = mat4(1.0f);

uniform mat4 projectionMatrix = mat4(1.0f);

out vec3 vertexColor;

void main()
{
    vertexColor = aColor;

    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}