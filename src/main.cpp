#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"
#include "Scene.h"

/*
	Questions
	How to set color?
	What is s in shape?
	What is km in shape?
	How do I get A, Li, N, Ri, E, and n?
	What is P, and how do I calculate it (for record)?
	How to get normal for record?
	What is "ray", is it just a direction or is it a point and direction?
*/

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 1200

float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
GLFWwindow* window;

std::vector<Shape*> shapes;
std::vector<Light*> lights;

void ClearFrameBuffer() {
	memset(&frameBuffer, 0, WINDOW_HEIGHT * WINDOW_WIDTH * 3 * sizeof(float));
}

void Display() {
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

void Init() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment5 - Brenden Hover", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearFrameBuffer();

	Camera camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 7.0f), glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f), 45.0f, 1.0f);

	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

	Sphere* sphere1 = new Sphere(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.2, 1.0, 0.2), glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(0.0, 0.0, 0.0), 100.0f, glm::vec3(-1.0, -0.7, 3.0), 0.3f);
	shapes.push_back(sphere1);

	Sphere* sphere2 = new Sphere(glm::vec3(0.1, 0.1, 0.1), glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0, 1.0, 1.0),
		glm::vec3(0.0, 0.0, 0.0), 10.0f, glm::vec3(1.0, -0.5, 3.0), 0.5f);
	shapes.push_back(sphere2);

	//Sphere* sphere3 = new Sphere(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
	//	glm::vec3(1.0, 1.0, 1.0), 0.0f, glm::vec3(-1.0, 0.0, 0.0), 1.0f);
	//shapes.push_back(sphere3);

	//Sphere* sphere4 = new Sphere(glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
	//	glm::vec3(0.8, 0.8, 0.8), 0.0f, glm::vec3(1.0, 0.0, -1.0), 1.0f);
	//shapes.push_back(sphere4);

	Plane* plane1 = new Plane(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0), 0.0f, glm::vec3(0.0, -1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	shapes.push_back(plane1);

	Plane* plane2 = new Plane(glm::vec3(0.1, 0.1, 0.1), glm::vec3(1.0, 1.0, 1.0), glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.0, 0.0, 0.0), 0.0f, glm::vec3(0.0, 0.0, -3.0), glm::vec3(0.0, 0.0, 1.0));
	shapes.push_back(plane2);

	Light* light1 = new Light(glm::vec3(0.0, 3.0, -2.0), glm::vec3(0.2, 0.2, 0.2));
	lights.push_back(light1);

	Light* light2 = new Light(glm::vec3(-2.0, 1.0, 4.0), glm::vec3(0.5, 0.5, 0.5));
	lights.push_back(light2);

	Scene scene = Scene(shapes, lights);

	camera.TakePicture(&scene);
	float* renderedImage = camera.GetRenderedImage();
	memcpy(frameBuffer, renderedImage, sizeof(float) * WINDOW_HEIGHT * WINDOW_WIDTH * 3);

	std::cout << "Picture taken" << std::endl;
}


int main() {
	Init();
	while(glfwWindowShouldClose(window) == 0) {
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}