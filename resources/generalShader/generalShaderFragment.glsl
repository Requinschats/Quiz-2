#version 330 core

in vec3 vertexNormal;

out vec4 FragColor;

void main()
{
    vec4 color = vec4(vertexNormal, 1.0f);
    if (color.a == 0.0){
        discard;
    }
    FragColor = color;

}