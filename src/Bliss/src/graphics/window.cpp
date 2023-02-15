#include <graphics/window.h>

bool Window::Init() {
    if (!glfwInit())
    {
        //this->Destroy();
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
    glfwSwapInterval(1);

    renderer.Init(window);


    this->OnCreate();

    double previousTime = glfwGetTime();
    int frameCount = 0;

    while (!glfwWindowShouldClose(window))
    {
        //glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

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

        this->Update(time);

        this->Render();

        renderer.PostUpdate(window);
        //glUseProgram(program);
        
    }

    this->Destroy();
    return true;
}

void Window::Destroy() {
    this->OnDestroy();
    glfwTerminate();
}