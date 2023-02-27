#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

#include "asset.h"

class Texture : public Asset
{
public:
    GLuint texture;

    Texture(const std::string& fileName);

    void Init() {};
    void Bind();
    void Render() {};
    void Unload();
};