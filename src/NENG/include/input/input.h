#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

struct Input {
    bool _keys[GLFW_KEY_LAST] = {};
    bool _mouse_buttons[GLFW_MOUSE_BUTTON_LAST] = {};

    struct Mouse {
        double x;
        double y;
    } mouse;

    bool isKeyPressed(int key) {
        return _keys[key];
    }

    bool isMouseButtonPressed(int button) {
        return _mouse_buttons[button];
    }

    const char* getKeyName(int key) {
        return glfwGetKeyName(key, 0);
    }
} input;

#pragma region Input Callbacks
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    input._keys[key] = (action == GLFW_PRESS);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    input.mouse.x = xpos;
    input.mouse.y = -ypos + 600;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    input._mouse_buttons[button] = (action == GLFW_PRESS);
}
#pragma endregion

#endif