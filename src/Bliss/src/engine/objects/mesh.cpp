#include <engine/objects/mesh.h>

Mesh::Mesh(Vertex *vert) {
    vertices = vert;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Mesh::Update(double time, float ratio, GLint j) {
    mat4x4 m, p, mvp;

    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) time);
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUniformMatrix4fv(j, 1, GL_FALSE, (const GLfloat*) mvp);
}

void Mesh::Render() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}