#include <input.h>

Input input = Input();

bool isKeyPressed(int key) {
    return input.keys[key];
}