#pragma once

#include <string>

/// @brief Extension to the Bliss library which allows for further open-source integration
class Module
{
public:
    virtual int Init() { return 0; }
    virtual int Shutdown() { return 0; }

protected:
private:
    std::string module_version;
    int module_version_int;
};