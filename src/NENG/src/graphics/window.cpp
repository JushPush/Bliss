#include <graphics/window.h>

void Window::error_callback(int error, const char* description) {
    
}



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

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    window = glfwCreateWindow(windat.width, windat.height, windat.title.c_str(), NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        this->Destroy();
        exit(EXIT_FAILURE);
        return false;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    glViewport( 0, 0, 400, 400 );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	// see https://www.opengl.org/sdk/docs/man2/xhtml/glOrtho.xml
	//glOrtho(0.0,400.0,0.0,400.0,0.0,1.0); // this creates a canvas you can do 2D drawing on
    glOrtho(0.0, this->windat.width, 0.0, this->windat.height, 0.0, 1.0);

    //gluOrtho2D (0.0, 200.0, 0.0, 150.0);
    this->OnCreate();

    // NOTE: OpenGL error checks have been omitted for brevity
 
    // Shader Stuff (yoinked from the getting started glfw tutorial)
    /*
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    */
 
    //program = glCreateProgram();
    //glAttachShader(program, vertex_shader);
    //glAttachShader(program, fragment_shader);
    //glLinkProgram(program);
 
    /*
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));
    */

    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);

        glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClear(GL_COLOR_BUFFER_BIT);

        double time = glfwGetTime();

        //glUseProgram(program);
        this->Update(time);


        glfwSwapBuffers(window);
        glfwPollEvents();

        
    }
    return true;
}

void Window::Destroy() {
    this->OnDestroy();
    glfwTerminate();
}