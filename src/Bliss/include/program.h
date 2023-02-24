/* date = February 1st 2023 8:38 am */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "graphics.h"
#include "input.h"

#include "defines.h"

#include <iostream>
#include <cstring>

#include "networking.h"

struct _program {
    std::string prog_name;

    // System
    struct {
        std::string _os     = "";
        std::string _cpu    = "";
        std::string _gpu    = "";
        int _ram            = 0;
    } sys_info;
    
    Window* window[MAX_WINDOWS] = {};

    char* console_buffer[BUF_CHAR_MAX] = {};

    double previousTime;

    Networker* networker = new Networker();
    void* audio;

    _program() {
        
    };
} program;

#endif //PROGRAM_H
