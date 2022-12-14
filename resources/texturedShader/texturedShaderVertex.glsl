#version 330 core

//attributes of each vertex set in the model classes
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normals;
layout (location = 2) in vec2 aUV;
layout (location = 3) in float alpha;

//variables passed from the code to set the perspective, world orientation and the lighting
uniform mat4 worldMatrix;
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 light_view_proj_matrix_0;
uniform mat4 light_view_proj_matrix_1;

//outputs of the vertex shader to be used in the fragment shader
out vec3 fragment_normal;
out vec3 fragment_color;
out vec3 fragment_position;
out vec4 fragment_position_light_space;
out vec2 vertexUV;
out float fragment_alpha;

void main()
{
    //lighting computations with planes' normals and positions
    fragment_color = normals;
    fragment_normal = mat3(worldMatrix) * normals;
    fragment_position = vec3(worldMatrix * vec4(position, 1.0));
    fragment_position_light_space = light_view_proj_matrix_1 * light_view_proj_matrix_0 * vec4(fragment_position, 1.0);
    gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(position, 1.0);
    vertexUV = aUV;

    //if an alpha is provided for transparency, set the fragment alpha to that value otherwise set it to 1.0
    if (alpha > 0)
    {
        fragment_alpha = alpha;
    }
    else
    {
        fragment_alpha = 1;
    }
}