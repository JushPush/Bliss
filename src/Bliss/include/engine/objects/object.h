#ifndef OBJECT_H
#define OBJECT_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Object {
public:
    virtual void Render();
    virtual void Update();
};

#endif