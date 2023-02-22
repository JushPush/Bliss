#ifndef MESH_H
#define MESH_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <linmath.h>

struct Vertex {
    float x, y;
    float r, g, b;
};

class Mesh {
public:
    Vertex *vertices;
    Mesh() {}
    Mesh(Vertex *vert);

    void Render();
    void Update(double time, float ratio, GLint j);
protected:
private:
    GLuint vertex_buffer;
};

#endif