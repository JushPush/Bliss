/* date = February 1st 2023 8:38 am */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "graphics/graphics.h"
#include "input/input.h"

#include "defines.h"

#include <iostream>
#include <cstring>

#include "networking/networking.h"

struct _program {
    std::string prog_name;

    // System
    struct {
        std::string _os     = "";
        std::string _cpu    = "";
        std::string _gpu    = "";
        int _ram            = 0;
    } sys_info;

    // IDK Objects IG
    Window* window[MAX_WINDOWS] = {};

    // Buffers
    char* console_buffer[BUF_CHAR_MAX] = {};

    double previousTime;

    // Services
    Networker* networker = new Networker();
    void* audio;

    _program() {
        previousTime = glfwGetTime();
        //glfwSetKeyCallback(window[0]->getWindow(), key_callback);
        //d_log("test", LogType::Error);
    };
} program;

int program_loop() {
    double currentTime = glfwGetTime();
    /*frameCount++;
    // If a second has passed.
    if ( currentTime - previousTime >= 1.0 )
    {
        // Display the frame count here any way you want.
        std::cout << "Framerate: " << frameCount << " FPS" << std::endl;

        frameCount = 0;
        previousTime = currentTime;
    }*/

    for (Window* win : program.window) {
        if (!glfwWindowShouldClose(win->getWindow())) {
            win->renderer.Update(win->getWindow());

            win->Input();
            win->Update(currentTime);
            win->Render();
            
            win->renderer.PostUpdate(win->getWindow());
        } else {
            win->Destroy();
        }
    }
    return 0;
}

#endif //PROGRAM_H
