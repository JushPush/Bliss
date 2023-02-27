#include <Bliss.h>

glm::vec3 polarVector(float p, float y)
{
    // this form is already normalized
    return glm::vec3(std::cos(y) * std::cos(p),
                     std::sin(p),
                     std::sin(y) * std::cos(p));
}



Window demoWindow;

// TODO: MAKE TRANSFORM INDEPENDENT FROM CAMERA! Once everything is binded to a single object, everything will be easier.

Transform transform;



int main() {
	demoWindow = CreateWindow(0,0,800,600,"Bliss Demo Window (DOD Build)", false);
	InitWindow(demoWindow);

	SDL_SetRelativeMouseMode(SDL_FALSE);

	SDL_WarpMouseInWindow(demoWindow.window, demoWindow.width / 2, demoWindow.height / 2);


	Mesh testMesh("./res/teapot.obj");

	Shader shader("./res/basicShader");
	Shader skyboxShader("./res/skybox/skybox");

	Texture texture("./res/bricks.jpg");
	Camera camera = CreateCamera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)demoWindow.width/(float)demoWindow.height, 0.1f, 100.0f);

	Skybox skybox = CreateSkybox();
	InitSkybox(skybox);

	#define RESET_MOUSE SDL_WarpMouseInWindow(demoWindow.window, demoWindow.width / 2, demoWindow.height / 2);

	const float sensitivity = 0.001f; 

	RESET_MOUSE
	
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

		if (demoWindow.mouseMove) {
			//RESET_MOUSE
		}

		//camera.forward = polarVector(glm::radians(input.mouse.pitch), glm::radians(input.mouse.yaw));

		ClearWindow(demoWindow, 1.0, 1.0, 1.0, 1.0);

		transform.GetRot()->y = counter * 0.25;

		shader.Bind();
		texture.Bind();
		shader.Update(transform, camera);
		testMesh.Render();

		skyboxShader.Bind();
		skyboxShader.Update(transform, camera);
		RenderSkybox(skybox);

		SwapBuffers(demoWindow);
		//

		counter += 0.01f;
	}

	shader.Unload();
	skyboxShader.Unload();
	texture.Unload();

	DestroyWindow(demoWindow);

	return 0;
}
