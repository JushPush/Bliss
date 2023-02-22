#include <Bliss.h>

windowData data = {
	0,
	0,
	800,
	600,
	"Bliss Demo Window",
	false
};
 
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

class nDemo : public Window {
public:
	/*Vertex vertices[3] = {
		{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
		{  0.6f, -0.4f, 0.f, 1.f, 0.f },
		{   0.f,  0.6f, 0.f, 0.f, 1.f }
	};*/
	Vertex vertices[4] = {
		{ -1.0f, -1.0f, 1.f, 0.f, 0.f },
		{  1.0f, -1.0f, 0.f, 1.f, 0.f },
		{  1.0f,  1.0f, 0.f, 0.f, 1.f },
		{ -1.0f,  1.0f, 0.f, 0.f, 1.f }
	};
	Mesh mesh;
	Shader shader;
	nDemo() {
		
	}
	

	nDemo(windowData dat) {windat = dat;}
	void OnCreate() override {
		//shader = Shader(vertex_shader_text, fragment_shader_text, vertices);

		//mesh = Mesh(vertices);
	}

	void OnDestroy() override {
	}

	void Input() override {
		if (input.isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(this->getWindow(),GLFW_TRUE);
	}

	void Update(double time) override {
		float ratio;
        int width, height;
 
        glfwGetFramebufferSize(this->getWindow(), &width, &height);
        ratio = width / (float) height;

		//mesh.Update(glfwGetTime(), ratio, mvp_location);
        //shader.Update();
	}

	void Render() override {
		shader.Render();
		mesh.Render();
	}
};

int main() {
	program.networker->BeginConnection();

	program.window[0] = new nDemo(data);
	program.window[0]->Init();

	return 0;
}
