#pragma once
#include <vector>
#include "Scene.h"

class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes, glm::vec3 eye, glm::vec3 lookAt, glm::vec3 up, float fovY, float focalDistance);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };

private:

	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;
	float fovY;
	float focalDistance;
	int widthRes;
	int heightRes;

	float *renderedImage;

};
