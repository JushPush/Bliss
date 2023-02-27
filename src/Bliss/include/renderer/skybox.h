#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <string>

const unsigned int width = 800;
const unsigned int height = 800;

struct Skybox {
    float* skyboxVertices;
    unsigned int* skyboxIndices;
    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
    unsigned int cubemapTexture;
};

Skybox CreateSkybox();

void InitSkybox(Skybox& skybox);
void RenderSkybox(Skybox& skybox);