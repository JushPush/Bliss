#include <NENG.h>

windowData data = {
	0,
	0,
	800,
	600,
	"Window"
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
	nDemo() {
		
	}
	
	void OnCreate() override {
		d_log("Window Test", LogType::Error);
	}

	void OnDestroy() override {
		d_log("Window Destroyed", LogType::Warning);
	}

	void KeyPress(int key, int scancode, int action, int mods) override {
		//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	}

	bool button_pressed_last = false;

	double x;
	double y;

	void Update(double time) override {
		//d_log("Time:" + std::to_string(time) + "s", LogType::Status);

		unsigned int VBO;
		glGenBuffers(1, &VBO);  

		glBindBuffer(GL_ARRAY_BUFFER, VBO);  
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//this->renderer.DrawLine(0, 0, 100, 100);

		if (input.isKeyPressed(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(this->getWindow(), GLFW_TRUE);

		if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
			if (!button_pressed_last) {
				x = input.mouse.x;
				y = input.mouse.y;
				button_pressed_last = true;

			}

			this->renderer.DrawLine(x, y, input.mouse.x, input.mouse.y);
		} else {
			button_pressed_last = false;
		}

		//glDrawArrays(GL_TRIANGLES, 0, 3);
	}
};

int main() {
	program.window[0] = new nDemo();

	//Window *demo = new nDemo();
	//Window window = Window(data);

	d_log("Window Initializing", LogType::Status);
	program.window[0]->Init();

	program.window[0]->Destroy();

	return 0;
}
