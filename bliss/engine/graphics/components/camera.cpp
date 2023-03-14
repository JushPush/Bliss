#include "camera.h"

Camera CreateCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
    return Camera {
        pos, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::perspective(fov, aspect, zNear, zFar)
    };
}

glm::mat4 GetViewProjection(const Camera& camera) {
    return camera.projection * glm::lookAt(camera.pos, camera.pos + camera.forward, camera.up);
}