/* date = February 1st 2023 8:37 am */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>

#include "renderer.h"
#include "../input/input.h"

#include "../engine/core/error.h"

struct windowData {
    int x;
    int y;
    int width;
    int height;
    std::string title;

    bool fullscreen;
};

class Window {
public:
    windowData windat = {
        0,0,
        800,600,
        "Title",
        false
    };
    Renderer renderer;
    INPUT input;

    struct {
        // TODO: implement custom mouse cursor
    } cursor;

    Window() {
    }

    Window(windowData wdat) {
        windat = wdat;
    }

    ~Window() 
    {
        Destroy();
    }

    void Setup(windowData wdat) { windat = wdat; }

    bool Init();

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    //virtual void KeyPress(int key, int scancode, int action, int mods) = 0;

    virtual void Input() = 0;
    virtual void Update(double time) = 0;
    virtual void Render() = 0;

    void Destroy();

    GLFWwindow* getWindow() {
        return window;
    }

    virtual void OnResize(int width, int height) {};

    void Resize(int width, int height) {
        windat.width = width;
        windat.height = height;

        renderer.Resize(
            rect(
                v2(0,0),
                v2(width,height)
            ), window
        ); 

        OnResize(width,height);
    }
private:
    GLFWwindow* window;

    GLFWmonitor* monitor;

    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Window* obj = (Window* )glfwGetWindowUserPointer(window);
        obj->input.inputs._keys[key] = (action == GLFW_PRESS);
    }

    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
    {
        Window* obj = (Window* )glfwGetWindowUserPointer(window);
        obj->input.inputs.mouse.x = xpos;
        obj->input.inputs.mouse.y = ypos;
    }

    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        Window* obj = (Window* )glfwGetWindowUserPointer(window);
        obj->input.inputs._mouse_buttons[button] = (action == GLFW_PRESS);
    }

    static void window_size_callback(GLFWwindow* window, int width, int height) {
        Window* obj = (Window* )glfwGetWindowUserPointer(window);
        obj->Resize(width,height);
    }

    static void window_close_callback(GLFWwindow* window) {
        Window* obj = (Window* )glfwGetWindowUserPointer(window);
        obj->Destroy();
    }

    bool begin_createWindow() {
        double width = 1.0 * this->windat.width;
        double height = 1.0 * this->windat.height;

        renderer = Renderer(rect(v2(0.0,0.0),v2(width,height)), window);

        return true;
    }
};

#endif //WINDOW_H
