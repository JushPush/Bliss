#include <graphics/renderer.h>

void Renderer::DrawLine(double startx, double starty, double endx, double endy) {
    glPointSize(10);
	glLineWidth(2.5); 
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(startx,starty,0.0);
	glVertex3f(endx,endy,0.0);
	glEnd();
}