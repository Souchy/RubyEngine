#pragma once

#ifndef __gl_h_
#include <glad/glad.h>
#endif
#include <resources/Mesh.h>

// VAOs and VBOs
enum VAO_IDs {
    Torus,
    NumVAOs,
};
enum Buffer_IDs {
    Indices,
    Position,
    Normal,
    UV,
    Color,
    // Tangent,
    NumBuffers
};

class MeshVao {
public:
    GLuint vaoId;
    GLuint m_Buffers[NumBuffers];
    GLsizei indexSize;

    static MeshVao createMeshBuffers(Mesh *mesh) {
        MeshVao vao;
        vao.indexSize = mesh->indices.size() * 3;

        // Create our VertexArrays Objects and VertexBuffer Objects
        glCreateVertexArrays(NumVAOs, &vao.vaoId);
        glCreateBuffers(NumBuffers, vao.m_Buffers);

        // Uploaed + bind + configure
        createIndexBuffer(mesh->indices, &vao.m_Buffers[Indices], vao.vaoId);
        createVbo3(mesh->positions, &vao.m_Buffers[Position], vao.vaoId, Position);
        createVbo3(mesh->normals, &vao.m_Buffers[Normal], vao.vaoId, Normal);
        createVbo2(mesh->uvs, &vao.m_Buffers[UV], vao.vaoId, UV);
        createVbo4(mesh->colors, &vao.m_Buffers[Color], vao.vaoId, Color);

        return vao;
    }

    static void createIndexBuffer(std::vector<glm::uvec3> data, GLuint *bufferId, GLuint vaoId) {
        GLsizei stride = sizeof(glm::uvec3);
        glNamedBufferData(*bufferId, stride * data.size(), data.data(), GL_STATIC_DRAW);
        glVertexArrayElementBuffer(vaoId, *bufferId);
    }

    static void createVbo2(std::vector<glm::vec2> data, GLuint *bufferId, GLuint vaoId, int location) {
        GLsizei stride = sizeof(glm::vec2);
        glNamedBufferData(*bufferId, stride * data.size(), data.data(), GL_STATIC_DRAW);
        bindVaoVbo(*bufferId, vaoId, location, stride, 2);
    }

    static void createVbo3(std::vector<glm::vec3> data, GLuint *bufferId, GLuint vaoId, int location) {
        GLsizei stride = sizeof(glm::vec3);
        glNamedBufferData(*bufferId, stride * data.size(), data.data(), GL_STATIC_DRAW);
        bindVaoVbo(*bufferId, vaoId, location, stride, 3);
    }

    static void createVbo4(std::vector<glm::vec4> data, GLuint *bufferId, GLuint vaoId, int location) {
        GLsizei stride = sizeof(glm::vec4);
        glNamedBufferData(*bufferId, stride * data.size(), data.data(), GL_STATIC_DRAW);
        bindVaoVbo(*bufferId, vaoId, location, stride, 4);
    }

private:
    static void bindVaoVbo(GLuint bufferId, GLuint vaoId, int location, GLsizei stride, int componentsCount) {
        glVertexArrayAttribFormat(vaoId,
                                  location,        // Attribute index
                                  componentsCount, // Number of components
                                  GL_FLOAT,        // Type
                                  GL_FALSE,        // Normalize
                                  0                // Relative offset (first component)
        );
        glVertexArrayVertexBuffer(vaoId,
                                  location, // Binding point
                                  bufferId, // VBO
                                  0,        // Offset (when the position starts)
                                  stride    // Stride
        );
        glEnableVertexArrayAttrib(vaoId,
                                  location // Attribute index
        );
        glVertexArrayAttribBinding(vaoId,
                                   location, // Attribute index
                                   location  // Binding point
        );
    }
};
