#include <bliss_math.h>

Vertex CreateVertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal) {
    return Vertex {
        pos, texCoord, normal
    };
}

v2 _v2(double x, double y) {
    return v2 {x,y};
}

rect _rect(v2 start, v2 end) {
    return rect {start,end};
}