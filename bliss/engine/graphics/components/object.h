#pragma once

#include "../data/mesh.h"
#include "../data/shader.h"
#include "../data/texture.h"

#include "transform.h"

class Object
{
public:
    Object(Shader shader, Texture texture, Mesh mesh);

    void SetShader(Shader shader);
    void SetTexture(Texture texture);
    void SetMesh(Mesh mesh);

    void Update(const Camera& camera) { _shader.Bind(); _texture.Bind(); _shader.Update(_transform, camera); }
    void Render() { _mesh.Render(); }

    Transform* getTransform() { return &_transform; }

protected:
private:
    Shader _shader;
    Texture _texture;
    Mesh _mesh;

    Transform _transform;
};