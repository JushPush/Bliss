#ifndef DEBUGTIMER_H
#define DEBUGTIMER_H

//#include <SDL2/SDL.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

class DebugTimer
{
public:
    void Start()
    {
        startTime = glfwGetTime();
    }
    
    void End(const std::string& message)
    {
        unsigned int endTime = glfwGetTime();
        std::cout << message << (endTime - startTime) << "s" << std::endl;
    }
    
protected:
private:
    unsigned int startTime;
};

#endif // DEBUGTIMER_H