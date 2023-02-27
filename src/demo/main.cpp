#include <Bliss.h>


#include <SDL2/SDL_ttf.h>

// clamp pitch to [-89, 89]
float clampPitch(float p)
{
    return p > 89.0f ? 89.0f : (p < -89.0f ? -89.0f : p);   
}

// clamp yaw to [-180, 180] to reduce floating point inaccuracy
float clampYaw(float y)
{
    float temp = (y + 180.0f) / 360.0f;
    return y - ((int)temp - (temp < 0.0f ? 1 : 0)) * 360.0f;
}

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

	SDL_ShowCursor(SDL_FALSE);

	SDL_SetRelativeMouseMode(SDL_FALSE);

	SDL_WarpMouseInWindow(demoWindow.window, demoWindow.width / 2, demoWindow.height / 2);


	Mesh testMesh("./res/teapot.obj");

	Shader shader("./res/basicShader");
	Shader skyboxShader("./res/skybox/skybox");
	Texture texture("./res/bricks.jpg");

	Object object = Object(shader, texture, testMesh);

	Camera camera = CreateCamera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, (float)demoWindow.width/(float)demoWindow.height, 0.1f, 100.0f);

	Skybox skybox = CreateSkybox();
	InitSkybox(skybox);

	#define RESET_MOUSE SDL_WarpMouseInWindow(demoWindow.window, demoWindow.width / 2, demoWindow.height / 2);

	const float sensitivity = 0.25f; 

	RESET_MOUSE

	float yaw = 0.0f, pitch = 0.0f;


	#pragma region FONT
	#pragma endregion



	Uint32 counter = SDL_GetTicks();

	int frames_drawn = 0;
	Uint32 fps_counter = 0;
	int fps = 0;
	Uint32 prev_ticks = SDL_GetTicks();

	while (demoWindow.running) {
		float deltaTime = (SDL_GetTicks() - counter) / 1000.0f;
		counter = SDL_GetTicks();

		Uint32 ticks_now = SDL_GetTicks();
		Uint32 diff = ticks_now - prev_ticks;
		fps_counter += diff;
		prev_ticks = ticks_now;

		if(fps_counter >= 1000) {
			fps = frames_drawn / (fps_counter/1000);

			std::cout << "FPS: " << fps << std::endl;

			frames_drawn = 0;
			fps_counter = 0;
		}

		CullEvent(demoWindow);

		if (isKeyPressed(KeyboardKey::KEY_ESCAPE)) {
			demoWindow.running = false;
		}

		float CameraSpeed = 2.5 * deltaTime;

		if (isKeyPressed(KeyboardKey::KEY_W)) {
			camera.pos += CameraSpeed * camera.forward;
		}
		if (isKeyPressed(KeyboardKey::KEY_A)) {
			camera.pos -= glm::normalize(glm::cross(camera.forward, camera.up)) * CameraSpeed;
		}
		if (isKeyPressed(KeyboardKey::KEY_S)) {
			camera.pos -= CameraSpeed * camera.forward;
		}
		if (isKeyPressed(KeyboardKey::KEY_D)) {
			camera.pos += glm::normalize(glm::cross(camera.forward, camera.up)) * CameraSpeed;
		}
		if (isKeyPressed(KeyboardKey::KEY_UP)) {
			camera.pos.y += 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_DOWN)) {
			camera.pos.y -= 0.1;
		}
		if (isKeyPressed(KeyboardKey::KEY_Q)) {
			object.getTransform()->GetScale()->x += deltaTime * 2.5;
		}
		if (isKeyPressed(KeyboardKey::KEY_E)) {
			object.getTransform()->GetScale()->x -= deltaTime * 2.5;
		}

		yaw = clampYaw(yaw + sensitivity * input.mouse.x);
		pitch = clampPitch(pitch - sensitivity * input.mouse.y);

		camera.forward = polarVector(glm::radians(pitch), glm::radians(yaw));

		RESET_MOUSE

		ClearWindow(demoWindow, 1.0, 1.0, 1.0, 1.0);

		//SDL_RenderCopy(demoWindow.renderer, Message, NULL, &Message_rect);

		object.getTransform()->GetRot()->y = counter / 1000.0 * 0.25;
		object.getTransform()->GetRot()->z = counter / 1000.0 * -0.25;

		skyboxShader.Bind();
		skyboxShader.Update(transform, camera);
		RenderSkybox(skybox);

		object.Update(camera);

		object.Render();

		SwapBuffers(demoWindow);

		frames_drawn += 1;
	}

	shader.Unload();
	skyboxShader.Unload();
	texture.Unload();

	DestroyWindow(demoWindow);

	return 0;
}
