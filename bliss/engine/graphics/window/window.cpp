#include "window.h"

#include <SDL2/SDL_ttf.h>

Window CreateWindow(int x, int y, int width, int height, std::string title, bool fullscreen) {
    return Window {
        x, y, width, height, title, fullscreen
    };
}

bool InitWindow(Window& window) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        //return false; 
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    window.window = SDL_CreateWindow(window.title.c_str(), window.x, window.y, window.width, window.height, SDL_WINDOW_OPENGL);
    if (!window.window) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        return false; 
    }
    /*window.renderer = SDL_CreateRenderer( window.window, -1, SDL_RENDERER_ACCELERATED );
    if (!window.renderer) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        return false; 
    }*/

    window.running = true;

    window.context = SDL_GL_CreateContext(window.window);

    GLenum res = glewInit();

    if (res != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    return true;
}

void DestroyWindow(Window& window) {
    SDL_GL_DeleteContext(window.context);
	SDL_DestroyWindow(window.window);
	SDL_Quit();
}

void SwapBuffers(Window& window) {
    SDL_GL_SwapWindow(window.window);
}

void ClearWindow(Window& window, float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}