#shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projectionMatrix = mat4(1.0f);

out vec3 vertexColor;
void main(){
   vertexColor = aColor;
   gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

#shader fragment
#version 330 core
in vec3 vertexColor;
out vec4 FragColor;
void main() {
   FragColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, 1.0f);
};