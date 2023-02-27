#pragma once

#include "../assets/mesh.h"
#include "../assets/shader.h"
#include "../assets/texture.h"

class Object
{
public:
    Object(Shader shader, Texture texture, Mesh mesh);

    void SetShader(Shader shader);
    void SetTexture(Texture texture);
    void SetMesh(Mesh mesh);

    void Update();
    void Render();

protected:
private:
    Shader _shader;
    Texture _texture;
    Mesh _mesh;
};