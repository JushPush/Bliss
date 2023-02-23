#ifndef OBJECT_H
#define OBJECT_H

#include <linmath.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <string>
#include <vector>

#pragma region OBJ_LOADER
struct OBJIndex
{
    unsigned int vertexIndex;
    unsigned int uvIndex;
    unsigned int normalIndex;
    
    bool operator<(const OBJIndex& r) const { return vertexIndex < r.vertexIndex; }
};

class IndexedModel
{
public:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;
    
    void CalcNormals();
};

class OBJModel
{
public:
    std::vector<OBJIndex> OBJIndices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    bool hasUVs;
    bool hasNormals;
    
    OBJModel(const std::string& fileName);
    
    IndexedModel ToIndexedModel();
private:
    unsigned int FindLastVertexIndex(const std::vector<OBJIndex*>& indexLookup, const OBJIndex* currentIndex, const IndexedModel& result);
    void CreateOBJFace(const std::string& line);
    
    glm::vec2 ParseOBJVec2(const std::string& line);
    glm::vec3 ParseOBJVec3(const std::string& line);
    OBJIndex ParseOBJIndex(const std::string& token, bool* hasUVs, bool* hasNormals);
};
#pragma endregion

class Object {
public:
	Object() {}

	virtual void Input() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};

#pragma region Camera stuff
struct Camera
{
public:
	Camera() {}
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		this->pos = pos;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	inline glm::vec3 GetPosition() const
	{
		return pos;
	}

	inline void SetPosition(glm::vec3 position) 
	{
		this->pos = position;
	}

	//void MoveForward(float amt)
	//{
	//	pos += forward * amt;
	//}

	//void MoveRight(float amt)
	//{
	//	pos += glm::cross(up, forward) * amt;
	//}

	//void Pitch(float angle)
	//{
	//	glm::vec3 right = glm::normalize(glm::cross(up, forward));

	//	forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
	//	up = glm::normalize(glm::cross(forward, right));
	//}

	//void RotateY(float angle)
	//{
	//	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	//	glm::mat4 rotation = glm::rotate(angle, UP);

	//	forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
	//	up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	//}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

struct Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->pos = pos;
		this->rot = rot;
		this->scale = scale;
	}

	inline glm::mat4 GetModel() const
	{
		glm::mat4 posMat = glm::translate(pos);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotX = glm::rotate(rot.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rot.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rot.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}

	inline glm::mat4 GetMVP(const Camera& camera) const
	{
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();

		return VP * M;//camera.GetViewProjection() * GetModel();
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec3* GetRot() { return &rot; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPos(glm::vec3& pos) { this->pos = pos; }
	inline void SetRot(glm::vec3& rot) { this->rot = rot; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scale;
};
#pragma endregion

struct Vertex {
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh {
public:
    Mesh() {}
    Mesh(const std::string& fileName);
    Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);

    void Render();

    virtual ~Mesh();
protected:
private:
    static const unsigned int NUM_BUFFERS = 4;

    void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;
    unsigned int *indices;
};

#endif