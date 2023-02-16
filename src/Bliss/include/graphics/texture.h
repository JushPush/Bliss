#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture;
};

#endif