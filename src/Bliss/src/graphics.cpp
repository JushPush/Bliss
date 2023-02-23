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
Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram();
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	m_uniforms[0] = glGetUniformLocation(m_program, "MVP");
	m_uniforms[1] = glGetUniformLocation(m_program, "Normal");
	m_uniforms[2] = glGetUniformLocation(m_program, "lightDirection");
}

Shader::~Shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(m_program, m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 Normal = transform.GetModel();

	glUniformMatrix4fv(m_uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(m_uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(m_uniforms[2], 0.0f, 0.0f, 1.0f);
}

std::string Shader::LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}

Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    if(data == NULL)
		std::cerr << "Unable to load texture: " << fileName << std::endl;
        
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
        
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
#pragma endregion