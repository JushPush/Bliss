#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../math/math.h"
#include "color.h"

#include "shader.h"

class Renderer {
public:
    struct {
        int startx = 0;
        int starty = 0;
        int width = 0;
        int height = 0;

        unsigned char* data = {};
    } display;

    Renderer() {}

    Renderer(rect disp, GLFWwindow* window) {
        display.startx = (int)disp.start.x;
        display.starty = (int)disp.start.y;
        display.width = (int)disp.end.x;
        display.height = (int)disp.end.y;
    }

    ~Renderer() {}

    bool Init(GLFWwindow* window);

    void Update(GLFWwindow* window);
    void PostUpdate(GLFWwindow* window);

    void DrawLine(v2 start, v2 end, rgb color, int point_size, double line_width);

    void DrawBox(rect box, rgb color, bool fill);

    void SetPixel(int x, int y, rgb color);
    void SetPixel(int x, int y, uint8_t color[3]);
    void ClearPixel(int x, int y);

    void Clear();

    void Resize(rect disp, GLFWwindow* window);
};

#endif