#ifndef INPUT_H
#define INPUT_H

#include <GLFW/glfw3.h>

#include "../math/math.h"

struct Keys {
    // Implement key library
} keys;

struct INPUT {
    struct {
        bool _keys[GLFW_KEY_LAST] = {};
        bool _mouse_buttons[GLFW_MOUSE_BUTTON_LAST] = {};

        struct {
            double x;
            double y;
        } mouse;
    } inputs, inputs_prev;

    v2 getMousePosition() {
        return v2(inputs.mouse.x,inputs.mouse.y);
    }

    bool isKeyPressed(int key) {
        return inputs._keys[key];
    }

    bool isMouseButtonPressed(int button) {
        return inputs._mouse_buttons[button];
    }

    const char* getKeyName(int key) {
        return glfwGetKeyName(key, 0);
    }
};

#pragma region Input Callbacks

#pragma endregion

#endif