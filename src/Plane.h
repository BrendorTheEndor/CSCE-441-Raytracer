#pragma once
#include "shape.h"

class Plane :
	public Shape {
public:
	Plane();
	~Plane();
	Plane(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 center, glm::vec3 normal);

	float Intersect(glm::vec3 rayDirection, float t0, float t1);

private:
	glm::vec3 center;
	glm::vec3 normal;
};
