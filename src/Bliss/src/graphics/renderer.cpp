#include <graphics/renderer.h>

void Renderer::DrawLine(v2 start, v2 end, rgb color, int point_size, double line_width) {
	glPointSize(point_size);
	glLineWidth(line_width); 
	glColor3f((color.r / 255.0), (color.g / 255.0), (color.b / 255.0));
	glBegin(GL_LINES);
	glVertex3f(start.x, start.y,0.0);
	glVertex3f(end.x,end.y,0.0);
	glEnd();
}

bool Renderer::Init(GLFWwindow* window) {
	Resize(rect(v2(this->display.startx,this->display.starty),v2(this->display.width,this->display.height)), window);
	
	return true;
}

void Renderer::Update(GLFWwindow* window) {
	float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float) height;

    glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPixelZoom(1.0, -1.0);
	glRasterPos2f(0.0, 0.0);
	//glDrawPixels(this->display.width, this->display.height, GL_RGB, GL_UNSIGNED_BYTE, display.data);
}

void Renderer::PostUpdate(GLFWwindow* window) {
	glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::SetPixel(int x, int y, rgb color) {
	COLOR _color = convertRGB(color);
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = _color.bytes[0];
	display.data[t + 1] = _color.bytes[1];
	display.data[t + 2] = _color.bytes[2];
}

void Renderer::SetPixel(int x, int y, uint8_t color[3]) {
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = color[0];
	display.data[t + 1] = color[1];
	display.data[t + 2] = color[2];
}

void Renderer::ClearPixel(int x, int y) {
	int t = y * display.width * 3 + x * 3;

	display.data[t ] = 0x00;
	display.data[t + 1] = 0x00;
	display.data[t + 2] = 0x00;
}

void Renderer::Clear() {
	free(display.data);
    display.data = new unsigned char[display.width * display.height * 3];

	for (int y = 0; y < this->display.height; ++y) {
		for (int x = 0; x < this->display.width; ++x) {
			ClearPixel(x,y);
		}
	}
}

void Renderer::Resize(rect disp, GLFWwindow* window) {
	display.startx = (int)disp.start.x;
    display.starty = (int)disp.start.y;
    display.width = (int)disp.end.x;
    display.height = (int)disp.end.y;

	Clear();

	glViewport( 0, 0, this->display.width, this->display.height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

	glOrtho(0,this->display.width,this->display.height,0,-1.0,1.0);
}

void Renderer::DrawBox(rect box, rgb color, bool fill) {
	for (int x = box.start.x; x < box.end.x; ++x) {
		for (int y = box.start.y; y < box.end.y; ++y) {
			SetPixel(x, y, color);
		}
	}
}