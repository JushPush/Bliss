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
	nDemo() {
		
	}

	nDemo(windowData dat) {windat = dat;}
	void OnCreate() override {
		
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
