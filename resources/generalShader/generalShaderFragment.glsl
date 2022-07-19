#version 330 core

in vec3 vertexNormal;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vertexNormal, 1.0f);
}