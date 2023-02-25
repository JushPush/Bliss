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

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

static const unsigned int MESH_NUM_BUFFERS = 4;

struct Mesh {
    GLuint VAO = 0;
    GLuint VBO[MESH_NUM_BUFFERS] = {};
    unsigned int numIndices = 0;
    unsigned int *indices = 0;
};

Mesh CreateMesh(const std::string& fileName);
Mesh CreateMesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

void InitMesh(Mesh& mesh, const IndexedModel& model);
void RenderMesh(Mesh& mesh);