#ifndef CAMERA_H
#define CAMERA_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    glm::mat4 view, proj, cameraMatrix;

	GLfloat fovY, zNear, zFar;

	void CalcCameraMatrix();
	
public:
	Camera();
	Camera(GLfloat fovX, GLfloat width, GLfloat height, GLfloat near, GLfloat far);
	void UpdateProj(GLfloat fovX, GLfloat width, GLfloat height, GLfloat near, GLfloat far);
	void UpdateView(glm::mat4 viewMat);
	glm::mat4 GetProj(), GetView(), GetCameraMatrix();
	~Camera();
};

#endif