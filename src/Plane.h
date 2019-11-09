#pragma once
#include "shape.h"

class Plane :
	public Shape {
public:
	Plane();
	~Plane();
	Plane(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 center, glm::vec3 normal);

private:
	glm::vec3 center;
	glm::vec3 normal;
};
