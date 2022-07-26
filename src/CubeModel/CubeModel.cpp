#include "CubeModel.h"
#include "GL/glew.h"
#include <glm/glm.hpp>

using namespace glm;

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 UVs;
    glm::vec3 color;
};

CubeModel::CubeModel(vec3 size) {
    vec3 halfSize = size * 0.5f;
    Vertex vertexBuffer[] = {  // position,                normal,                  UVs,                color,
            //left
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec2(0, 0), vec3(1.0f, 0.0f, 0.0f)},
            {vec3(-halfSize.x, -halfSize.y, halfSize.z),  vec3(-1.0f, 0.0f, 0.0f), vec2(1, 0), vec3(1.0f, 0.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, halfSize.z),   vec3(-1.0f, 0.0f, 0.0f), vec2(0, 1), vec3(1.0f, 0.0f, 0.0f)},
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(-1.0f, 0.0f, 0.0f), vec2(1, 0), vec3(1.0f, 0.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, halfSize.z),   vec3(-1.0f, 0.0f, 0.0f), vec2(0, 1), vec3(1.0f, 0.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, -halfSize.z),  vec3(-1.0f, 0.0f, 0.0f), vec2(1, 1), vec3(1.0f, 0.0f, 0.0f)},

            //front
            {vec3(halfSize.x, halfSize.y, -halfSize.z),   vec3(0.0f, 0.0f, -1.0f), vec2(1, 1), vec3(0.0f, 0.0f, 1.0f)},
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec2(0, 0), vec3(0.0f, 0.0f, 1.0f)},
            {vec3(-halfSize.x, halfSize.y, -halfSize.z),  vec3(0.0f, 0.0f, -1.0f), vec2(1, 0), vec3(0.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, halfSize.y, -halfSize.z),   vec3(0.0f, 0.0f, -1.0f), vec2(0, 1), vec3(0.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, -halfSize.z),  vec3(0.0f, 0.0f, -1.0f), vec2(1, 1), vec3(0.0f, 0.0f, 1.0f)},
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, 0.0f, -1.0f), vec2(0, 0), vec3(0.0f, 0.0f, 1.0f)},


            //bottom
            {vec3(halfSize.x, -halfSize.y, halfSize.z),   vec3(0.0f, -1.0f, 0.0f), vec2(0, 0), vec3(0.0f, 1.0f, 1.0f)},
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec2(1, 1), vec3(0.0f, 1.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, -halfSize.z),  vec3(0.0f, -1.0f, 0.0f), vec2(0, 1), vec3(0.0f, 1.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, halfSize.z),   vec3(0.0f, -1.0f, 0.0f), vec2(0, 0), vec3(0.0f, 1.0f, 1.0f)},
            {vec3(-halfSize.x, -halfSize.y, halfSize.z),  vec3(0.0f, -1.0f, 0.0f), vec2(1, 0), vec3(0.0f, 1.0f, 1.0f)},
            {vec3(-halfSize.x, -halfSize.y, -halfSize.z), vec3(0.0f, -1.0f, 0.0f), vec2(1, 1), vec3(0.0f, 1.0f, 1.0f)},

            //back
            {vec3(-halfSize.x, halfSize.y, halfSize.z),   vec3(0.0f, 0.0f, 1.0f),  vec2(1, 1), vec3(0.0f, 1.0f, 0.0f)},
            {vec3(-halfSize.x, -halfSize.y, halfSize.z),  vec3(0.0f, 0.0f, 1.0f),  vec2(1, 0), vec3(0.0f, 1.0f, 0.0f)},
            {vec3(halfSize.x, -halfSize.y, halfSize.z),   vec3(0.0f, 0.0f, 1.0f),  vec2(0, 0), vec3(0.0f, 1.0f, 0.0f)},
            {vec3(halfSize.x, halfSize.y, halfSize.z),    vec3(0.0f, 0.0f, 1.0f),  vec2(0, 1), vec3(0.0f, 1.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, halfSize.z),   vec3(0.0f, 0.0f, 1.0f),  vec2(1, 1), vec3(0.0f, 1.0f, 0.0f)},
            {vec3(halfSize.x, -halfSize.y, halfSize.z),   vec3(0.0f, 0.0f, 1.0f),  vec2(0, 0), vec3(0.0f, 1.0f, 0.0f)},

            //right
            {vec3(halfSize.x, halfSize.y, halfSize.z),    vec3(1.0f, 0.0f, 0.0f),  vec2(1, 1), vec3(1.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, -halfSize.z),  vec3(1.0f, 0.0f, 0.0f),  vec2(0, 0), vec3(1.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, halfSize.y, -halfSize.z),   vec3(1.0f, 0.0f, 0.0f),  vec2(1, 0), vec3(1.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, -halfSize.z),  vec3(1.0f, 0.0f, 0.0f),  vec2(0, 0), vec3(1.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, halfSize.y, halfSize.z),    vec3(1.0f, 0.0f, 0.0f),  vec2(1, 1), vec3(1.0f, 0.0f, 1.0f)},
            {vec3(halfSize.x, -halfSize.y, halfSize.z),   vec3(1.0f, 0.0f, 0.0f),  vec2(0, 1), vec3(1.0f, 0.0f, 1.0f)},

            //top
            {vec3(halfSize.x, halfSize.y, halfSize.z),    vec3(0.0f, 1.0f, 0.0f),  vec2(1, 1), vec3(1.0f, 1.0f,
                                                                                                    0.0f)}, // top - yellow
            {vec3(halfSize.x, halfSize.y, -halfSize.z),   vec3(0.0f, 1.0f, 0.0f),  vec2(1, 0), vec3(1.0f, 1.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, -halfSize.z),  vec3(0.0f, 1.0f, 0.0f),  vec2(0, 1), vec3(1.0f, 1.0f, 0.0f)},
            {vec3(halfSize.x, halfSize.y, halfSize.z),    vec3(0.0f, 1.0f, 0.0f),  vec2(1, 1), vec3(1.0f, 1.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, -halfSize.z),  vec3(0.0f, 1.0f, 0.0f),  vec2(0, 1), vec3(1.0f, 1.0f, 0.0f)},
            {vec3(-halfSize.x, halfSize.y, halfSize.z),   vec3(0.0f, 1.0f, 0.0f),  vec2(1, 0), vec3(1.0f, 1.0f, 0.0f)}
    };

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);



    // 1st attribute buffer : vertex Positions
    glVertexAttribPointer(
            0,                // attribute. No particular reason for 0, but must match the layout in the shader.
            3,                // size
            GL_FLOAT,        // type
            GL_FALSE,        // normalized?
            sizeof(Vertex), // stride
            (void *) 0        // array buffer offset
    );
    glEnableVertexAttribArray(0);

    // 2nd attribute buffer : vertex normal
    glVertexAttribPointer(1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void *) sizeof(vec3)    // Normal is Offseted by vec3 (see class Vertex)
    );
    glEnableVertexAttribArray(1);


    // 3rd attribute buffer : vertex color
    glVertexAttribPointer(2,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void *) (2 * sizeof(vec3)) // Color is Offseted by 2 vec3 (see class Vertex)
    );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(Vertex),
                          (void *) ((2 * sizeof(vec3)) + sizeof(vec2)) // Color is Offseted by 2 vec3 (see class Vertex)
    );
    glEnableVertexAttribArray(3);


}

void CubeModel::Draw() {
    glBindVertexArray(mVAO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices: 3 * 2 * 6 (3 per triangle, 2 triangles per face, 6 faces)
}
