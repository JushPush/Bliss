#pragma once

#include <linmath.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <vector>
#include <cstring>

#include <iostream>

#include "../bliss_math.h"

#include "obj_loader.h"

#include "asset.h"

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

static const unsigned int MESH_NUM_BUFFERS = 4;

class Mesh : public Asset {
public:
    GLuint VAO;
    GLuint VBO[MESH_NUM_BUFFERS];
    unsigned int numIndices;
    unsigned int *indices;

    Mesh() {}

    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

    void Init() {};
    void Bind() {};
    void Unload() {};

    void InitMesh(const IndexedModel& model);

    void Render();
};