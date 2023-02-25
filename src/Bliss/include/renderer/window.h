#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <GL/glew.h>

#include "../input.h"

// Data-Oriented approach for better optimization

struct Window {
    int x, y, width, height;
    std::string title;
    bool fullscreen;

    // Super cool and fun stuff
    bool minimized = false;

    bool running = true;

    SDL_Window *window = 0;
    SDL_Renderer *renderer = 0;
    SDL_GLContext glContext = 0;
};

Window CreateWindow(int x, int y, int width, int height, std::string title, bool fullscreen);
bool InitWindow(Window& window);
void DestroyWindow(Window& window);

void ClearWindow(Window& window, float r, float g, float b, float a);
void SwapBuffers(Window& window);

void CullEvent(Window& window);