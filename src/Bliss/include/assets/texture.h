#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

struct Texture
{
    GLuint texture;
};

Texture CreateTexture(const std::string& fileName);

void BindTexture(Texture& texture);

void DeleteTexture(Texture& texture);