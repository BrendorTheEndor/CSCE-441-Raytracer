#pragma once
#include <vector>
#include "Scene.h"

#define RECURSION_MAX 4
const float epsilon = pow(10, -3);

class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, float fovY, float focalDistance);

	// Does the raytrace for all pixels to "take a picture" of the scene
	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };

private:

	// General properties of a camera
	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;
	float fovY;
	float focalDistance;
	int widthRes;
	int heightRes;

	float *renderedImage;

};
