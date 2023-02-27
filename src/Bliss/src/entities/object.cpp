#include <entities/object.h>

Object::Object(Shader shader, Texture texture, Mesh mesh) {
    _shader = shader;
    _texture = texture;
    _mesh = mesh;
}

void Object::SetShader(Shader shader) {}
void Object::SetTexture(Texture texture) {}
void Object::SetMesh(Mesh mesh) {}

void Object::Update() 
{
    _shader.Bind();
    // _shader.Update(transform, camera);
}
void Object::Render() 
{

}