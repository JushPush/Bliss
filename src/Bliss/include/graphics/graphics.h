#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../math/math.h"
#include "../input/input.h"
#include "../engine/core/error.h"

#pragma region Data stuff ig
struct rgb {
    int r, g, b;
};

union COLOR {
    uint8_t bytes[3];
};

COLOR convertRGB(rgb _rgb_);

rgb _rgb(int red, int green, int blue);
#define rgb(r,g,b) _rgb(r,g,b)

struct windowData {
    int x;
    int y;
    int width;
    int height;
    std::string title;

    bool fullscreen;
};
#pragma endregion

#pragma region Renderer
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
#pragma endregion

#pragma region Window
class Window {
public:
    windowData windat = {
        0,0,
        800,600,
        "",
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
#pragma endregion

#pragma region Shaders and Textures
class Shader {
public:
    Shader() {}
    Shader(const char* vertex_shader_text, const char* fragment_shader_text);

    void Update();
    void Render();

protected:
private:
    GLuint vertex_shader, fragment_shader, program;
    GLint mvp_location, vpos_location, vcol_location;
};
#pragma endregion

#endif