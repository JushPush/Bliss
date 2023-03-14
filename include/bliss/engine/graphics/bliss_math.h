#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Vertex {
    glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

Vertex CreateVertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal);

typedef struct v2 {
    double x;
    double y;
}
v2;

v2 _v2(double x, double y);

typedef struct rect {
    v2 start;
    v2 end;
}
rect;

rect _rect(v2 start, v2 end);

#define v2(x,y) _v2(x,y)
#define rect(a,b) _rect(a,b)