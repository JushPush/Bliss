#include <graphics.h>

#include <GL/glew.h>
#include <iostream>
#include <fstream>

#include <stb_image.h>

COLOR convertRGB(rgb _rgb_) {
    return COLOR {
        {
            (uint8_t)_rgb_.r,
            (uint8_t)_rgb_.g,
            (uint8_t)_rgb_.b
        }
    };
}

rgb _rgb(int red, int green, int blue) {
    return rgb { red, green, blue };
}

#pragma region Renderer

#pragma endregion

#pragma region Window
bool Window::Init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        //return false; 
    }

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

    window = SDL_CreateWindow(this->windat.title.c_str(), this->windat.x, this->windat.y, this->windat.width, this->windat.height, SDL_WINDOW_OPENGL);// glfwCreateWindow(windat.width, windat.height, windat.title.c_str(), NULL, NULL);
    if (!window) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        return false; }

    glContext = SDL_GL_CreateContext(window);

    GLenum res = glewInit();

    if (res != GLEW_OK) {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

    /*renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "ERROR: SDL failed to initialize" << std::endl << "SDL Error: " << SDL_GetError() << std::endl;
        return false; }*/

    this->OnCreate();

    running = true;

    float counter = 0.0f;

    while (isRunning())
    {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_KEYDOWN:
                    input.inputs._keys[event.key.keysym.scancode] = true;
                    break;
                case SDL_KEYUP:
                    input.inputs._keys[event.key.keysym.scancode] = false;
                    break;
                case SDL_QUIT:
                    running = false;
                    break;
                default:
                    break;
            }
        }

        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        //SDL_RenderClear(renderer);

        this->Clear(0.0f, 0.0f, 0.0f, 1.0f);

        float sinCounter = sinf(counter);
        float absSinCounter = abs(sinCounter);

        this->Input(counter);

        this->Update(counter);

        this->Render();

        this->SwapBuffers();
        SDL_Delay(1);
        counter += 0.01f;

        //SDL_RenderPresent(renderer);
    }

    this->Destroy();
    return true;
}

Window::~Window() {
    SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::Clear(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Close() {
    this->running = false;
}

void Window::Destroy() {
    this->OnDestroy();
    //glfwTerminate();
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}
#pragma endregion

#pragma region Shaders and Textures

#pragma endregion