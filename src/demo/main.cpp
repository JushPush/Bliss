#include <Bliss.h>

windowData data = {
	0,
	0,
	800,
	600,
	"Window",
	false
};

class nDemo : public Window {
public:
	
	Mesh mesh;

	Shader shader;

	nDemo() {
		
	}
	void OnCreate() override {
		
		Vertex verticies[] = {
			Vertex(glm::vec3(-0.5,-0.5,0)),
			Vertex(glm::vec3(0,0.5,0)),
			Vertex(glm::vec3(0.5,-0.5,0))
		};
		shader = Shader();

		shader.Init();
		mesh = Mesh(verticies, sizeof(verticies)/sizeof(verticies[0]));
	}

	void OnDestroy() override {
		//std::cout << "b" << std::endl;
	}

	void Input() override {
		if (input.isKeyPressed(GLFW_KEY_ESCAPE))
			glfwSetWindowShouldClose(this->getWindow(),GLFW_TRUE);
	}

	void Update(double time) override {

		if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			this->renderer.SetPixel(input.getMousePosition().x, input.getMousePosition().y, rgb(255,0,0));
		}
		mesh.Update();
	}

	void Render() override {
		this->renderer.DrawBox(rect(v2(0,0),v2(this->windat.width,this->windat.height / 2)),rgb(251,64,174), true);
		shader.Bind();
		mesh.Render();
	}
};

int main() {
	program.networker->BeginConnection();
	//Host* host = new Host();

	program.window[0] = new nDemo();
	program.window[0]->Init();

	//program_loop();

	return 0;
}
