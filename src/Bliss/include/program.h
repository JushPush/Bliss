/* date = February 1st 2023 8:38 am */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "graphics/window.h"
#include "input/input.h"

#include "defines.h"

#include <iostream>
#include <cstring>

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

    // Services
    void* networking;
    void* audio;

    _program() {
        //glfwSetKeyCallback(window[0]->getWindow(), key_callback);
        //d_log("test", LogType::Error);
    };
} program;

#endif //PROGRAM_H
