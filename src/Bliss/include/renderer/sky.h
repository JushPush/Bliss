#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>
#include <string>



class Skybox {
public:
    const unsigned int width = 800;
    const unsigned int height = 800;

    float* skyboxVertices;

    unsigned int* skyboxIndices;

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;

    unsigned int cubemapTexture;

    Skybox();

    void Init();
    void Render();
};