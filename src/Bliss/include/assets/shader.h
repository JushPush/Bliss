#pragma once

#include <GL/glew.h>

#include <iostream>
#include <string>
#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../entities/camera.h"

static const unsigned int S_NUM_SHADERS = 2;
static const unsigned int S_NUM_UNIFORMS = 3;

struct Shader
{
    GLuint program;
    GLuint shaders[S_NUM_SHADERS];
    GLuint uniforms[S_NUM_UNIFORMS];
};

Shader CreateShader(const std::string& path);

GLuint GLCreateShader(const std::string& text, unsigned int type);

void BindShader(Shader& shader);
void UpdateShader(Shader& shader, const Transform& transform, const Camera& camera);

void DeleteShader(Shader& shader);

std::string LoadShader(const std::string& fileName);
void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
