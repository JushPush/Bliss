#include <assets/mesh.h>

Mesh CreateMesh(const std::string& fileName)
{
    //Mesh* mesh = (Mesh*)malloc(sizeof(Mesh));
    Mesh mesh = Mesh();

    InitMesh(mesh, OBJModel(fileName).ToIndexedModel());

    return mesh;
}

Mesh CreateMesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel model;
    Mesh mesh;

    for (unsigned int i = 0; i < numVertices; i++)
    {
        model.positions.push_back(vertices[i].pos);
		model.texCoords.push_back(vertices[i].texCoord);
		model.normals.push_back(vertices[i].normal);
    }

    for(unsigned int i = 0; i < numIndices; i++)
        model.indices.push_back(indices[i]);
    
    InitMesh(mesh, model);

    return mesh;
}

void InitMesh(Mesh& mesh, const IndexedModel& model)
{
    mesh.numIndices = model.indices.size();

    glGenVertexArrays(1, &mesh.VAO);
	glBindVertexArray(mesh.VAO);

	glGenBuffers(MESH_NUM_BUFFERS, mesh.VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.VBO[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void RenderMesh(Mesh& mesh)
{
    glBindVertexArray(mesh.VAO);

    glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}