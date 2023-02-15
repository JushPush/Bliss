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
	nDemo() {
		
	}
	
	void OnCreate() override {
		
	}

	void OnDestroy() override {
		//std::cout << "b" << std::endl;
	}

	void KeyPress(int key, int scancode, int action, int mods, bool mouse) override {
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(this->getWindow(),GLFW_TRUE);
	}

	void Update(double time) override {

		if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			this->renderer.SetPixel(input.getMousePosition().x, input.getMousePosition().y, rgb(255,0,0));
		}
	}

	void Render() override {
		this->renderer.DrawBox(rect(v2(0,0),v2(this->windat.width,this->windat.height / 2)),rgb(251,64,174), true);
	}
};

int main() {
	program.window[0] = new nDemo();
	program.window[0]->Init();

	return 0;
}
