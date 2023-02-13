#ifndef RENDERER_H
#define RENDERER_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

typedef struct v2 {
    int x;
    int y;
}
v2;

#define v2(x,y) v2 {x,y}

class Renderer {
public:
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;

    Renderer() {}

    void DrawLine(double startx, double starty, double endx, double endy);
};

#endif