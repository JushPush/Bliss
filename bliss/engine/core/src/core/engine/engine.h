#pragma once

#include <iostream>
#include <vector>

#include "module.h"

namespace Punji
{
    class Engine
    {
    public:
        Engine();

        void Init();
        void Shutdown();

    private:
        std::vector<Module> _modules;
    };
}