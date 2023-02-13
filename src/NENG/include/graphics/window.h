/* date = February 1st 2023 8:37 am */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>

#include "renderer.h"
#include "../input/input.h"

#pragma region Callbacks

void error_callback(int error, const char* description)
{
    //fprintf(stderr, "Error: %s\n", description);
}

void window_close_callback(GLFWwindow* window)
{
    //if (!time_to_close)
    //    glfwSetWindowShouldClose(window, GL_FALSE);
}

void window_size_callback(GLFWwindow* window, int width, int height)
{

}

#pragma endregion

struct windowData {
    int x;
    int y;
    int width;
    int height;
    std::string title;
};

static windowData defWinDat = {
        0,0,
        800,600,
        "Title"
};

class Window {
public:
    windowData windat = {};
    Renderer renderer;

    Window(windowData wdat = defWinDat) {
        //instance = this;
        windat = wdat;
    }

    ~Window() {}

    void Setup(windowData wdat) { windat = wdat; }

    bool Init();

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    virtual void KeyPress(int key, int scancode, int action, int mods) = 0;

    virtual void Update(double time) = 0;

    void Destroy();

    GLFWwindow* getWindow() {
        return window;
    }

    static void error_callback(int error, const char* description);
    static void window_close_callback(GLFWwindow* window);
    static void window_size_callback(GLFWwindow* window, int width, int height);

private:
    GLFWwindow* window;
    GLFWcursor* cursor;
};

#endif //WINDOW_H
