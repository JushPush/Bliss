#ifndef ERROR_H
#define ERROR_H

#include "../../logger.h"

static void error_callback(int error, const char* description) {
    std::cout << "ERROR " << error << " : " << description << std::endl;
    //d_log("ERROR " + std::to_string(error) + " : " + description, LogType::Error);
}

#endif