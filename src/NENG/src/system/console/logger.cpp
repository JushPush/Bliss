#include <system/console/logger.h>

void d_log(std::string message, LogType ltype) {
    switch (ltype)
    {
    case LogType::Status:
        std::cout << message << std::endl;
        break;
    case LogType::Warning:
        std::cout << ANSI_COLOR_YELLOW << message << ANSI_COLOR_RESET << std::endl;
        break;
    case LogType::Error:
        std::cout << ANSI_COLOR_RED << message << ANSI_COLOR_RESET << std::endl;
        break;
    default:
        break;
    }
}