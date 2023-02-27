#include <renderer/window.h>

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

    window.glContext = SDL_GL_CreateContext(window.window);

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
    SDL_GL_DeleteContext(window.glContext);
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

// clamp pitch to [-89, 89]
float clampPitch(float p)
{
    return p > 89.0f ? 89.0f : (p < -89.0f ? -89.0f : p);   
}

// clamp yaw to [-180, 180] to reduce floating point inaccuracy
float clampYaw(float y)
{
    float temp = (y + 180.0f) / 360.0f;
    return y - ((int)temp - (temp < 0.0f ? 1 : 0)) * 360.0f;
}

void CullEvent(Window& window) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_KEYDOWN:
                input.keys[event.key.keysym.scancode] = true;
                break;
            case SDL_KEYUP:
                input.keys[event.key.keysym.scancode] = false;
                break;
            case SDL_MOUSEMOTION:
                window.mouseMove = true;
                input.mouse.x = (float)event.motion.x - window.width / 2;
                input.mouse.y = (float)event.motion.y - window.height / 2;
                break;
            case SDL_QUIT:
                window.running = false;
                break;
            default:
                window.mouseMove = false;
                break;
        }
    }
}