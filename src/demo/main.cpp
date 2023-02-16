#include <Bliss.h>

windowData data = {
	0,
	0,
	800,
	600,
	"Bliss Demo Window",
	false
};

class nDemo : public Window {
public:
	
	Mesh *mesh;

	Shader *shader;

	Camera camera;

	Transform transform;

	nDemo() {
		
	}

	nDemo(windowData dat) {windat = dat;}
	void OnCreate() override {
		Vertex vertices[] =
		{
			Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
			Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
			Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
			Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),

			Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
			Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
			Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
			Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),

			Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
			Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
			Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
			Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),

			Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
			Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
			Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
			Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),

			Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
			Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
			Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
			Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),

			Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
			Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
		};

		unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };

		mesh = new Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));

		shader = new Shader("./res/basicShader");
		camera = Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)this->windat.width/(float)this->windat.height, 0.1f, 100.0f);
	}

	void OnDestroy() override {
	}

	void Input() override {
		if (input.isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(this->getWindow(),GLFW_TRUE);
	}

	void Update(double time) override {

		if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			this->renderer.SetPixel(input.getMousePosition().x, input.getMousePosition().y, rgb(255,0,0));
		}
		//mesh.Update();
	}

	void Render() override {
		this->renderer.DrawBox(rect(v2(0,0),v2(this->windat.width,this->windat.height / 2)),rgb(251,64,174), true);
		shader->Bind();

		shader->Update(transform, camera);
		mesh->Render();
	}
};

int main() {
	program.networker->BeginConnection();
	//Host* host = new Host();

	program.window[0] = new nDemo(data);
	program.window[0]->Init();

	//program_loop();

	return 0;
}
