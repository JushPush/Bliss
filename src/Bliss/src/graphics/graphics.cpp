#include <graphics/graphics.h>

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
void Renderer::DrawLine(v2 start, v2 end, rgb color, int point_size, double line_width) {
	glPointSize(point_size);
	glLineWidth(line_width); 
	glColor3f((color.r / 255.0), (color.g / 255.0), (color.b / 255.0));
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y,0.0);
	glVertex3f(end.x,end.y,0.0);
	glEnd();
}

bool Renderer::Init(GLFWwindow* window) {
	Resize(rect(v2(this->display.startx,this->display.starty),v2(this->display.width,this->display.height)), window);
	
	return true;
}

void Renderer::Update(GLFWwindow* window) {
	float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glPixelZoom(1.0, -1.0);
	//glRasterPos2f(0.0, 0.0);
	//glDrawPixels(this->display.width, this->display.height, GL_RGB, GL_UNSIGNED_BYTE, display.data);
}

void Renderer::PostUpdate(GLFWwindow* window) {
	glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::SetPixel(int x, int y, rgb color) {
	COLOR _color = convertRGB(color);
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = _color.bytes[0];
	display.data[t + 1] = _color.bytes[1];
	display.data[t + 2] = _color.bytes[2];
}

void Renderer::SetPixel(int x, int y, uint8_t color[3]) {
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = color[0];
	display.data[t + 1] = color[1];
	display.data[t + 2] = color[2];
}

void Renderer::ClearPixel(int x, int y) {
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = 0x00;
	display.data[t + 1] = 0x00;
	display.data[t + 2] = 0x00;
}

void Renderer::Clear() {
	free(display.data);
    display.data = new unsigned char[display.width * display.height * 3];

	for (int y = 0; y < this->display.height; ++y) {
		for (int x = 0; x < this->display.width; ++x) {
			ClearPixel(x,y);
		}
	}
}

void Renderer::Resize(rect disp, GLFWwindow* window) {
	display.startx = (int)disp.start.x;
    display.starty = (int)disp.start.y;
    display.width = (int)disp.end.x;
    display.height = (int)disp.end.y;

	Clear();

	glViewport( 0, 0, this->display.width, this->display.height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0,this->display.width,this->display.height,0,-1.0,1.0);
}

void Renderer::DrawBox(rect box, rgb color, bool fill) {
	for (int x = box.start.x; x < box.end.x; ++x) {
		for (int y = box.start.y; y < box.end.y; ++y) {
			SetPixel(x, y, color);
		}
	}
}
#pragma endregion

#pragma region Window
bool Window::Init() {
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
        // Initialization failed
        return false;
    }

    glfwSetErrorCallback(error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    window = glfwCreateWindow(windat.width, windat.height, windat.title.c_str(), NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        this->Destroy();
        exit(EXIT_FAILURE);
        return false;
    }

    glfwSetWindowUserPointer(window, this);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    begin_createWindow();

    glfwMakeContextCurrent(window);
    monitor = glfwGetPrimaryMonitor();

    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    gladLoadGL();
    glfwSwapInterval(0);

    renderer.Init(window);


    this->OnCreate();

    double previousTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

        double currentTime = glfwGetTime();
        frameCount++;
        // If a second has passed.
        if ( currentTime - previousTime >= 1.0 )
        {
            // Display the frame count here any way you want.
            std::cout << "Framerate: " << frameCount << " FPS" << std::endl;

            frameCount = 0;
            previousTime = currentTime;
        }

        renderer.Update(window);

        double time = glfwGetTime();

        this->Input();

        this->Update(time);

        this->Render();

        renderer.PostUpdate(window);
    }

    this->Destroy();
    return true;
}

void Window::Destroy() {
    this->OnDestroy();
    glfwTerminate();
}
#pragma endregion

#pragma region Shaders and Textures
Shader::Shader(const char* vertex_shader_text, const char* fragment_shader_text) {
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetAttribLocation(program, "vPos");
	vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    //glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
    //                    sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    //glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //                    sizeof(vertices[0]), (void*) (sizeof(float) * 2));
}

void Shader::Update() {
    glUseProgram(program);
}

void Shader::Render() {

}
#pragma endregion