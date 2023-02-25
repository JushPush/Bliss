#include <assets/shader.h>

#include <stb_image.h>

Shader CreateShader(const std::string& path)
{
    Shader shader = Shader();
    shader.program = glCreateProgram();
	shader.shaders[0] = GLCreateShader(LoadShader(path + ".vs"), GL_VERTEX_SHADER);
	shader.shaders[1] = GLCreateShader(LoadShader(path + ".fs"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < S_NUM_SHADERS; i++)
		glAttachShader(shader.program, shader.shaders[i]);

	glBindAttribLocation(shader.program, 0, "position");
	glBindAttribLocation(shader.program, 1, "texCoord");
	glBindAttribLocation(shader.program, 2, "normal");

	glLinkProgram(shader.program);
	CheckShaderError(shader.program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(shader.program);
	CheckShaderError(shader.program, GL_LINK_STATUS, true, "Invalid shader program");

	shader.uniforms[0] = glGetUniformLocation(shader.program, "MVP");
	shader.uniforms[1] = glGetUniformLocation(shader.program, "Normal");
	shader.uniforms[2] = glGetUniformLocation(shader.program, "lightDirection");

    return shader;
}

GLuint GLCreateShader(const std::string& text, unsigned int type)
{
    GLuint shader = glCreateShader(type);

    if(shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

    const GLchar* p[1];
    p[0] = text.c_str();
    GLint lengths[1];
    lengths[0] = text.length();

    glShaderSource(shader, 1, p, lengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

    return shader;
}

void BindShader(Shader& shader)
{
    glUseProgram(shader.program);
}
void UpdateShader(Shader& shader, const Transform& transform, const Camera& camera)
{
    glm::mat4 MVP = transform.GetMVP(camera);
	glm::mat4 Normal = transform.GetModel();

	glUniformMatrix4fv(shader.uniforms[0], 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(shader.uniforms[1], 1, GL_FALSE, &Normal[0][0]);
	glUniform3f(shader.uniforms[2], 0.0f, 0.0f, 1.0f);
}

void DeleteShader(Shader& shader)
{
    for(unsigned int i = 0; i < S_NUM_SHADERS; i++)
    {
        glDetachShader(shader.program, shader.shaders[i]);
        glDeleteShader(shader.shaders[i]);
    }

	glDeleteProgram(shader.program);
}

std::string LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());

    std::string output;
    std::string line;

    if (file.is_open())
    {
        while(file.good())
        {
            std::getline(file,line);
            output.append(line + "\n");
        }
    }
    else
    {
        std::cerr << "Unable to load shader: " << fileName << std::endl;
    }

    return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}
