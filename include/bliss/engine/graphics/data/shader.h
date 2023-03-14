#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../components/transform.h"
#include "asset.h"

#include "stb_image.h"

static const unsigned int S_NUM_SHADERS = 2;
static const unsigned int S_NUM_UNIFORMS = 3;

class Shader : public Asset 
{
public:
    GLuint program;
    GLuint shaders[S_NUM_SHADERS];
    GLuint uniforms[S_NUM_UNIFORMS];

    Shader() {}

    Shader(const std::string& fileName);

    void Bind();
    void Update(const Transform& transform, const Camera& camera);
    void Render() {};

    void Unload();
};

GLuint GLCreateShader(const std::string& text, unsigned int type);

std::string LoadShaderSRC(const std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
