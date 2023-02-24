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
	Shader* shaderProgram;
	Shader* skyboxShader;
	Camera camera;

	Skybox* _skybox;

	nDemo() {
		
	}

	nDemo(windowData dat) {windat = dat;}
	void OnCreate() override {
		shaderProgram = new Shader("./res/basicShader.vs", "./res/basicShader.fs");
		skyboxShader = new Shader("./res/skybox/skybox.vs", "./res/skybox/skybox.fs");
		
		shaderProgram->Activate();
		skyboxShader->Activate();
		
		/*_skybox = new Skybox();
		_skybox->Init();
		monkey = new Mesh("./res/teapot.obj");
		skybox = new Shader("./res/skybox/skybox");
		shader = new Shader("./res/basicShader");
		texture = new Texture("./res/bricks.jpg");*/
		//camera = Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)this->windat.width/(float)this->windat.height, 0.1f, 100.0f);
	}

	void OnDestroy() override {
	}

	void Input(double time) override {
		/*if (input.isKeyPressed(KeyboardKey::KEY_ESCAPE))
			this->Close();
		
		if (input.isKeyPressed(KeyboardKey::KEY_W)) {
			glm::vec3 pos = camera.GetPosition();
			pos.z += 0.1;
			camera.SetPosition(pos);
		}
		if (input.isKeyPressed(KeyboardKey::KEY_A)) {
			glm::vec3 pos = camera.GetPosition();
			pos.x += 0.1;
			camera.SetPosition(pos);
		}
		if (input.isKeyPressed(KeyboardKey::KEY_S)) {
			glm::vec3 pos = camera.GetPosition();
			pos.z -= 0.1;
			camera.SetPosition(pos);
		}
		if (input.isKeyPressed(KeyboardKey::KEY_D)) {
			glm::vec3 pos = camera.GetPosition();
			pos.x -= 0.1;
			camera.SetPosition(pos);
		}
		if (input.isKeyPressed(KeyboardKey::KEY_UP)) {
			glm::vec3 pos = camera.GetPosition();
			pos.y += 0.1;
			camera.SetPosition(pos);
		}
		if (input.isKeyPressed(KeyboardKey::KEY_DOWN)) {
			glm::vec3 pos = camera.GetPosition();
			pos.y -= 0.1;
			camera.SetPosition(pos);
		}*/
	}

	void Update(double time) override {
		float ratio;
        int width, height;

		//transform.GetRot()->y = time * 0.25;

		//skybox->Bind();
		//shader->Bind();
		//skybox->Update(transform, camera);
		//texture->Bind();
		//shader->Update(transform, camera);
	}

	void Render() override {
		//objectManager->Render();
		//_skybox->Render();
		//monkey->Render();
	}
};

int main() {
	//program.networker->BeginConnection();

	program.window[0] = new nDemo(data);
	program.window[0]->Init();

	return 0;
}
