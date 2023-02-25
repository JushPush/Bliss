#include <Bliss.h>

Window demoWindow;

Transform transform;

int main() {
	demoWindow = CreateWindow(0,0,800,600,"Bliss Demo Window (DOD Build)", false);
	InitWindow(demoWindow);

	Mesh* testMesh = CreateMesh("./res/teapot.obj");
	Shader shader = CreateShader("./res/basicShader");
	Texture texture = CreateTexture("./res/bricks.jpg");
	Camera camera = CreateCamera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)demoWindow.width/(float)demoWindow.height, 0.1f, 100.0f);


	float counter = 0.0f;

	while (demoWindow.running) {
		CullEvent(demoWindow);

		if (isKeyPressed(KeyboardKey::KEY_ESCAPE)) {
			demoWindow.running = false;
		}

		if (isKeyPressed(KeyboardKey::KEY_W)) {
			camera.pos.z += 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_A)) {
			camera.pos.x += 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_S)) {
			camera.pos.z -= 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_D)) {
			camera.pos.x -= 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_UP)) {
			camera.pos.y += 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_DOWN)) {
			camera.pos.y -= 0.1;
		}

		ClearWindow(demoWindow, 1.0, 1.0, 1.0, 1.0);

		transform.GetRot()->y = counter * 0.25;

		BindShader(shader);
		BindTexture(texture);

		UpdateShader(shader, transform, camera);

		RenderMesh(*testMesh);

		SwapBuffers(demoWindow);

		counter += 0.01f;
	}

	DeleteShader(shader);
	DeleteTexture(texture);

	DestroyWindow(demoWindow);

	return 0;
}
