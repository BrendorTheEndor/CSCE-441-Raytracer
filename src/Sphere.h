#pragma once
#include "Shape.h"


class Sphere :
	public Shape {
public:
	Sphere();
	~Sphere();
	Sphere(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float s, glm::vec3 position, float radius);

	float Intersect(glm::vec3 rayDirection, glm::vec3 rayOrigin, float t0, float t1);
	glm::vec3 GetNormal();

private:
	glm::vec3 position;
	glm::vec3 lastNormal;
	float radius;
};
