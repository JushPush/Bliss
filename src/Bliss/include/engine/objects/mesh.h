#ifndef MESH_H
#define MESH_H

//#include <GL/glew.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>


class Vertex {
public:
    Vertex(const glm::vec3& pos) {
        this->pos = pos;
    }

private:
    glm::vec3 pos;
    //glm::vec3 color;
};

class Mesh {
public:
    Mesh() {}
    Mesh(Vertex* verticies, unsigned int numVerticies);

    void Render();

    virtual ~Mesh();

private:
    //Mesh(const Mesh& other);
    //void operator=(const Mesh& other);

    enum {
        POSITION_VB,

        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];

    unsigned int m_drawCount;
};

#endif