#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include <string>
#include <GL/glew.h>
#include "engine/object.h"

#include "bliss_math.h"
#include "input.h"

#include "entities/camera.h"

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

    /*Renderer(rect disp, GLFWwindow* window) {
        display.startx = (int)disp.start.x;
        display.starty = (int)disp.start.y;
        display.width = (int)disp.end.x;
        display.height = (int)disp.end.y;
    }*/

    ~Renderer() {}
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
    INPUT input;

    struct {
        // TODO: implement custom mouse cursor
    } cursor;

    Window() {
    }

    Window(windowData wdat) {
        windat = wdat;
    }

    virtual ~Window();

    void Setup(windowData wdat) { windat = wdat; }

    bool Init();

    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;

    //virtual void KeyPress(int key, int scancode, int action, int mods) = 0;

    virtual void Input(double time) = 0;
    virtual void Update(double time) = 0;
    virtual void Render() = 0;

    void Close();

    void Destroy();

    void Clear(float r, float g, float b, float a);
	void SwapBuffers();

    SDL_Window* getWindow() {
        return window;
    }

    virtual void OnResize(int width, int height) {};

    void Resize(int width, int height) {
        windat.width = width;
        windat.height = height;

        OnResize(width,height);
    }

    bool isRunning() { return running; }
private:
    bool running = false;

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_GLContext glContext;

    /*static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
    }*/

    bool begin_createWindow() {
        double width = 1.0 * this->windat.width;
        double height = 1.0 * this->windat.height;

        return true;
    }
};
#pragma endregion

#pragma region Shaders and Textures
class Shader
{
public:
    Shader() {}
	Shader(const std::string& fileName);

	void Bind();
	void Update(const Transform& transform, const Camera& camera);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

class Texture
{
public:
    Texture() {}
	Texture(const std::string& fileName);

	void Bind();

	virtual ~Texture();
protected:
private:
	GLuint m_texture;
};
#pragma endregion

#endif