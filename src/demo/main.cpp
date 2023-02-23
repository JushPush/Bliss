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
	//ObjectManager* objectManager;
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
		//objectManager = new ObjectManager();
		monkey = new Mesh("./res/monkey3.obj");
		shader = new Shader("./res/basicShader");
		texture = new Texture("./res/bricks.jpg");
		camera = Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)this->windat.width/(float)this->windat.height, 0.1f, 100.0f);

		//objectManager->objects.push_back(monkey);
	}

	void OnDestroy() override {
	}

	void Input(double time) override {
		if (input.isKeyPressed(KeyboardKey::KEY_ESCAPE))
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
		//objectManager->Render();
		monkey->Render();
	}
};

int main() {
	//program.networker->BeginConnection();

	program.window[0] = new nDemo(data);
	program.window[0]->Init();

	return 0;
}
