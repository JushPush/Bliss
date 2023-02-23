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
	Mesh* mesh;
	Mesh* monkey;
	Shader* shader;
	Texture* texture;
	Transform transform;
	Camera camera;

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
		monkey = new Mesh("./res/monkey3.obj");
		shader = new Shader("./res/basicShader");
		texture = new Texture("./res/bricks.jpg");
		camera = Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)this->windat.width/(float)this->windat.height, 0.1f, 100.0f);
	}

	void OnDestroy() override {
	}

	void Input() override {
		//if (input.isKeyPressed(GLFW_KEY_ESCAPE))
			//glfwSetWindowShouldClose(this->getWindow(),GLFW_TRUE);
	}

	void Update(double time) override {
		float ratio;
        int width, height;

		transform.GetRot()->y = time * 0.25;

		shader->Bind();
		texture->Bind();
		shader->Update(transform, camera);
	}

	void Render() override {
		mesh->Render();
		monkey->Render();
	}
};

int main() {
	program.networker->BeginConnection();

	program.window[0] = new nDemo(data);
	program.window[0]->Init();

	return 0;
}
